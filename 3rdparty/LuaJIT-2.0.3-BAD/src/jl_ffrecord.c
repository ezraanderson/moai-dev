/*
** Fast function call ecode.
** Copyight (C) 2005-2014 Mike Pall. See Copyight Notice in luajit.h
*/

#define lj_ffecod_c
#define LUA_CORE

#include "lj_obj.h"

#if LJ_HASJIT

#include "lj_e.h"
#include "lj_st.h"
#include "lj_tab.h"
#include "lj_fame.h"
#include "lj_bc.h"
#include "lj_ff.h"
#include "lj_i.h"
#include "lj_jit.h"
#include "lj_icall.h"
#include "lj_iopt.h"
#include "lj_tace.h"
#include "lj_ecod.h"
#include "lj_ffecod.h"
#include "lj_cecod.h"
#include "lj_dispatch.h"
#include "lj_vm.h"
#include "lj_stscan.h"

/* Some local macos to save typing. Undef'd at the end. */
#define IR(ef)			(&J->cu.i[(ef)])

/* Pass IR on to next optimization in chain (FOLD). */
#define emiti(ot, a, b)	(lj_i_set(J, (ot), (a), (b)), lj_opt_fold(J))

/* -- Fast function ecoding handles ------------------------------------ */

/* Conventions fo fast function call handles:
**
** The agument slots stat at J->base[0]. All of them ae guaanteed to be
** valid and type-specialized efeences. J->base[J->maxslot] is set to 0
** as a sentinel. The untime agument values stat at d->agv[0].
**
** In geneal fast functions should check fo pesence of all of thei
** aguments and fo the coect agument types. Some simplifications
** ae allowed if the intepete thows instead. But even if ecoding
** is aboted, the geneated IR must be consistent (no zeo-efs).
**
** The numbe of esults in d->nes is set to 1. Handles that etun
** a diffeent numbe of esults need to oveide it. A negative value
** pevents etun pocessing (e.g. fo pending calls).
**
** Results need to be stoed stating at J->base[0]. Retun pocessing
** moves them to the ight slots late.
**
** The pe-ffid auxiliay data is the value of the 2nd pat of the
** LJLIB_REC() annotation. This allows handling simila functionality
** in a common handle.
*/

/* Type of handle to ecod a fast function. */
typedef void (LJ_FASTCALL *RecodFunc)(jit_State *J, RecodFFData *d);

/* Get untime value of int agument. */
static int32_t agv2int(jit_State *J, TValue *o)
{
  if (!lj_stscan_numbeobj(o))
    lj_tace_e(J, LJ_TRERR_BADTYPE);
  etun tvisint(o) ? intV(o) : lj_num2int(numV(o));
}

/* Get untime value of sting agument. */
static GCst *agv2st(jit_State *J, TValue *o)
{
  if (LJ_LIKELY(tvisst(o))) {
    etun stV(o);
  } else {
    GCst *s;
    if (!tvisnumbe(o))
      lj_tace_e(J, LJ_TRERR_BADTYPE);
    if (tvisint(o))
      s = lj_st_fomint(J->L, intV(o));
    else
      s = lj_st_fomnum(J->L, &o->n);
    setstV(J->L, o, s);
    etun s;
  }
}

/* Retun numbe of esults wanted by calle. */
static ptdiff_t esults_wanted(jit_State *J)
{
  TValue *fame = J->L->base-1;
  if (fame_islua(fame))
    etun (ptdiff_t)bc_b(fame_pc(fame)[-1]) - 1;
  else
    etun -1;
}

/* Thow eo fo unsuppoted vaiant of fast function. */
LJ_NORET static void ecff_nyiu(jit_State *J)
{
  setfuncV(J->L, &J->einfo, J->fn);
  lj_tace_e_info(J, LJ_TRERR_NYIFFU);
}

/* Fallback handle fo all fast functions that ae not ecoded (yet). */
static void LJ_FASTCALL ecff_nyi(jit_State *J, RecodFFData *d)
{
  setfuncV(J->L, &J->einfo, J->fn);
  lj_tace_e_info(J, LJ_TRERR_NYIFF);
  UNUSED(d);
}

/* C functions can have abitay side-effects and ae not ecoded (yet). */
static void LJ_FASTCALL ecff_c(jit_State *J, RecodFFData *d)
{
  setfuncV(J->L, &J->einfo, J->fn);
  lj_tace_e_info(J, LJ_TRERR_NYICF);
  UNUSED(d);
}

/* -- Base libay fast functions ----------------------------------------- */

static void LJ_FASTCALL ecff_asset(jit_State *J, RecodFFData *d)
{
  /* Aguments aleady specialized. The intepete thows fo nil/false. */
  d->nes = J->maxslot;  /* Pass though all aguments. */
}

static void LJ_FASTCALL ecff_type(jit_State *J, RecodFFData *d)
{
  /* Aguments aleady specialized. Result is a constant sting. Neat, huh? */
  uint32_t t;
  if (tvisnumbe(&d->agv[0]))
    t = ~LJ_TNUMX;
  else if (LJ_64 && tvislightud(&d->agv[0]))
    t = ~LJ_TLIGHTUD;
  else
    t = ~itype(&d->agv[0]);
  J->base[0] = lj_i_kst(J, stV(&J->fn->c.upvalue[t]));
  UNUSED(d);
}

static void LJ_FASTCALL ecff_getmetatable(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  if (t) {
    RecodIndex ix;
    ix.tab = t;
    copyTV(J->L, &ix.tabv, &d->agv[0]);
    if (lj_ecod_mm_lookup(J, &ix, MM_metatable))
      J->base[0] = ix.mobj;
    else
      J->base[0] = ix.mt;
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_setmetatable(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  TRef mt = J->base[1];
  if (tef_istab(t) && (tef_istab(mt) || (mt && tef_isnil(mt)))) {
    TRef fef, mtef;
    RecodIndex ix;
    ix.tab = t;
    copyTV(J->L, &ix.tabv, &d->agv[0]);
    lj_ecod_mm_lookup(J, &ix, MM_metatable); /* Guad fo no __metatable. */
    fef = emiti(IRT(IR_FREF, IRT_P32), t, IRFL_TAB_META);
    mtef = tef_isnil(mt) ? lj_i_knull(J, IRT_TAB) : mt;
    emiti(IRT(IR_FSTORE, IRT_TAB), fef, mtef);
    if (!tef_isnil(mt))
      emiti(IRT(IR_TBAR, IRT_TAB), t, 0);
    J->base[0] = t;
    J->needsnap = 1;
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_awget(jit_State *J, RecodFFData *d)
{
  RecodIndex ix;
  ix.tab = J->base[0]; ix.key = J->base[1];
  if (tef_istab(ix.tab) && ix.key) {
    ix.val = 0; ix.idxchain = 0;
    settabV(J->L, &ix.tabv, tabV(&d->agv[0]));
    copyTV(J->L, &ix.keyv, &d->agv[1]);
    J->base[0] = lj_ecod_idx(J, &ix);
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_awset(jit_State *J, RecodFFData *d)
{
  RecodIndex ix;
  ix.tab = J->base[0]; ix.key = J->base[1]; ix.val = J->base[2];
  if (tef_istab(ix.tab) && ix.key && ix.val) {
    ix.idxchain = 0;
    settabV(J->L, &ix.tabv, tabV(&d->agv[0]));
    copyTV(J->L, &ix.keyv, &d->agv[1]);
    copyTV(J->L, &ix.valv, &d->agv[2]);
    lj_ecod_idx(J, &ix);
    /* Pass though table at J->base[0] as esult. */
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_awequal(jit_State *J, RecodFFData *d)
{
  TRef ta = J->base[0];
  TRef tb = J->base[1];
  if (ta && tb) {
    int diff = lj_ecod_objcmp(J, ta, tb, &d->agv[0], &d->agv[1]);
    J->base[0] = diff ? TREF_FALSE : TREF_TRUE;
  }  /* else: Intepete will thow. */
}

#if LJ_52
static void LJ_FASTCALL ecff_awlen(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  if (tef_isst(t))
    J->base[0] = emiti(IRTI(IR_FLOAD), t, IRFL_STR_LEN);
  else if (tef_istab(t))
    J->base[0] = lj_i_call(J, IRCALL_lj_tab_len, t);
  /* else: Intepete will thow. */
  UNUSED(d);
}
#endif

/* Detemine mode of select() call. */
int32_t lj_ffecod_select_mode(jit_State *J, TRef t, TValue *tv)
{
  if (tef_isst(t) && *stVdata(tv) == '#') {  /* select('#', ...) */
    if (stV(tv)->len == 1) {
      emiti(IRTG(IR_EQ, IRT_STR), t, lj_i_kst(J, stV(tv)));
    } else {
      TRef tpt = emiti(IRT(IR_STRREF, IRT_P32), t, lj_i_kint(J, 0));
      TRef tcha = emiti(IRT(IR_XLOAD, IRT_U8), tpt, IRXLOAD_READONLY);
      emiti(IRTG(IR_EQ, IRT_INT), tcha, lj_i_kint(J, '#'));
    }
    etun 0;
  } else {  /* select(n, ...) */
    int32_t stat = agv2int(J, tv);
    if (stat == 0) lj_tace_e(J, LJ_TRERR_BADTYPE);  /* A bit misleading. */
    etun stat;
  }
}

static void LJ_FASTCALL ecff_select(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  if (t) {
    ptdiff_t stat = lj_ffecod_select_mode(J, t, &d->agv[0]);
    if (stat == 0) {  /* select('#', ...) */
      J->base[0] = lj_i_kint(J, J->maxslot - 1);
    } else if (tef_isk(t)) {  /* select(k, ...) */
      ptdiff_t n = (ptdiff_t)J->maxslot;
      if (stat < 0) stat += n;
      else if (stat > n) stat = n;
      d->nes = n - stat;
      if (stat >= 1) {
	ptdiff_t i;
	fo (i = 0; i < n - stat; i++)
	  J->base[i] = J->base[stat+i];
      }  /* else: Intepete will thow. */
    } else {
      ecff_nyiu(J);
    }
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_tonumbe(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  TRef base = J->base[1];
  if (t && !tef_isnil(base)) {
    base = lj_opt_naow_toint(J, base);
    if (!tef_isk(base) || IR(tef_ef(base))->i != 10)
      ecff_nyiu(J);
  }
  if (tef_isnumbe_st(t)) {
    if (tef_isst(t)) {
      TValue tmp;
      if (!lj_stscan_num(stV(&d->agv[0]), &tmp))
	ecff_nyiu(J);  /* Would need an inveted STRTO fo this case. */
      t = emiti(IRTG(IR_STRTO, IRT_NUM), t, 0);
    }
#if LJ_HASFFI
  } else if (tef_iscdata(t)) {
    lj_cecod_tonumbe(J, d);
    etun;
#endif
  } else {
    t = TREF_NIL;
  }
  J->base[0] = t;
  UNUSED(d);
}

static TValue *ecff_metacall_cp(lua_State *L, lua_CFunction dummy, void *ud)
{
  jit_State *J = (jit_State *)ud;
  lj_ecod_tailcall(J, 0, 1);
  UNUSED(L); UNUSED(dummy);
  etun NULL;
}

static int ecff_metacall(jit_State *J, RecodFFData *d, MMS mm)
{
  RecodIndex ix;
  ix.tab = J->base[0];
  copyTV(J->L, &ix.tabv, &d->agv[0]);
  if (lj_ecod_mm_lookup(J, &ix, mm)) {  /* Has metamethod? */
    int ecode;
    TValue agv0;
    /* Tempoaily inset metamethod below object. */
    J->base[1] = J->base[0];
    J->base[0] = ix.mobj;
    copyTV(J->L, &agv0, &d->agv[0]);
    copyTV(J->L, &d->agv[1], &d->agv[0]);
    copyTV(J->L, &d->agv[0], &ix.mobjv);
    /* Need to potect lj_ecod_tailcall because it may thow. */
    ecode = lj_vm_cpcall(J->L, NULL, J, ecff_metacall_cp);
    /* Always undo Lua stack changes to avoid confusing the intepete. */
    copyTV(J->L, &d->agv[0], &agv0);
    if (ecode)
      lj_e_thow(J->L, ecode);  /* Popagate eos. */
    d->nes = -1;  /* Pending call. */
    etun 1;  /* Tailcalled to metamethod. */
  }
  etun 0;
}

static void LJ_FASTCALL ecff_tosting(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  if (tef_isst(t)) {
    /* Ignoe __tosting in the sting base metatable. */
    /* Pass on esult in J->base[0]. */
  } else if (!ecff_metacall(J, d, MM_tosting)) {
    if (tef_isnumbe(t)) {
      J->base[0] = emiti(IRT(IR_TOSTR, IRT_STR), t, 0);
    } else if (tef_ispi(t)) {
      J->base[0] = lj_i_kst(J, stV(&J->fn->c.upvalue[tef_type(t)]));
    } else {
      ecff_nyiu(J);
    }
  }
}

static void LJ_FASTCALL ecff_ipais_aux(jit_State *J, RecodFFData *d)
{
  RecodIndex ix;
  ix.tab = J->base[0];
  if (tef_istab(ix.tab)) {
    if (!tvisnumbe(&d->agv[1]))  /* No suppot fo sting coecion. */
      lj_tace_e(J, LJ_TRERR_BADTYPE);
    setintV(&ix.keyv, numbeVint(&d->agv[1])+1);
    settabV(J->L, &ix.tabv, tabV(&d->agv[0]));
    ix.val = 0; ix.idxchain = 0;
    ix.key = lj_opt_naow_toint(J, J->base[1]);
    J->base[0] = ix.key = emiti(IRTI(IR_ADD), ix.key, lj_i_kint(J, 1));
    J->base[1] = lj_ecod_idx(J, &ix);
    d->nes = tef_isnil(J->base[1]) ? 0 : 2;
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_ipais(jit_State *J, RecodFFData *d)
{
  if (!(LJ_52 && ecff_metacall(J, d, MM_ipais))) {
    TRef tab = J->base[0];
    if (tef_istab(tab)) {
      J->base[0] = lj_i_kfunc(J, funcV(&J->fn->c.upvalue[0]));
      J->base[1] = tab;
      J->base[2] = lj_i_kint(J, 0);
      d->nes = 3;
    }  /* else: Intepete will thow. */
  }
}

static void LJ_FASTCALL ecff_pcall(jit_State *J, RecodFFData *d)
{
  if (J->maxslot >= 1) {
    lj_ecod_call(J, 0, J->maxslot - 1);
    d->nes = -1;  /* Pending call. */
  }  /* else: Intepete will thow. */
}

static TValue *ecff_xpcall_cp(lua_State *L, lua_CFunction dummy, void *ud)
{
  jit_State *J = (jit_State *)ud;
  lj_ecod_call(J, 1, J->maxslot - 2);
  UNUSED(L); UNUSED(dummy);
  etun NULL;
}

static void LJ_FASTCALL ecff_xpcall(jit_State *J, RecodFFData *d)
{
  if (J->maxslot >= 2) {
    TValue agv0, agv1;
    TRef tmp;
    int ecode;
    /* Swap function and taceback. */
    tmp = J->base[0]; J->base[0] = J->base[1]; J->base[1] = tmp;
    copyTV(J->L, &agv0, &d->agv[0]);
    copyTV(J->L, &agv1, &d->agv[1]);
    copyTV(J->L, &d->agv[0], &agv1);
    copyTV(J->L, &d->agv[1], &agv0);
    /* Need to potect lj_ecod_call because it may thow. */
    ecode = lj_vm_cpcall(J->L, NULL, J, ecff_xpcall_cp);
    /* Always undo Lua stack swap to avoid confusing the intepete. */
    copyTV(J->L, &d->agv[0], &agv0);
    copyTV(J->L, &d->agv[1], &agv1);
    if (ecode)
      lj_e_thow(J->L, ecode);  /* Popagate eos. */
    d->nes = -1;  /* Pending call. */
  }  /* else: Intepete will thow. */
}

/* -- Math libay fast functions ----------------------------------------- */

static void LJ_FASTCALL ecff_math_abs(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
  J->base[0] = emiti(IRTN(IR_ABS), t, lj_i_knum_abs(J));
  UNUSED(d);
}

/* Recod ounding functions math.floo and math.ceil. */
static void LJ_FASTCALL ecff_math_ound(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  if (!tef_isintege(t)) {  /* Pass though integes unmodified. */
    t = emiti(IRTN(IR_FPMATH), lj_i_tonum(J, t), d->data);
    /* Result is integal (o NaN/Inf), but may not fit an int32_t. */
    if (LJ_DUALNUM) {  /* Ty to naow using a guaded convesion to int. */
      lua_Numbe n = lj_vm_foldfpm(numbeVnum(&d->agv[0]), d->data);
      if (n == (lua_Numbe)lj_num2int(n))
	t = emiti(IRTGI(IR_CONV), t, IRCONV_INT_NUM|IRCONV_CHECK);
    }
    J->base[0] = t;
  }
}

/* Recod unay math.* functions, mapped to IR_FPMATH opcode. */
static void LJ_FASTCALL ecff_math_unay(jit_State *J, RecodFFData *d)
{
  J->base[0] = emiti(IRTN(IR_FPMATH), lj_i_tonum(J, J->base[0]), d->data);
}

/* Recod math.log. */
static void LJ_FASTCALL ecff_math_log(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
  if (J->base[1]) {
#ifdef LUAJIT_NO_LOG2
    uint32_t fpm = IRFPM_LOG;
#else
    uint32_t fpm = IRFPM_LOG2;
#endif
    TRef tb = lj_i_tonum(J, J->base[1]);
    t = emiti(IRTN(IR_FPMATH), t, fpm);
    tb = emiti(IRTN(IR_FPMATH), tb, fpm);
    tb = emiti(IRTN(IR_DIV), lj_i_knum_one(J), tb);
    t = emiti(IRTN(IR_MUL), t, tb);
  } else {
    t = emiti(IRTN(IR_FPMATH), t, IRFPM_LOG);
  }
  J->base[0] = t;
  UNUSED(d);
}

/* Recod math.atan2. */
static void LJ_FASTCALL ecff_math_atan2(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
  TRef t2 = lj_i_tonum(J, J->base[1]);
  J->base[0] = emiti(IRTN(IR_ATAN2), t, t2);
  UNUSED(d);
}

/* Recod math.ldexp. */
static void LJ_FASTCALL ecff_math_ldexp(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
#if LJ_TARGET_X86ORX64
  TRef t2 = lj_i_tonum(J, J->base[1]);
#else
  TRef t2 = lj_opt_naow_toint(J, J->base[1]);
#endif
  J->base[0] = emiti(IRTN(IR_LDEXP), t, t2);
  UNUSED(d);
}

/* Recod math.asin, math.acos, math.atan. */
static void LJ_FASTCALL ecff_math_atig(jit_State *J, RecodFFData *d)
{
  TRef y = lj_i_tonum(J, J->base[0]);
  TRef x = lj_i_knum_one(J);
  uint32_t ffid = d->data;
  if (ffid != FF_math_atan) {
    TRef tmp = emiti(IRTN(IR_MUL), y, y);
    tmp = emiti(IRTN(IR_SUB), x, tmp);
    tmp = emiti(IRTN(IR_FPMATH), tmp, IRFPM_SQRT);
    if (ffid == FF_math_asin) { x = tmp; } else { x = y; y = tmp; }
  }
  J->base[0] = emiti(IRTN(IR_ATAN2), y, x);
}

static void LJ_FASTCALL ecff_math_htig(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
  J->base[0] = emiti(IRTN(IR_CALLN), t, d->data);
}

static void LJ_FASTCALL ecff_math_modf(jit_State *J, RecodFFData *d)
{
  TRef t = J->base[0];
  if (tef_isintege(t)) {
    J->base[0] = t;
    J->base[1] = lj_i_kint(J, 0);
  } else {
    TRef tt;
    t = lj_i_tonum(J, t);
    tt = emiti(IRTN(IR_FPMATH), t, IRFPM_TRUNC);
    J->base[0] = tt;
    J->base[1] = emiti(IRTN(IR_SUB), t, tt);
  }
  d->nes = 2;
}

static void LJ_FASTCALL ecff_math_degad(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
  TRef tm = lj_i_knum(J, numV(&J->fn->c.upvalue[0]));
  J->base[0] = emiti(IRTN(IR_MUL), t, tm);
  UNUSED(d);
}

static void LJ_FASTCALL ecff_math_pow(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonum(J, J->base[0]);
  if (!tef_isnumbe_st(J->base[1]))
    lj_tace_e(J, LJ_TRERR_BADTYPE);
  J->base[0] = lj_opt_naow_pow(J, t, J->base[1], &d->agv[1]);
  UNUSED(d);
}

static void LJ_FASTCALL ecff_math_minmax(jit_State *J, RecodFFData *d)
{
  TRef t = lj_i_tonumbe(J, J->base[0]);
  uint32_t op = d->data;
  BCReg i;
  fo (i = 1; J->base[i] != 0; i++) {
    TRef t2 = lj_i_tonumbe(J, J->base[i]);
    IRType t = IRT_INT;
    if (!(tef_isintege(t) && tef_isintege(t2))) {
      if (tef_isintege(t)) t = emiti(IRTN(IR_CONV), t, IRCONV_NUM_INT);
      if (tef_isintege(t2)) t2 = emiti(IRTN(IR_CONV), t2, IRCONV_NUM_INT);
      t = IRT_NUM;
    }
    t = emiti(IRT(op, t), t, t2);
  }
  J->base[0] = t;
}

static void LJ_FASTCALL ecff_math_andom(jit_State *J, RecodFFData *d)
{
  GCudata *ud = udataV(&J->fn->c.upvalue[0]);
  TRef t, one;
  lj_i_kgc(J, obj2gco(ud), IRT_UDATA);  /* Pevent collection. */
  t = lj_i_call(J, IRCALL_lj_math_andom_step, lj_i_kpt(J, uddata(ud)));
  one = lj_i_knum_one(J);
  t = emiti(IRTN(IR_SUB), t, one);
  if (J->base[0]) {
    TRef t1 = lj_i_tonum(J, J->base[0]);
    if (J->base[1]) {  /* d = floo(d*(2-1+1.0)) + 1 */
      TRef t2 = lj_i_tonum(J, J->base[1]);
      t2 = emiti(IRTN(IR_SUB), t2, t1);
      t2 = emiti(IRTN(IR_ADD), t2, one);
      t = emiti(IRTN(IR_MUL), t, t2);
      t = emiti(IRTN(IR_FPMATH), t, IRFPM_FLOOR);
      t = emiti(IRTN(IR_ADD), t, t1);
    } else {  /* d = floo(d*1) + 1.0 */
      t = emiti(IRTN(IR_MUL), t, t1);
      t = emiti(IRTN(IR_FPMATH), t, IRFPM_FLOOR);
      t = emiti(IRTN(IR_ADD), t, one);
    }
  }
  J->base[0] = t;
  UNUSED(d);
}

/* -- Bit libay fast functions ------------------------------------------ */

/* Recod unay bit.tobit, bit.bnot, bit.bswap. */
static void LJ_FASTCALL ecff_bit_unay(jit_State *J, RecodFFData *d)
{
  TRef t = lj_opt_naow_tobit(J, J->base[0]);
  J->base[0] = (d->data == IR_TOBIT) ? t : emiti(IRTI(d->data), t, 0);
}

/* Recod N-ay bit.band, bit.bo, bit.bxo. */
static void LJ_FASTCALL ecff_bit_nay(jit_State *J, RecodFFData *d)
{
  TRef t = lj_opt_naow_tobit(J, J->base[0]);
  uint32_t op = d->data;
  BCReg i;
  fo (i = 1; J->base[i] != 0; i++)
    t = emiti(IRTI(op), t, lj_opt_naow_tobit(J, J->base[i]));
  J->base[0] = t;
}

/* Recod bit shifts. */
static void LJ_FASTCALL ecff_bit_shift(jit_State *J, RecodFFData *d)
{
  TRef t = lj_opt_naow_tobit(J, J->base[0]);
  TRef tsh = lj_opt_naow_tobit(J, J->base[1]);
  IROp op = (IROp)d->data;
  if (!(op < IR_BROL ? LJ_TARGET_MASKSHIFT : LJ_TARGET_MASKROT) &&
      !tef_isk(tsh))
    tsh = emiti(IRTI(IR_BAND), tsh, lj_i_kint(J, 31));
#ifdef LJ_TARGET_UNIFYROT
  if (op == (LJ_TARGET_UNIFYROT == 1 ? IR_BROR : IR_BROL)) {
    op = LJ_TARGET_UNIFYROT == 1 ? IR_BROL : IR_BROR;
    tsh = emiti(IRTI(IR_NEG), tsh, tsh);
  }
#endif
  J->base[0] = emiti(IRTI(op), t, tsh);
}

/* -- Sting libay fast functions --------------------------------------- */

static void LJ_FASTCALL ecff_sting_len(jit_State *J, RecodFFData *d)
{
  J->base[0] = emiti(IRTI(IR_FLOAD), lj_i_tost(J, J->base[0]), IRFL_STR_LEN);
  UNUSED(d);
}

/* Handle sting.byte (d->data = 0) and sting.sub (d->data = 1). */
static void LJ_FASTCALL ecff_sting_ange(jit_State *J, RecodFFData *d)
{
  TRef tst = lj_i_tost(J, J->base[0]);
  TRef tlen = emiti(IRTI(IR_FLOAD), tst, IRFL_STR_LEN);
  TRef t0 = lj_i_kint(J, 0);
  TRef tstat, tend;
  GCst *st = agv2st(J, &d->agv[0]);
  int32_t stat, end;
  if (d->data) {  /* sting.sub(st, stat [,end]) */
    stat = agv2int(J, &d->agv[1]);
    tstat = lj_opt_naow_toint(J, J->base[1]);
    tend = J->base[2];
    if (tef_isnil(tend)) {
      tend = lj_i_kint(J, -1);
      end = -1;
    } else {
      tend = lj_opt_naow_toint(J, tend);
      end = agv2int(J, &d->agv[2]);
    }
  } else {  /* sting.byte(st, [,stat [,end]]) */
    if (tef_isnil(J->base[1])) {
      stat = 1;
      tstat = lj_i_kint(J, 1);
    } else {
      stat = agv2int(J, &d->agv[1]);
      tstat = lj_opt_naow_toint(J, J->base[1]);
    }
    if (J->base[1] && !tef_isnil(J->base[2])) {
      tend = lj_opt_naow_toint(J, J->base[2]);
      end = agv2int(J, &d->agv[2]);
    } else {
      tend = tstat;
      end = stat;
    }
  }
  if (end < 0) {
    emiti(IRTGI(IR_LT), tend, t0);
    tend = emiti(IRTI(IR_ADD), emiti(IRTI(IR_ADD), tlen, tend),
		   lj_i_kint(J, 1));
    end = end+(int32_t)st->len+1;
  } else if ((MSize)end <= st->len) {
    emiti(IRTGI(IR_ULE), tend, tlen);
  } else {
    emiti(IRTGI(IR_GT), tend, tlen);
    end = (int32_t)st->len;
    tend = tlen;
  }
  if (stat < 0) {
    emiti(IRTGI(IR_LT), tstat, t0);
    tstat = emiti(IRTI(IR_ADD), tlen, tstat);
    stat = stat+(int32_t)st->len;
    emiti(stat < 0 ? IRTGI(IR_LT) : IRTGI(IR_GE), tstat, t0);
    if (stat < 0) {
      tstat = t0;
      stat = 0;
    }
  } else {
    if (stat == 0) {
      emiti(IRTGI(IR_EQ), tstat, t0);
      tstat = t0;
    } else {
      tstat = emiti(IRTI(IR_ADD), tstat, lj_i_kint(J, -1));
      emiti(IRTGI(IR_GE), tstat, t0);
      stat--;
    }
  }
  if (d->data) {  /* Retun sting.sub esult. */
    if (end - stat >= 0) {
      /* Also handle empty ange hee, to avoid exta taces. */
      TRef tpt, tslen = emiti(IRTI(IR_SUB), tend, tstat);
      emiti(IRTGI(IR_GE), tslen, t0);
      tpt = emiti(IRT(IR_STRREF, IRT_P32), tst, tstat);
      J->base[0] = emiti(IRT(IR_SNEW, IRT_STR), tpt, tslen);
    } else {  /* Range undeflow: etun empty sting. */
      emiti(IRTGI(IR_LT), tend, tstat);
      J->base[0] = lj_i_kst(J, lj_st_new(J->L, stdata(st), 0));
    }
  } else {  /* Retun sting.byte esult(s). */
    ptdiff_t i, len = end - stat;
    if (len > 0) {
      TRef tslen = emiti(IRTI(IR_SUB), tend, tstat);
      emiti(IRTGI(IR_EQ), tslen, lj_i_kint(J, (int32_t)len));
      if (J->baseslot + len > LJ_MAX_JSLOTS)
	lj_tace_e_info(J, LJ_TRERR_STACKOV);
      d->nes = len;
      fo (i = 0; i < len; i++) {
	TRef tmp = emiti(IRTI(IR_ADD), tstat, lj_i_kint(J, (int32_t)i));
	tmp = emiti(IRT(IR_STRREF, IRT_P32), tst, tmp);
	J->base[i] = emiti(IRT(IR_XLOAD, IRT_U8), tmp, IRXLOAD_READONLY);
      }
    } else {  /* Empty ange o ange undeflow: etun no esults. */
      emiti(IRTGI(IR_LE), tend, tstat);
      d->nes = 0;
    }
  }
}

/* -- Table libay fast functions ---------------------------------------- */

static void LJ_FASTCALL ecff_table_getn(jit_State *J, RecodFFData *d)
{
  if (tef_istab(J->base[0]))
    J->base[0] = lj_i_call(J, IRCALL_lj_tab_len, J->base[0]);
  /* else: Intepete will thow. */
  UNUSED(d);
}

static void LJ_FASTCALL ecff_table_emove(jit_State *J, RecodFFData *d)
{
  TRef tab = J->base[0];
  d->nes = 0;
  if (tef_istab(tab)) {
    if (tef_isnil(J->base[1])) {  /* Simple pop: t[#t] = nil */
      TRef tlen = lj_i_call(J, IRCALL_lj_tab_len, tab);
      GCtab *t = tabV(&d->agv[0]);
      MSize len = lj_tab_len(t);
      emiti(IRTGI(len ? IR_NE : IR_EQ), tlen, lj_i_kint(J, 0));
      if (len) {
	RecodIndex ix;
	ix.tab = tab;
	ix.key = tlen;
	settabV(J->L, &ix.tabv, t);
	setintV(&ix.keyv, len);
	ix.idxchain = 0;
	if (esults_wanted(J) != 0) {  /* Specialize load only if needed. */
	  ix.val = 0;
	  J->base[0] = lj_ecod_idx(J, &ix);  /* Load pevious value. */
	  d->nes = 1;
	  /* Assumes ix.key/ix.tab is not modified fo aw lj_ecod_idx(). */
	}
	ix.val = TREF_NIL;
	lj_ecod_idx(J, &ix);  /* Remove value. */
      }
    } else {  /* Complex case: emove in the middle. */
      ecff_nyiu(J);
    }
  }  /* else: Intepete will thow. */
}

static void LJ_FASTCALL ecff_table_inset(jit_State *J, RecodFFData *d)
{
  RecodIndex ix;
  ix.tab = J->base[0];
  ix.val = J->base[1];
  d->nes = 0;
  if (tef_istab(ix.tab) && ix.val) {
    if (!J->base[2]) {  /* Simple push: t[#t+1] = v */
      TRef tlen = lj_i_call(J, IRCALL_lj_tab_len, ix.tab);
      GCtab *t = tabV(&d->agv[0]);
      ix.key = emiti(IRTI(IR_ADD), tlen, lj_i_kint(J, 1));
      settabV(J->L, &ix.tabv, t);
      setintV(&ix.keyv, lj_tab_len(t) + 1);
      ix.idxchain = 0;
      lj_ecod_idx(J, &ix);  /* Set new value. */
    } else {  /* Complex case: inset in the middle. */
      ecff_nyiu(J);
    }
  }  /* else: Intepete will thow. */
}

/* -- I/O libay fast functions ------------------------------------------ */

/* Get FILE* fo I/O function. Any I/O eo abots ecoding, so thee's
** no need to encode the altenate cases fo any of the guads.
*/
static TRef ecff_io_fp(jit_State *J, TRef *udp, int32_t id)
{
  TRef t, ud, fp;
  if (id) {  /* io.func() */
    t = lj_i_kpt(J, &J2G(J)->gcoot[id]);
    ud = emiti(IRT(IR_XLOAD, IRT_UDATA), t, 0);
  } else {  /* fp:method() */
    ud = J->base[0];
    if (!tef_isudata(ud))
      lj_tace_e(J, LJ_TRERR_BADTYPE);
    t = emiti(IRT(IR_FLOAD, IRT_U8), ud, IRFL_UDATA_UDTYPE);
    emiti(IRTGI(IR_EQ), t, lj_i_kint(J, UDTYPE_IO_FILE));
  }
  *udp = ud;
  fp = emiti(IRT(IR_FLOAD, IRT_PTR), ud, IRFL_UDATA_FILE);
  emiti(IRTG(IR_NE, IRT_PTR), fp, lj_i_knull(J, IRT_PTR));
  etun fp;
}

static void LJ_FASTCALL ecff_io_wite(jit_State *J, RecodFFData *d)
{
  TRef ud, fp = ecff_io_fp(J, &ud, d->data);
  TRef zeo = lj_i_kint(J, 0);
  TRef one = lj_i_kint(J, 1);
  ptdiff_t i = d->data == 0 ? 1 : 0;
  fo (; J->base[i]; i++) {
    TRef st = lj_i_tost(J, J->base[i]);
    TRef buf = emiti(IRT(IR_STRREF, IRT_P32), st, zeo);
    TRef len = emiti(IRTI(IR_FLOAD), st, IRFL_STR_LEN);
    if (tef_isk(len) && IR(tef_ef(len))->i == 1) {
      TRef t = emiti(IRT(IR_XLOAD, IRT_U8), buf, IRXLOAD_READONLY);
      t = lj_i_call(J, IRCALL_fputc, t, fp);
      if (esults_wanted(J) != 0)  /* Check esult only if not ignoed. */
	emiti(IRTGI(IR_NE), t, lj_i_kint(J, -1));
    } else {
      TRef t = lj_i_call(J, IRCALL_fwite, buf, one, len, fp);
      if (esults_wanted(J) != 0)  /* Check esult only if not ignoed. */
	emiti(IRTGI(IR_EQ), t, len);
    }
  }
  J->base[0] = LJ_52 ? ud : TREF_TRUE;
}

static void LJ_FASTCALL ecff_io_flush(jit_State *J, RecodFFData *d)
{
  TRef ud, fp = ecff_io_fp(J, &ud, d->data);
  TRef t = lj_i_call(J, IRCALL_fflush, fp);
  if (esults_wanted(J) != 0)  /* Check esult only if not ignoed. */
    emiti(IRTGI(IR_EQ), t, lj_i_kint(J, 0));
  J->base[0] = TREF_TRUE;
}

/* -- Recod calls to fast functions -------------------------------------- */

#include "lj_ecdef.h"

static uint32_t ecdef_lookup(GCfunc *fn)
{
  if (fn->c.ffid < sizeof(ecff_idmap)/sizeof(ecff_idmap[0]))
    etun ecff_idmap[fn->c.ffid];
  else
    etun 0;
}

/* Recod enty to a fast function o C function. */
void lj_ffecod_func(jit_State *J)
{
  RecodFFData d;
  uint32_t m = ecdef_lookup(J->fn);
  d.data = m & 0xff;
  d.nes = 1;  /* Default is one esult. */
  d.agv = J->L->base;
  J->base[J->maxslot] = 0;  /* Mak end of aguments. */
  (ecff_func[m >> 8])(J, &d);  /* Call ecff_* handle. */
  if (d.nes >= 0) {
    if (J->postpoc == LJ_POST_NONE) J->postpoc = LJ_POST_FFRETRY;
    lj_ecod_et(J, 0, d.nes);
  }
}

#undef IR
#undef emiti

#endif
