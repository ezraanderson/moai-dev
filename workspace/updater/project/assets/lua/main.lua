


--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
---_globals.lua


local function unit__globals()

print('LOADING _GLOBALS')



--**********************************************************
--**********************************************************
system = {}

--**********************************************************
--MOI
mFramebuffer = {}

mHttp		   = {}

mThread			= {}


mTexture	    = {}
mShader	        = {}
mColors	        = {}
mQuad	        = {}

mAnimate 	    = {}
mCurve   	    = {}

mLayer   	    = {}
mViewport       = {}	
mCamera			= {}

mProp			= {}
mText		    = {}
mFont		    = {}
mColor	  		= {}
mSprite	  		= {} 
mTimers 	  	= {}
mQuad		  	= {}
mUntz		  	= {}
mProps      	= {}



sKeyboard       = {}
sMenu			= {}
sHighscore		= {}



--******************************************************************************
--
isLoaded = false


A         	= {} --COROUTINE
D 			= {} --DEBUG
F 			= {} --FUNCTION
L         	= {} --LOAD
input 		= {} --INPUT FUNCTIONS
keyArray 	= {} --KEYS DOWN




keyArray[119] = false
keyArray[115] = false
keyArray[97]  = false
keyArray[100] = false







--********************************
--GETS REMOVED FROM SQUISH
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
end --END SQUISH FUNCTION
unit__globals()
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
---debug_fps.lua


local function unit_debug_fps()
--ADD COMMAS
function comma_value(amount)
  local formatted = amount
  while true do
    formatted, k = string.gsub(formatted, "^(-?%d+)(%d%d%d)", '%1,%2')
    if (k==0) then
      break
    end
  end
  return formatted
end




--ROUND
function round(val, decimal)
  if (decimal) then
    return math.floor( (val * 10^decimal) + 0.5) / (10^decimal)
  else
    return math.floor(val+0.5)
  end
end




--MESSAGE
function format_num(amount, decimal, prefix, neg_prefix)

  local str_amount,  formatted, famount, remain

  decimal = decimal or 2  -- default 2 decimal places
  neg_prefix = neg_prefix or "-" -- default negative sign

  famount = math.abs(round(amount,decimal))
  famount = math.floor(famount)

  remain = round(math.abs(amount) - famount, decimal)

        -- comma to separate the thousands
  formatted = comma_value(famount)

        -- attach the decimal portion
  if (decimal > 0) then
    remain = string.sub(tostring(remain),3)
    formatted = formatted .. "." .. remain ..
                string.rep("0", decimal - string.len(remain))
  end

        -- attach prefix string e.g '$'
  formatted = (prefix or "") .. formatted

        -- if value is negative then format accordingly
  if (amount<0) then
    if (neg_prefix=="()") then
      formatted = "("..formatted ..")"
    else
      formatted = neg_prefix .. formatted
    end
  end

  return formatted
end



--******************************************************************************

local myCache = {}

myCache['total']  		=0
myCache['lua']    		=0
myCache['texture']		=0
myCache['_luagc_count'] =0
myCache['_sys_rss']		=0
myCache['_sys_vs']		=0




local memUsage 	=0

local total 	= 0
local lua 		= 0
local texture   = 0
local lc        = 0
local sr        = 0
local sv        = 0




function printMemeUsage()

--MOAISim.forceGarbageCollection()

memUsage 	= MOAISim.getMemoryUsage()



total 	  = memUsage['total'] 		/1024
lua 	  = memUsage['lua'] 		/1024
texture   = memUsage['texture'] 	/1024
lc        = memUsage['_luagc_count']/1024
sr        = memUsage['_sys_rss']
sv        = memUsage['_sys_vs']




for k,v in pairs(memUsage) do

print(k,v)


end


print('-----------------------------------------------------------------------')
print('total:           '..format_num(total,2)		..'   '..format_num(myCache['total'],2)		..'   '..format_num(total-myCache['total'],2))
print('lua:             '..format_num(lua,2)		..'   '..format_num(myCache['lua'],2)		..'   '..format_num(lua-myCache['lua'],2))
print('texture:         '..format_num(texture,2)	..'   '..format_num(myCache['texture'],2)	..'   '..format_num(texture-myCache['texture'],2))
print('')
print('_luagc_count:    '..format_num(lc,-2))
--print('_sys_rss:        '..format_num(sr,-2))
--print('_sys_vs:         '..format_num(sv,-2))
print('-----------------------------------------------------------------------')

                            
if myCache['total'] == 0 then

			myCache['total']  		=total
			myCache['lua']    		=lua
			myCache['texture']		=texture
			myCache['lc']			=lc
			myCache['sr']			=sr
			myCache['sv']			=sv


end


	print('')
end


--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
end --END SQUISH FUNCTION
unit_debug_fps()
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
---geohop.lua


local function unit_geohop()
MOAISim.setTraceback(function() end)

local math   = math
local random = math.random
local cos    = math.cos
local sin    = math.sin
local pi     = math.pi
local atan2  = math.atan2
local rad	 = math.rad
local sqrt   = math.sqrt
local floor  = math.floor
local abs	 = math.abs
local deg	 = math.deg
local rad    = math.rad






local make_icon = false

local scale_width   = 480
local scale_height  = 320
local pw = scale_width / 480
local ph = scale_height / 320




--******************************************************************************
function rect_vs_rect(r1l, r1t, r1r, r1b, r2l, r2t, r2r, r2b)
  if r1r < r2l or r1l > r2r then
    return false
  end
  if r1b < r2t or r1t > r2b then
    return false
  end
  return true
end






--******************************************************************************
local function math_getDistance(x1, y1, x2, y2)
        return math.sqrt( ((x2-x1)^2) + ((y2-y1)^2) )
end



--******************************************************************************


local keys = {}
local gExplode = {}
local gTrail   = {}
local mHero = {}

local best 		= 0
local death_cnt = 0

local color_idx     = 0
local color_current = {1,1,0,1}
local color_list  = {
					{1,0,0,1},
					{0,1,0,1},
					{0,0,1,1},
					{1,0,1,1},
					{1,1,0,1},
					{0,1,1,1},
					{1,1,1,1},
				  }
--******************************************************************************
local hero_dx,hero_dy  =  0,0
local start_x,start_y  =32+10,320-10-32
local hero_x,hero_y    = start_x,start_y

local jump_time     = os.clock()
local jump_speed    = 0
local jump_state    = 'ground'
local dx_speed 		= 2




---****************************************************************************


local bonus_left  = {
						--{2,8},
						{2,2},
						{2,7},
						{4,6},
						{4,3},
						{2,5},
						{4,5},
						{3,3},
						{3,5},
					}





local bonus_right  = {
					--	{(2+12),8},
						{(2+12),2},
						{(2+12),7},
						{(4+8),6},
						{(4+8),3},
						{(2+12),5},
						{(4+8),5},
						{(3+10),3},
						{(3+10),5},
					}







--**********************************
--LOCAL MERGE

local bonus_list 	= {}
local bonus_index   = 0
local bonus_has     = true
local bonus_x 		= 0
local bonus_y 		= 0
local bonus_time 	= os.clock()


for i = 1, #bonus_left do


	--RIGHT
	local x = (bonus_right[i][1]*32)-16
	local y = (bonus_right[i][2]*32)

	bonus_right[i][1] = x
	bonus_right[i][2] = y
	bonus_list[#bonus_list+1] = {x,y}



	--LEFT
	local x = (bonus_left[i][1] *32) -16
	local y = (bonus_left[i][2] *32)

	bonus_left[i][1] = x
	bonus_left[i][2] = y
	bonus_list[#bonus_list+1] = {x,y}

end




--******************************************************************************
--COLIISION
local box_list = {
					{16,15,200,320-15},
					{480-200,15,480-16,320-15},

					{200-16,110,300,210},
				 }










--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************







--*************************************************************
--RESET
local function rest_me()
	
print('>> RESET ME')

		hero_x,hero_y    = start_x,start_y
		jump_state 		 = 'ground'

		bonus_has   = true
		bonus_index = 0
		bonus_index = bonus_index + 1
		if bonus_index > #bonus_list then
		bonus_index = 1
		end

		bonus_x 	 = bonus_list[bonus_index][1]
		bonus_y		 = bonus_list[bonus_index][2]
		bonus_time 	 = os.clock()

	

end






--****************************************************
--SHOW AN AD
function F._show_ad_done()
	print('***********************')
	print('***********************')
	print(' ADS DONE')
	mFramebuffer['prop']:seekColor(1,1,1,1,1,MOAIEaseType.LINEAR)
	print('***********************')
	print('***********************')
end

function F._show_ad()
print('**')	
print('**')	
print('------------------------------------------------')
print('isFree',system['isFree'])
	if 	 (system['isFree'] == true) then

	
			if MOAIChartBoost ~= nil then


					if MOAIChartBoost.hasCachedInterstitial() then
						print('','AD --> YES')
					else
						F._show_ad_done()
					end
			else
				print('','AD --> NOT FREE')

			end--IF CHARTBOOSt


	end --IF FREE

print('------------------------------------------------')
print('**')	
print('**')		

end






--*************************************************************



function A._enterframe()




while true do



print('RUN',scale_width,pw)





--**********************************************************
local cnt_effect = 0
effect_vbo:setCursorZero()

--**********************************************************



if (keys[32] == true) then

keys[32] = false




--GROUND
if jump_state   == 'ground' then


	if death_cnt == 4 then
	 		dx_speed = 2
		 	dots_points = 0
			death_cnt = 0
			mFramebuffer['prop']:seekColor(1,1,1,1,1,MOAIEaseType.LINEAR)

	else
	 		dx_speed = 2
		 	dots_points = 0
		 	mText['score']:setString(tostring(dots_points))
	end


	
end


if jump_state ~= 'dead' then
    jump_speed   = 5
	jump_state   = 'jumping'
end

--DEAD
if jump_state == 'dead' then
	--bonus_index = 0
	--dx_speed = 2
 	--jump_state   = 'ground'
end








end


--**************************************
--JUMP
if jump_state == 'jumping' then
	    jump_speed   = jump_speed  - 0.2
		if jump_speed < 0 then
			jump_state = 'falling'
			jump_speed = 0
		end
end


--**************************************
--FALL
if jump_state == 'falling' then
	local jSpeed = jump_speed + 0.25
	jump_speed  = jSpeed + (jump_speed*0.05)
end



--**************************************
--MOVE
if jump_state == 'jumping' then
	hero_dy = (jump_speed)*-1
elseif jump_state == 'falling' then
	hero_dy = jump_speed
elseif jump_state == 'ground' then
		hero_dy = 0
elseif jump_state == 'dead' then
		hero_dy = 0
end


--***********************************************************************
--***********************************************************************
--ELSE FULL PATH

if jump_state ~= 'dead' then

	if (jump_state ~= 'ground') then
						hero_x = hero_x + dx_speed
						hero_y = hero_y + hero_dy
	end


--hero_x = hero_x + 2
gTrail[#gTrail+1] = {hero_x,hero_y,0,os.clock(),0}






local xx,yy = mFramebuffer['layer']:worldToWnd(hero_x,hero_y)
local change_dir = false

if xx > 480-32 then

	change_dir = true

end

if xx < 32 then

	change_dir = true

end


if change_dir == true then
	dx_speed = dx_speed * -1




--BONUSE
		bonus_has = true
		bonus_index = bonus_index + 1
		if bonus_index > #bonus_list then
			bonus_index = 1
		end

        bonus_x = bonus_list[bonus_index][1]
        bonus_y = bonus_list[bonus_index][2]
		bonus_time = os.clock()


		--mText['byte']:seekColor(color[1],color[2],color[3],color[4],7,MOAIEaseType.LINEAR)--FADE TO RED
	
end





hero_list = {
--LEFT
{xx-10,yy,xx-9,yy-1},
--RIGHT
{xx+10,yy,xx+9,yy-2},
--UP
{xx,yy-10,xx,yy-9},
--DOWN
{xx,yy+10,xx,yy+9},


}


--LEFT INSIDE
local isLeft  = false
local isRight = false
local isTop   = false
local isDown  = false

for i = 1, #hero_list do
local hero_rect = hero_list[i]
	for j = 1,#box_list do
		local bound_rect = box_list[j]

		--print(hero_rect[1],hero_rect[2],hero_rect[3],hero_rect[4],bound_rect[1],bound_rect[2],bound_rect[3],bound_rect[4])
		if rect_vs_rect(hero_rect[1],hero_rect[2],hero_rect[3],hero_rect[4],bound_rect[1],bound_rect[2],bound_rect[3],bound_rect[4]) then
			if i == 1 then
				isLeft = true
			end

			if i == 2 then
				isRight = true
			end

			if i == 3 then
				isTop = true
			end

			if i == 4 then
				isDown = true
			end

		end
	end
end

--local isLeft  = true
--local isRight = true
--local isTop   = true
--local isDown  = true
--
if isLeft == false or isRight == false or isTop == false or isDown ==false then
	--print('dead')
	gExplode[#gExplode+1] = { hero_x,hero_y,0,os.clock(),0}


     jump_state   	  = 'dead'
  	 bonus_has  	  = false




	

		if isLeft == false then
			false_rect = hero_list[1]
		end

		if isRight == false then
			false_rect = hero_list[2]
		end

		if isTop == false then
			false_rect = hero_list[3]
		end

		if isDown == false then
			false_rect = hero_list[4]
		end

end





--IF DISTANCE TO BOUN
if bonus_has == true then

if make_icon == true then
	bonus_x = 480*.5
	bonus_y = 320*.5
	pw =5
end


if os.clock()- bonus_time > 1 then
		gExplode[#gExplode+1] = { bonus_x,bonus_y,0,os.clock(),2}
		bonus_time = os.clock()
end

--print('bouns true')

					local rot  = rad(0)
					local mCos = cos(rot)
					local pSin = sin(rot)

					--UV
					local ux,uy     = 0.25, 0.25

						cnt_effect=cnt_effect + 1
						effect_vbo:writeGeo(
						--LOC : X,Y,Z
						bonus_x,
						bonus_y,
						0,
						--COLOR : R,G,B,A
						1,
						1,
						0,
						1,
						--SIZE
						24*pw,
						--ROT
						mCos,
						pSin,
						--UV
						ux,
						uy
						)


						cnt_effect=cnt_effect + 1
						effect_vbo:writeGeo(
						--LOC : X,Y,Z
						bonus_x,
						bonus_y,
						0,
						--COLOR : R,G,B,A
						1,
						1,
						0,
						1,
						--SIZE
						24*pw,
						--ROT
						mCos,
						pSin,
						--UV
						ux,
						uy
						)








if bonus_index > 0 then


	if math_getDistance(bonus_x,bonus_y,hero_x,hero_y) < 16 then


		bonus_has = false
		dots_points = dots_points + 1
		mText['score']:setString(tostring(dots_points))
	  	gExplode[#gExplode+1] = { hero_x,hero_y,0,os.clock(),1}



--BEST
	if dots_points > best then
		    best = dots_points
	end
	 mText['best']:setString(tostring(best))



	end

end
end















--****************************************************************************
--HERO



					local rot  = rad(0)
					local mCos = cos(rot)
					local pSin = sin(rot)

					--UV
					local ux,uy     = 0.25, 0.25



						cnt_effect=cnt_effect + 1
						effect_vbo:writeGeo(
						--LOC : X,Y,Z
						hero_x,
						hero_y,
						1,
						--COLOR : R,G,B,A
						0,
						1,
						0,
						1,
						--SIZE
						32*pw,
						--ROT
						mCos,
						pSin,
						--UV
						ux,
						uy
						)


						cnt_effect=cnt_effect + 1
						effect_vbo:writeGeo(
						--LOC : X,Y,Z
						hero_x,
						hero_y,
						0,
						--COLOR : R,G,B,A
						0,
						1,
						0,
						1,
						--SIZE
						32*pw,
						--ROT
						mCos,
						pSin,
						--UV
						ux,
						uy
						)


end --dead















--********************************************************************************
--********************************************************************************
--********************************************************************************
--********************************************************************************
--********************************************************************************
--TRAIL LIST





--print(#gTrail)

local max_trails = #gTrail

for i=max_trails,1,-1 do

local explode = gTrail[i]

local e_x    = explode[1]
local e_y    = explode[2]
local e_rot  = explode[3]
local e_time = explode[4]
local e_type = explode[5]
local finish = 0.5
local end_time   = os.clock() - e_time

if e_x ~= hero_x and e_y ~= hero_y then


--print(i,end_time)

				--UV
				local ux,uy     =  0.25,  0.25


				--RANDOM
				local r,g,b,a  = 0,1,0,1

				if e_type == 1 then
					r,g,b,a  = 1,1,0,1
				end

				--EDN TIME
			


				--ROTATION : SLOW SHOULD HAVE DFEUALT
				local rot  = rad(0)
				local mCos = cos(rot)
				local pSin = sin(rot)

					cnt_effect=cnt_effect + 1
						effect_vbo:writeGeo(
						--LOC : X,Y,Z
						e_x,
						e_y,
						0,
						--COLOR : R,G,B,A
						r,
						g,
						b,
						1/(max_trails-i),
						--SIZE
						32*pw,
						--ROT
						mCos,
						pSin,
						--UV
						ux,
						uy
						)

end
				--*****************************
				-- REMOVE
				if (end_time) > finish then
						table.remove(gTrail,i)
				end




end





--********************************************************************************
--********************************************************************************
--********************************************************************************
--********************************************************************************
--********************************************************************************
--EXPLODE LIST
--RESET THE DEAD
if jump_state == 'dead' and #gTrail == 0 then




--*************************************************************
--FADE OU
if death_cnt == 2 then

			death_cnt = 3

			local function ad_done()
				print('ADD POP')
				death_cnt = 4
				F._show_ad()
				rest_me()
			end

		
			local ad_me = mFramebuffer['prop']:seekColor(0.1,0.1,0.1,0.5,1)
			ad_me:setListener ( MOAIAction.EVENT_STOP, ad_done )
	
		
else

		--IF FREE
		if death_cnt < 2 then

			if system['isFree'] == true then
					death_cnt = death_cnt + 1
			end


			rest_me()
		end
end




	


end

--********************************************************************************
--********************************************************************************
--********************************************************************************
--********************************************************************************
--********************************************************************************





for i=#gExplode,1,-1 do

local explode = gExplode[i]

local e_x    = explode[1]
local e_y    = explode[2]
local e_rot  = explode[3]
local e_time = explode[4]
local e_type = explode[5]
local scale  = 4
local finish = 0.5
local force  = 250
local rings_step = 32


						--UV
								local ux,uy     =  0.25,  0.25


								--RANDOM
								local r,g,b,a  = 0,0,0,0

								if e_type == 0 then

									 r,g,b,a  = 0,1,0,1


								--TREASURE
								elseif e_type == 1 then
									r,g,b,a  = 1,1,0,1



								--HERO
								elseif e_type == 2 then

									r,g,b,a = random(10,255)/255,random(10,255)/255,random(10,255)/255,1
									r,g,b,a = 1,1,0,1
									scale  		= 2
									finish 		= 2
									force  		= 150
									rings_step  = 4
							
								end



								local end_time   = os.clock() - e_time
								local angle      = pi*2 / rings_step
								local angleStep  = 0

								--DISTANCE AND CIRCLE SIZE
								--print('')
								for j = 1, rings_step do


										--ROTATION : SLOW SHOULD HAVE DFEUALT
										local rot  = rad(end_time*250)
										local mCos = cos(rot)
										local pSin = sin(rot)

										--FISTR POINT
										angleStep = angleStep + angle

										local	x = e_x + ( sin ( angleStep )* end_time*force )
										local	y = e_y + ( cos ( angleStep )* end_time*force )


										 if end_time ~= 0 then

												local size = scale/end_time


													if (size > 12)
													and (size < 64)
													then

													--print(#gExplode,j,floor(x),floor(y),floor(size),scale,end_time,math_getDistance(x,y,e_x,e_y),cnt_effect)


													--BUG ON IPHONE-3gs
													if math_getDistance(x,y,e_x,e_y) < 120 then

															--GEO
															cnt_effect = cnt_effect + 1
															effect_vbo:writeGeo(
																	--LOC : X,Y,Z
																	x,
																	y,
																	0,
																	--COLOR : R,G,B,A
																	r,
																	g,
																	b,
																	a,
																	--SIZE
																	size*pw,
																	--ROT
																	mCos,
																	pSin,
																	--UV
																	ux,
																	uy
															);

													end


													end

										end


						end --j

				--*****************************
				-- REMOVE
				if (end_time) > finish then
						table.remove(gExplode,i)
				end



end --END I


				--SET HIGH
				effect_mesh:setHigh(cnt_effect) --BASED ON VERTIXS

--print(cnt_effect)
				--YEILD
  			local delta=	coroutine.yield()
			--print(delta)


		end
end









--****************************************************
function F._func_hero_lock()
	print('>> LOCK HERO STATE')
end
--****************************************************
function F._func_hero_unlock()
print('>> UNLOCK HERO STATE')


end

--****************************************************
--LOAD RESTART

function F._game_restart()

print('>> RESTART GAME')




		--KEYS
		keys[97]   = false
		keys[100]  = false
		keys[119]  = false
		keys[115]  = false

		--VELOCITY
		hero_dx = 0
		hero_dy = 0





	mBombs_alpha = 1

	dots_total   = 0 --TOTAL DOTS
	dots_current = 0 --DOTS CURRENT
	dots_percent = 0 --PERCENTAGE OF DOTS LEFT
	dots_step	 = 0 --RELEASE GHOST STEP
	dots_last	 = 0 --DOTS LAST

	dots_points  = 0
	dots_level   = 1

	game_level   = 1
	game_lives   = 3

	game_speed   = 1
	--game_name    = 'EZRA'

	cycle_time  = os.clock()
	cycle_ticks = 0




--EXPLODE
	for i=#gExplode,1,-1 do
		table.remove(gExplode,i)
	end





	mText['score']:setString(tostring(dots_points))



	rest_me()





end





--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************


function L._load_display()

print('>> LOAD DISPLAY')

realW 		   		= system['SCREEN_W']
realH 		   		= system['SCREEN_H']
halfW     	   		= realW * 0.5
halfH     	   		= realH * 0.5




--VIEWPORT
mFramebuffer['viewport'] = MOAIViewport.new ()
mFramebuffer['viewport']:setSize (0,0,scale_width,scale_height )
mFramebuffer['viewport']:setScale ( scale_width, -scale_height )
mFramebuffer['viewport']:setOffset (  -1,1 )

--LAYER
mFramebuffer['layer'] = MOAILayer2D.new ()
mFramebuffer['layer']:setViewport ( mFramebuffer['viewport'] )

--MOAISim.pushRenderPass ( mFramebuffer['layer'] )





--TEXTURE
	mFramebuffer['texture'] = MOAIFrameBufferTexture.new ()
	mFramebuffer['texture']:init ( scale_width,scale_height )
	mFramebuffer['texture']:setRenderTable ({ mFramebuffer['layer'] })
--RENDER : BUFFER
	MOAIRenderMgr.setBufferTable ({ mFramebuffer['texture'] })




--QUAD
	mFramebuffer['quad'] = MOAIGfxQuad2D.new ()
	mFramebuffer['quad']:setRect ( 0,0,scale_width,scale_height) --6 smaller on the quad
	mFramebuffer['quad']:setTexture(mFramebuffer['texture'])
--	mFramebuffer['quad']:setUVRect ( 0, 0, 1, 1 )



--RENDER : PRO
	mFramebuffer['prop'] = MOAIProp2D.new ()
	mFramebuffer['prop']:setDeck (  mFramebuffer['quad'] )
	mFramebuffer['prop']:setLoc(0,0)
--	mFramebuffer['prop']:setColor(1,0,0,1)







--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************

pw = realW  / 480
ph = halfH / 320 
pw = 1
ph = 1


mViewport['display'] = MOAIViewport.new ()
mViewport['display']:setSize (  realW, realH )
--mViewport['display']:setScale ( scale_width,-scale_height )
mViewport['display']:setScale ( 480,-320 )
mViewport['display']:setOffset (  -1,1 )


mLayer['display'] = MOAILayer2D.new ()
mLayer['display']:setViewport ( mViewport['display'] )
MOAISim.pushRenderPass ( mLayer['display'] )





	--mFramebuffer['layer']:setClearDepth(true)
	--mFramebuffer['layer']:setClearColor()
	--mFramebuffer['texture']:setClearColor()
	--MOAIGfxDevice.getFrameBuffer():setClearColor()



--******************************************************
--ADD BUFFER


if make_icon == false then
		mLayer['display']:insertProp ( mFramebuffer['prop'])
end








--
--		function onDraw ( index, xOff, yOff, xFlip, yFlip )
--
--
--		   MOAIGfxDevice.setPenColor ( 1, 1, 1, 1)
--
--	        for i = 1, #box_list do
--				local rect = box_list[i]
--			--	MOAIDraw.drawRect(rect[1],rect[2],rect[3],rect[4])
--			end
--
--
--	        for i = 1, #hero_list do
--				local rect = hero_list[i]
--			--	MOAIDraw.drawRect(rect[1],rect[2],rect[3],rect[4]*yFlip)
--			end
--
--
--
--			--COLLISON SPOT
--				--MOAIDraw.drawCircle(false_rect[1]-1,false_rect[2]-1,2,30)
--
--
--
--
--
--
----        for i = 1, #bonus_left do
----			MOAIDraw.drawCircle((bonus_left[i][1])-1,(bonus_left[i][2])-1,8,15)
----		end
----
----
----        for i = 1, #bonus_right do
----			MOAIDraw.drawCircle((bonus_right[i][1])-1,(bonus_right[i][2])-1,8,15)
----		end
----
----
----		if  bonus_index   ~= 0 then
----		   MOAIGfxDevice.setPenColor ( 1, 0, 0, 1)
----			MOAIDraw.drawCircle((bonus_list[bonus_index][1])-1,(bonus_list[bonus_index][2])-1,8,15)
----		end
----
----
--
--		
--
--
--
--
--
--
--
--
--
--
--
--
--
--		end
--
--
--
--		local 	sKeyboard_scriptDeck = MOAIScriptDeck.new ()
--		sKeyboard_scriptDeck:setRect ( 0,-160,480,160 )
--		sKeyboard_scriptDeck:setDrawCallback ( onDraw )
--
--
--
--		local   draw_prop = MOAIProp2D.new ()
--		draw_prop:setDeck ( sKeyboard_scriptDeck )
--		draw_prop:setLoc(32,32)
--		mFramebuffer['layer']:insertProp ( draw_prop )
--







end








--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************

function L._load_text()


local charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-'


mFont['sreda'] = MOAIFont.new ()
mFont['sreda']:loadFromTTF  ( system['pathFont']..'/sreda.ttf' , charcodes, 8, 163,32 )
		

		
		
		mText['score'] = MOAITextBox.new ()
		mText['score']:setString ( '0' )
		mText['score'] :setFont ( mFont['sreda'] )
		mText['score'] :setTextSize ( 12, 163 )
		mText['score'] :setRect ( scale_width*.5-50,45,scale_width*.5+50,75+45  )
		mText['score'] :setYFlip ( false )		
		mText['score'] :setLoc (-1,-3)
		

		
		mText['score'] :setPriority(10000)
		mText['score'] :setColor(1,1,0,1)
		mText['score'] :setAlignment ( MOAITextBox.CENTER_JUSTIFY, MOAITextBox.CENTER_JUSTIFY )
		
		



		mText['best'] = MOAITextBox.new ()
		mText['best']:setString ( '0' )
		mText['best'] :setFont ( mFont['sreda'] )
		mText['best'] :setTextSize ( 12, 163 )
		mText['best'] :setRect ( scale_width*.5-50,scale_height-60-32,scale_width*.5+50,scale_height-30-32  )
		mText['best'] :setYFlip ( false )

		mText['best'] :setLoc (-1,-3)


		mText['best'] :setPriority(10000)
		mText['best'] :setColor(1,1,0,1)
		mText['best'] :setAlignment ( MOAITextBox.CENTER_JUSTIFY, MOAITextBox.CENTER_JUSTIFY )








--********************************************************************************************
--********************************************************************************************
--********************************************************************************************



	--TEXTURE
	mTexture['score'] = MOAITexture.new()
	mTexture['score']:setFilter ( MOAITexture.GL_LINEAR ) --smooth
	mTexture['score']:load( system['pathImages']..'//score.png' , MOAIImage.PREMULTIPLY_ALPHA )


	--QUAD
	mQuad['score'] = MOAIGfxQuad2D.new ()
	mQuad['score']:setTexture ( mTexture['score'])
	mQuad['score']:setRect ( -50, -12,50,12 )
	mQuad['score']:setUVRect ( 0, 0, 1, 1 )

	--PROP
	mProp['score'] = MOAIProp.new ()
	mProp['score']:setDeck ( mQuad['score'] )
	mProp['score']:setLoc ( scale_width*.5,24 )
	mProp['score'] :setPriority(10000)
	--mProp['score']:setColor(1,0,1,1)




--********************************************************************************************
--********************************************************************************************
--********************************************************************************************



	--TEXTURE
	mTexture['best'] = MOAITexture.new()
	mTexture['best']:setFilter ( MOAITexture.GL_LINEAR ) --smooth
	mTexture['best']:load( system['pathImages']..'//tap.png' , MOAIImage.PREMULTIPLY_ALPHA )


	--QUAD
	mQuad['best'] = MOAIGfxQuad2D.new ()
	mQuad['best']:setTexture ( mTexture['best'])
	mQuad['best']:setRect ( -50, -12,50,12 )
	mQuad['best']:setUVRect ( 0, 0, 1, 1 )

	--PROP
	mProp['best'] = MOAIProp.new ()
	mProp['best']:setDeck ( mQuad['best'] )
	mProp['best']:setLoc ( scale_width*.5,320-24 )
	mProp['best'] :setPriority(10000)
	--mProp['score']:setColor(1,0,1,1)






if make_icon == false then

	mFramebuffer['layer']:insertProp ( mText['score'] )
		--mLayer['display']:insertProp ( mText['score'] )
	
	mFramebuffer['layer']:insertProp ( mText['best'] )
		--mLayer['display']:insertProp ( mText['best'] )
	
	
	
	mFramebuffer['layer']:insertProp (mProp['best'] )
		--mLayer['display']:insertProp (mProp['best'] )
	
	mFramebuffer['layer']:insertProp (mProp['score'] )
			--mLayer['display']:insertProp (mProp['score'] )


end








end



--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
function L._load_map()

	print('>> LOAD MAP')

local tilemap 		= {}		
local g_map			= {}
local g_grid  		= {}
local g_tileMap 	= {}

	
g_map['width']  = 15
g_map['height'] = 10



tilemap['data'] = dofile(system['pathLevel']..'/map.lua')

for k,v  in pairs(tilemap['data']['layers']) do
	if v['name'] == 'level_1' then tilemap['level_a'] = v['data'] end
end


--TEXTURE
g_grid['texture'] = MOAITexture.new()
g_grid['texture']:setFilter ( MOAITexture.GL_LINEAR ) --smooth
g_grid['texture']:load( system['pathImages']..'//tileset.png'  , MOAIImage.PREMULTIPLY_ALPHA )


--DECK
g_grid['deck'] = MOAITileDeck2D.new ()
g_grid['deck']:setSize ( 8,8 )
g_grid['deck']:setUVRect(-0.5, 0.5, 0.5, -0.5)
g_grid['deck']:setTexture (g_grid['texture']  )






--GRIDES
g_grid['level_a'] = MOAIGrid.new ()
g_grid['level_a']:setSize ( g_map['width'],g_map['height'], 32, 32,0,0 )

--BACK
g_tileMap['level_a'] = MOAIProp2D.new ()
g_tileMap['level_a']:setDeck ( g_grid['deck'] )
g_tileMap['level_a']:setGrid ( g_grid['level_a'] )
g_tileMap['level_a']:setPriority(0)
g_tileMap['level_a']:setColor(1,0,1,1)



if make_icon == false then
	mFramebuffer['layer']:insertProp ( g_tileMap['level_a'] )

end

local cnt = 0
for y = 0,g_map['height']-1 do --Y
			for x = 0,g_map['width']-1 do --X

			        cnt = cnt + 1
					
					local level_a   = tilemap['level_a'][cnt]	

					--LEVEL_A
					g_grid['level_a']:setTile(x+1, y+1, level_a)	


			end --end x

	end --end y

end

--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--START UNZT
function L._load_music()

--		MOAIUntzSystem.initialize (44100,800)
--
--		mUntz['sound'] = MOAIUntzSound.new ()
--		mUntz['sound']:load ( system['pathSounds']..'bg//'..'trance-6.ogg',false )
--		mUntz['sound']:setVolume ( 0.1 )
--		mUntz['sound']:setLooping ( true )
--		mUntz['sound']:play ()


--- ERROR

--		mUntz['fatal_error'] = MOAIUntzSound.new ()
--		mUntz['fatal_error']:load ( system['pathSounds']..'sfx//'..sound_fx..'_fatal_error.ogg',true )
--		mUntz['fatal_error']:setVolume ( 1 )
--		mUntz['fatal_error']:setLooping ( false )




end





--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--EFFECTS


function L._load_effect()

	--COUNT
	local effect_cnt  = 900

	
	
	--FORMATE
	effect_vertexFormat = MOAIVertexFormat.new ()
	effect_vertexFormat:declareCoord(1, MOAIVertexFormat.GL_FLOAT, 3) --LOC X,LOC X
	effect_vertexFormat:declareColor(2, MOAIVertexFormat.GL_UNSIGNED_BYTE)--COLOR
	effect_vertexFormat:declareAttribute(3, MOAIVertexFormat.GL_FLOAT,1) --POINT SIZE
	effect_vertexFormat:declareUV ( 4, MOAIVertexFormat.GL_FLOAT, 2 ) --ROTATION
	effect_vertexFormat:declareUV ( 5, MOAIVertexFormat.GL_FLOAT, 2 ) --UV
	
	
	
	--VBO
	effect_vbo = MOAIVertexBuffer.new ()
	effect_vbo:setFormat ( effect_vertexFormat )
	effect_vbo:reserveVerts ( effect_cnt )
	
	
	
	local cnt_tile 		= 0
	local cnt_effect 	= 0
	
	
	
	--*************************
	--TILE AREA
	for y = 1,30 do
		for x = 1,30 do
		
	
	   				--ROTATION
					local rot  = 0
					local mCos = cos(rot)
					local pSin = sin(rot)
	
					--UV
					local ux,uy     = 0.30, 0.30
	
	
					--INCREASE
					cnt_effect=cnt_effect + 1
					effect_vbo:writeGeo(
									--LOC : X,Y,Z
									x*32-16, --WAV TO SET MAX AND MINUS
									y*32-16,
									0,
									--COLOR : R,G,B,A
									0,
									0,
									0,
									0,
									--SIZE
									16,
									--ROT
									mCos,
									pSin,
									--UV
									ux,
									uy
					)
	
	
		end--end x
	end--end y
	
	
	
	
	
	
	--BLEES
	effect_vbo:bless()
	
	
	--TEXTURE
	mTexture = MOAITexture.new()
	mTexture:setFilter ( MOAITexture.GL_LINEAR ) --smooth
	mTexture:load( system['pathImages']..'//sheet.png' , MOAIImage.PREMULTIPLY_ALPHA )
	
	--MESH
	effect_mesh = MOAIMesh.new ()
	effect_mesh:setVertexBuffer ( effect_vbo )
	effect_mesh:setPrimType ( MOAIMesh.GL_POINTS) --GL_TRIANGLE_STRIP
	effect_mesh:setHigh(0) --BASED ON VERTIXS
	effect_mesh:setTexture (mTexture)
	
	effect_prop = MOAIProp.new ()
	effect_prop:setDeck ( effect_mesh )
	effect_prop:setBlendMode(MOAIProp2D.BLEND_ADD)
	
	
	effect_prop:setShader(mShader['points_effect'])
	
	if make_icon == false then	
		mFramebuffer['layer']:insertProp ( effect_prop)
	else
		mLayer['display']:insertProp ( effect_prop)
	end
	

end









--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
---*********************************************************************
--SNAP SHOT
function F._func_snapshot()
		mLayer['display']:setClearColor(0,0,0,1)

		local img = MOAIImage.new()


		local function write_Image()

				local time = os.time()
				local date = os.date("%Y_%m_%d_%H_%M_%S",time)
				local filename = system['useDir']..system['gameName'].."//app_snapshots//"

				img:writePNG ( system['useDir']..system['gameName'].."//app_snapshots//"..date..".png" )
				img = nil
				mLayer['display']:setClearColor()
		end

		local frameBuffer = MOAIGfxDevice.getFrameBuffer ()
		frameBuffer:grabNextFrame (img, write_Image )
end




--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************

function input.keyboard ( key, down )


keys[key] = down

if down == true then
	if key == 13 then  F._func_snapshot() end
end


end



--******************************************************************************
--******************************************************************************
local isButton = false

function input.touch( eventType, idx, x, y, tapCount )

--EXIT
if y < 50 then
	if tapCount == 3 then
		os.exit()
	end
end

		if eventType == MOAITouchSensor.TOUCH_DOWN then
			keys[32] = true

		elseif eventType == MOAITouchSensor.TOUCH_UP then
		

		elseif eventType == MOAITouchSensor.TOUCH_MOVE  then
			--keys[32] = true

		end


end --END INPUT






--**********************************************************************************
--**********************************************************************************
--**********************************************************************************
--**********************************************************************************
--**********************************************************************************


function L._load_inputs()



    if MOAIEnvironment['devBrand'] == 'OUYA' then

		      --MOAIInputMgr.device.gameButton:setCallback (input.button )
		      --MOAIInputMgr.device.gameAnalog:setCallback (input.analog )
		 	  --MOAIInputMgr.device.keyboard:setCallback ( onKeyboardEvent )

	elseif (MOAIInputMgr.device.pointer) then

			--RESIZE
			MOAIGfxDevice.setListener ( MOAIGfxDevice.EVENT_RESIZE, F._screenSize )

			--KEYBOARD
			MOAIInputMgr.device.keyboard:setCallback ( input.keyboard )

			--MOUSE
			--MOAIInputMgr.device.pointer:setCallback ( input.mouseMove )

			--LEFT_CLICK
			--MOAIInputMgr.device.mouseLeft:setCallback(input.mouseLeft)

			--RIGHT_CLICK
			--MOAIInputMgr.device.mouseRight:setCallback(input.mouseRight)


	else

			--TOUCH SCREEN
				MOAIInputMgr.device.touch:setCallback (input.touch)

			--LEVEL
				--MOAIInputMgr.device.level:setCallback ( input.level )




	end



---***********************
--SET OBJECTS


end








--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
end --END SQUISH FUNCTION
unit_geohop()
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
---shaders.lua


local function unit_shaders()
--local shaders = {}

--sdf

--*****************************************************



local vertex_level = [[

uniform mat4 transform;
attribute vec4  color;
attribute vec4 position;

varying LOWP vec4 colorVarying;

void main () {
gl_Position    = position * transform *vec4(1,-1,1,1);

//	gl_Position    = position * transform;
	colorVarying   = color;
}


]]



local fragment_level = [[
precision mediump float;
uniform vec4 maskcolor;
uniform float dx;
uniform float dy;
varying LOWP vec4 colorVarying;

void main() {
	gl_FragColor = maskcolor;
}

]]





--
--if ii == 1 then MOAIGfxDevice.setPenColor(1,0,0,1) end
--if ii == 2 then MOAIGfxDevice.setPenColor(0,1,0,1) end
--if ii == 3 then MOAIGfxDevice.setPenColor(0,1,1,1) end
--if ii == 4 then MOAIGfxDevice.setPenColor(1,0,1,1) end

--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--RED

mShader['red'] = MOAIShader.new ()
mShader['red']:setVertexAttribute ( 1, 'position' )
mShader['red']:setVertexAttribute ( 2, 'color' )

mShader['red']:reserveUniforms ( 4 )
mShader['red']:declareUniform ( 1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )
mShader['red']:declareUniform  (2, 'maskcolor', MOAIShader.UNIFORM_COLOR)	
mShader['red']:load ( vertex_level, fragment_level )

--COLOR VALUES
local 	mask_red = MOAIColor.new ()
		mask_red:setColor ( 0, 0, 0, 0 )
		mask_red:seekColor ( 0.2, 0, 0, 0.2, 1.5 )

mShader['red']:setAttrLink ( 2, mask_red, MOAIColor.COLOR_TRAIT )





mCurve 	 = {}
mAnimate = {}


--	mCurve['particle']= MOAIAnimCurve.new ()
--	mCurve['particle']:reserveKeys ( 2)
--	mCurve['particle']:setKey ( 1, 0, 0.1,               MOAIEaseType.LINEAR )   --SET
--	mCurve['particle']:setKey ( 2, 5, 0.2,               MOAIEaseType.LINEAR )   --MOVE TO
--
--
--
--	mAnimate['particle']= MOAIAnim.new ()
--	mAnimate['particle']:reserveLinks ( 1 )
--	mAnimate['particle']:setLink ( 1, mCurve['particle'], mask_red, MOAIColor.ATTR_A_COL )
--	mAnimate['particle']:setMode ( MOAITimer.PING_PONG )
--	mAnimate['particle']:setListener(MOAITimer.EVENT_TIMER_END_SPAN,done)
--	mAnimate['particle']:start()
--
--********************************************
--LINE


mShader['red_lines'] = MOAIShader.new ()
mShader['red_lines']:setVertexAttribute ( 1, 'position' )
mShader['red_lines']:setVertexAttribute ( 2, 'color' )

mShader['red_lines']:reserveUniforms ( 4 )
mShader['red_lines']:declareUniform ( 1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )
mShader['red_lines']:declareUniform  (2, 'maskcolor', MOAIShader.UNIFORM_COLOR)	
mShader['red_lines']:load ( vertex_level, fragment_level )



--COLOR VALUES
local 	mask_Lines = MOAIColor.new ()
		mask_Lines:setColor ( 0, 0, 0, 0 )
		mask_Lines:seekColor ( 1, 0, 0, 1, 1.5 )

mShader['red_lines']:setAttrLink ( 2, mask_Lines, MOAIColor.COLOR_TRAIT )







--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--GREEN

mShader['green'] = MOAIShader.new ()
mShader['green']:setVertexAttribute ( 1, 'position' )
mShader['green']:setVertexAttribute ( 2, 'color' )

mShader['green']:reserveUniforms ( 4 )
mShader['green']:declareUniform ( 1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )
mShader['green']:declareUniform  (2, 'maskcolor', MOAIShader.UNIFORM_COLOR)	
mShader['green']:load ( vertex_level, fragment_level  )

--COLOR VALUES
local 	mask_color = MOAIColor.new ()
		mask_color:setColor ( 0, 0, 0, 0 )
		mask_color:seekColor ( .9, 0, 0, 1, 1.5 )

mShader['green']:setAttrLink ( 2, mask_color, MOAIColor.COLOR_TRAIT )



--LINES

mShader['green_lines'] = MOAIShader.new ()
mShader['green_lines']:setVertexAttribute ( 1, 'position' )
mShader['green_lines']:setVertexAttribute ( 2, 'color' )

mShader['green_lines']:reserveUniforms ( 4 )
mShader['green_lines']:declareUniform ( 1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )
mShader['green_lines']:declareUniform  (2, 'maskcolor', MOAIShader.UNIFORM_COLOR)	
mShader['green_lines']:load ( vertex_level, fragment_level )

--COLOR VALUES
local 	mask_color = MOAIColor.new ()
		mask_color:setColor ( 0, 0, 0, 0 )
		mask_color:seekColor ( 0, 1, 0, 1, 1.5 )

mShader['green_lines']:setAttrLink ( 2, mask_color, MOAIColor.COLOR_TRAIT )


--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--PURPLE

mShader['blue'] = MOAIShader.new ()
mShader['blue']:setVertexAttribute ( 1, 'position' )
mShader['blue']:setVertexAttribute ( 2, 'color' )

mShader['blue']:reserveUniforms ( 4 )
mShader['blue']:declareUniform ( 1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )
mShader['blue']:declareUniform  (2, 'maskcolor', MOAIShader.UNIFORM_COLOR)	
mShader['blue']:load ( vertex_level, fragment_level  )

--COLOR VALUES
local 	mask_color = MOAIColor.new ()
		mask_color:setColor ( 0, 0, 0, 0 )
		mask_color:seekColor ( 0, 1, 1, 0.1, 1.5 )

mShader['blue']:setAttrLink ( 2, mask_color, MOAIColor.COLOR_TRAIT )


--****************************
--LINES

mShader['blue_lines'] = MOAIShader.new ()
mShader['blue_lines']:setVertexAttribute ( 1, 'position' )
mShader['blue_lines']:setVertexAttribute ( 2, 'color' )

mShader['blue_lines']:reserveUniforms ( 4 )
mShader['blue_lines']:declareUniform ( 1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )
mShader['blue_lines']:declareUniform  (2, 'maskcolor', MOAIShader.UNIFORM_COLOR)	
mShader['blue_lines']:load ( vertex_level, fragment_level )

--COLOR VALUES
local 	mask_color = MOAIColor.new ()
		mask_color:setColor ( 0, 0, 0, 0 )
		mask_color:seekColor ( 0, 1, 1, 1, 1.5 )

mShader['blue_lines']:setAttrLink ( 2, mask_color, MOAIColor.COLOR_TRAIT )















--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--CIRCLE

local vertex_circle = [[


uniform mat4 transform;

attribute vec4  position;
attribute vec4  color;
attribute float size;
attribute float center;

varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

varying float discard_center;

void main() { 
   colorVarying 		= color;
   gl_PointSize 		= size;
   gl_Position  		= vec4(position.xyz, 1) * transform;
   discard_center       = center;

}
]]



local fragment_circle = [[

precision mediump float;
uniform sampler2D sampler;

varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;
varying float discard_center;

void main() {



float border = 0.05;
float radius = 0.5;
vec4 color0 = vec4(0.0, 0.0, 0.0, 0.0);
vec4 color1 = vec4(colorVarying[0], colorVarying[1], colorVarying[2], 1);

vec2 m 		= gl_PointCoord.xy - vec2(0.5, 0.5);
float dist  = radius - sqrt(m.x * m.x + m.y * m.y);

float t = 0.0;


if (dist > 0.2)
	t = 0;
else if (dist > 0.05)
	t = 1;
else if (dist > 0.0)
	t = dist / 0.05;

 gl_FragColor = mix(color0, color1, t);

}
]]




--
--float dist = distance(gl_PointCoord, vec2(0.5, 0.5));
--
--    if(dist >= 0.5) 
--       discard;	
--	else if (dist < 0.45) 
--		discard;
--
-- gl_FragColor = colorVarying;
--
--

--float border = 0.05;
--float radius = 0.5;
--vec4 color0 = vec4(0.0, 0.0, 0.0, 0.0);
--vec4 color1 = vec4(colorVarying[0], colorVarying[1], colorVarying[2], 1);
--
--vec2 m 		= gl_PointCoord.xy - vec2(0.5, 0.5);
--float dist  = radius - sqrt(m.x * m.x + m.y * m.y);
--
--
--
--
--if (dist > 0.05)
--	t = 1.0;
--else if (dist > 0.0)
--	t = dist / 0.05;
--
-- gl_FragColor = mix(color0, color1, t);
--
--




--float dist =  sqrt(dot(uv, uv));
--  if ( (dist > (circle_radius+border)) || (dist < (circle_radius-border)) )
--    gl_FragColor = bkg_color;
--  else 
--    gl_FragColor = circle_color;


--float dist = distance(gl_PointCoord, vec2(0.5, 0.5));
--    if(dist >= 0.5) {
--        discard;
--}



    		--float dist = distance(fPosition, vec2(-0.50 + col, 0.50 - row));
            --float delta = 0.1;
            --float alpha = smoothstep(0.45-delta, 0.45, dist);
            --fColor = mix(colors[row*2+col], fColor, alpha);





--- Shader
mShader['circle'] = MOAIShader.new ()
mShader['circle']:reserveUniforms(1)
mShader['circle']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX
mShader['circle']:setVertexAttribute ( 1, 'position' )
mShader['circle']:setVertexAttribute ( 2, 'color' )
mShader['circle']:setVertexAttribute ( 3, 'size' )
mShader['circle']:setVertexAttribute ( 4, 'center' )
mShader['circle']:load(vertex_circle, fragment_circle)









--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--*************************************************************************************************
--GAUSE


local vertex_gause = [[

attribute vec4 position;
attribute vec2 uv;
attribute vec4 color;


varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

void main(void)
{
 
	gl_Position  = position;
	uvVarying 	 = uv;
	colorVarying = color;

}

]]





local fragment_gause = [[



uniform sampler2D 	tex;


varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;


const float sampleDist = 2.0;
const float sampleStrength = 3.5; 
float samples[3];


void main(void)
{

 

    samples[0] = -0.02;
    samples[1] = -0.04;
	//samples[2] = -0.06;	

	
	vec2 dir 	= 0.5 - uvVarying;
	float dist 	= sqrt(dir.x*dir.x + dir.y*dir.y);
	dir 		= dir/dist;

    vec4 color = texture2D(tex,uvVarying); 

     vec4 sum = color;

	 sum += texture2D( tex, uvVarying + dir * samples[0] * sampleDist );
	 sum += texture2D( tex, uvVarying + dir * samples[1] * sampleDist );
	// sum += texture2D( tex, uvVarying + dir * samples[2] * sampleDist );
		
sum *= 0.25;


float t = dist * sampleStrength;
t = clamp( t ,0.0,1.0);

gl_FragColor = mix( color, sum, t );
gl_FragColor += texture2D(tex, uvVarying);





}

]]




mShader['gause'] = MOAIShader.new ()
mShader['gause']:setVertexAttribute ( 1, 'position' )
mShader['gause']:setVertexAttribute ( 2, 'uv' )
mShader['gause']:setVertexAttribute ( 3, 'color' )
mShader['gause']:load ( vertex_gause, fragment_gause )




--****************************************************************************
--****************************************************************************
--****************************************************************************
--****************************************************************************
--****************************************************************************
--****************************************************************************
--BLUER
local vertex_blur = [[ 
 

attribute vec4 position;  //IN
attribute vec2 uv;        //IN
attribute vec4 color;

uniform float dx;
uniform float dy;

varying vec2  v_texCoord;          //OUT
varying vec2  v_blurTexCoords;  //OUT				
varying vec4 colorVarying;

	void main()
	{



	
			gl_Position = position;				
			v_texCoord  = uv;    
			colorVarying = color;


		
			v_blurTexCoords = v_texCoord + vec2(dx,  dy);

			//v_blurTexCoords[ 1] = v_texCoord + vec2(dx*0.002,  dy*0.002);
	
	}

  ]]

 

local fragment_blur = [[ 


uniform sampler2D s_texture; 

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords;

varying LOWP vec4 colorVarying;

void main()

{ 


   
//if(colorVarying.a <= .1) discard; 



gl_FragColor = texture2D(s_texture, v_blurTexCoords)        *0.2;
//gl_FragColor = texture2D(s_texture, v_blurTexCoords)   *0.2;
gl_FragColor += texture2D(s_texture, v_texCoord);





}
 

]]



mShader['blur'] = MOAIShader.new ()
mShader['blur']:setVertexAttribute ( 1, 'position' )
mShader['blur']:setVertexAttribute ( 2, 'uv' )
mShader['blur']:setVertexAttribute ( 3, 'color' )

mShader['blur']:reserveUniforms ( 2 )
mShader['blur']:declareUniformFloat ( 1, 'dx',20*0.001 )
mShader['blur']:declareUniformFloat ( 2, 'dy',20*0.001 )
mShader['blur']:load ( vertex_blur, fragment_blur )











--****************************************************************************
--****************************************************************************
--****************************************************************************
--****************************************************************************
--****************************************************************************
--****************************************************************************
--NEON
local vertex_neon = [[ 
 

attribute vec4 position;  //IN
attribute vec2 uv;        //IN
attribute vec4 color;


varying vec2  v_texCoord;          //OUT				
varying vec4  colorVarying; //OUT
varying vec2  v_blurTexCoords[7];//OUT

	void main()
	{

	


			gl_Position = position;				
			v_texCoord  = uv;    
			colorVarying = color;


 
	vec2 singleStepOffset = vec2(0.004, 0.004);
	v_blurTexCoords[0] = v_texCoord.xy;

	v_blurTexCoords[1] = v_texCoord.xy + singleStepOffset * 1.407333;
	v_blurTexCoords[2] = v_texCoord.xy - singleStepOffset * 1.407333;

	v_blurTexCoords[3] = v_texCoord.xy + singleStepOffset * 3.294215;
	v_blurTexCoords[4] = v_texCoord.xy - singleStepOffset * 3.294215;

	v_blurTexCoords[5] = v_texCoord.xy + singleStepOffset * 5.294215;
	v_blurTexCoords[6] = v_texCoord.xy - singleStepOffset * 5.294215;




	}

  ]]

 

local fragment_neon = [[ 


uniform sampler2D s_texture; 
varying vec2  v_blurTexCoords[7];//IN
varying vec2 v_texCoord;

varying LOWP vec4 colorVarying;

void main()

{ 

	lowp vec4 sum = vec4(0.0);
	sum += texture2D(s_texture, v_blurTexCoords[0]) * 0.204164;

	sum += texture2D(s_texture, v_blurTexCoords[1]) * 0.304005;
	sum += texture2D(s_texture, v_blurTexCoords[2]) * 0.304005;

	sum += texture2D(s_texture, v_blurTexCoords[3]) * 0.093913;
	sum += texture2D(s_texture, v_blurTexCoords[4]) * 0.093913;


	sum += texture2D(s_texture, v_blurTexCoords[5]) * 0.043913;
	sum += texture2D(s_texture, v_blurTexCoords[6]) * 0.043913;

	
gl_FragColor = sum;
	gl_FragColor += texture2D(s_texture, v_texCoord);


}
 

]]



mShader['neon'] = MOAIShader.new ()
mShader['neon']:setVertexAttribute ( 1, 'position' )
mShader['neon']:setVertexAttribute ( 2, 'uv' )
mShader['neon']:setVertexAttribute ( 3, 'color' )
mShader['neon']:load ( vertex_neon, fragment_neon )

--*****************************************************************************



--BLUER
local vertex_blur = [[ 
 

attribute vec4 position;  //IN
attribute vec2 uv;        //IN
attribute vec4 color;

uniform float dx;
uniform float dy;

varying vec2  v_texCoord;          //OUT
varying vec2  v_blurTexCoords[14];  //OUT				
varying vec4 colorVarying;

	void main()
	{



	
			gl_Position = position;				
			v_texCoord  = uv;    
			colorVarying = color;

  
    v_blurTexCoords[0] = v_texCoord + vec2(0.0, -0.028);
    v_blurTexCoords[1] = v_texCoord + vec2(0.0, -0.024);
    v_blurTexCoords[2] = v_texCoord + vec2(0.0, -0.020);
    v_blurTexCoords[3] = v_texCoord + vec2(0.0, -0.016);
    v_blurTexCoords[4] = v_texCoord + vec2(0.0, -0.012);
    v_blurTexCoords[5] = v_texCoord + vec2(0.0, -0.008);
    v_blurTexCoords[6] = v_texCoord + vec2(0.0, -0.004);
    v_blurTexCoords[7] = v_texCoord + vec2(0.0,  0.004);








		
	
	}

  ]]

 

local fragment_blur = [[ 


uniform sampler2D s_texture; 

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[14];

varying LOWP vec4 colorVarying;

void main()

{ 




	gl_FragColor = vec4(0.0);
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 0])*0.044299121055113265;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 1])*0.0895781211794;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 2])*0.215963866053;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 3])*0.443683338718;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 4])*0.776744219933;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 5])*0.115876621105;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 6])*0.147308056121;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 7])*0.147308056121;


//gl_FragColor += texture2D(s_texture, v_texCoord); //BASE





}
 

]]



mShader['blur'] = MOAIShader.new ()
mShader['blur']:setVertexAttribute ( 1, 'position' )
mShader['blur']:setVertexAttribute ( 2, 'uv' )
mShader['blur']:setVertexAttribute ( 3, 'color' )

mShader['blur']:reserveUniforms ( 2 )
mShader['blur']:declareUniformFloat ( 1, 'dx',20*0.001 )
mShader['blur']:declareUniformFloat ( 2, 'dy',20*0.001 )
mShader['blur']:load ( vertex_blur, fragment_blur )




--*****************************************************************************
--POINTS : NORMAL
local vertex_points = [[


uniform mat4 transform;

attribute vec4 position;
attribute vec4 color;
attribute float size;

varying vec4 colorVarying;

void main() {

   colorVarying = color;
   gl_PointSize = size;
   gl_Position = vec4(position.xyz, 1) * transform *vec4(1,-1,1,1);

}



  ]]



local fragment_points = [[


uniform sampler2D sampler;
varying vec4 colorVarying;
uniform vec4      maskColor;
void main() {


    gl_FragColor =  texture2D(sampler, gl_PointCoord)*colorVarying;
	//gl_FragColor =colorVarying;
}




]]



mShader['points'] = MOAIShader.new ()

mShader['points']:reserveUniforms(1)
mShader['points']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX
mShader['points']:setVertexAttribute ( 1, 'position' )
mShader['points']:setVertexAttribute ( 2, 'color' )
mShader['points']:setVertexAttribute ( 3, 'size' )
mShader['points']:load(vertex_points, fragment_points)




--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : LEVEL RED


local vertex_level_red = [[

precision mediump float;
uniform mat4 transform;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

void main() {

   colorVarying  = color;
   uvVarying     = uv;
   gl_PointSize  = size;
   gl_Position   = vec4(position.xyz, 1) * transform *vec4(1.0,-1.0,1.0,1.0);






}



  ]]



local fragment_level_red = [[

precision mediump float;

varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

uniform sampler2D sampler;


void main() {


//** 4 X 4
//** vec2(0.25,0.25) : scale * quarter
//** point * scale + offset
//** mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.25,0.25)+vec2(0.75,0.00);
//** gl_FragColor  		  = texture2D(sampler, realTexCoord);


		mediump vec2 realTexCoord =  vec2(0.125,0.125)*gl_PointCoord+uvVarying;
	    gl_FragColor  		      = texture2D(sampler, realTexCoord)*vec4(1,0,0,1);


}




]]



mShader['level_red'] = MOAIShader.new ()

mShader['level_red']:reserveUniforms(1)
mShader['level_red']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX

mShader['level_red']:setVertexAttribute ( 1, 'position' )
mShader['level_red']:setVertexAttribute ( 2, 'size' )
mShader['level_red']:setVertexAttribute ( 3, 'uv' )

mShader['level_red']:load(vertex_level_red, fragment_level_red)




--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : LEVEL RED


local vertex_level_green = [[


uniform mat4 transform;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

void main() {

   colorVarying  = color;
   uvVarying     = uv;
   gl_PointSize  = size;
   gl_Position   = vec4(position.xyz, 1) * transform *vec4(1,-1,1,1);






}



  ]]



local fragment_level_green = [[



varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

uniform sampler2D sampler;


void main() {


//** 4 X 4
//** vec2(0.25,0.25) : scale * quarter
//** point * scale + offset
//** mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.25,0.25)+vec2(0.75,0.00);
//** gl_FragColor  		  = texture2D(sampler, realTexCoord);


		mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.125,0.125)+uvVarying;
	    gl_FragColor  		  = texture2D(sampler, realTexCoord)*vec4(0,1,0,1);


}




]]



mShader['level_green'] = MOAIShader.new ()

mShader['level_green']:reserveUniforms(1)
mShader['level_green']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX

mShader['level_green']:setVertexAttribute ( 1, 'position' )
mShader['level_green']:setVertexAttribute ( 2, 'size' )
mShader['level_green']:setVertexAttribute ( 3, 'uv' )

mShader['level_green']:load(vertex_level_green, fragment_level_green)



--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : LEVEL BLUE


local vertex_level_blue = [[


uniform mat4 transform;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

void main() {

   colorVarying  = color;
   uvVarying     = uv;
   gl_PointSize  = size;
   gl_Position   = vec4(position.xyz, 1) * transform *vec4(1,-1,1,1);






}



  ]]



local fragment_level_blue = [[



varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

uniform sampler2D sampler;


void main() {


//** 4 X 4
//** vec2(0.25,0.25) : scale * quarter
//** point * scale + offset
//** mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.25,0.25)+vec2(0.75,0.00);
//** gl_FragColor  		  = texture2D(sampler, realTexCoord);


		mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.125,0.125)+uvVarying;
	    gl_FragColor  		  = texture2D(sampler, realTexCoord)*vec4(0,1,1,1);


}




]]



mShader['level_blue'] = MOAIShader.new ()

mShader['level_blue']:reserveUniforms(1)
mShader['level_blue']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX

mShader['level_blue']:setVertexAttribute ( 1, 'position' )
mShader['level_blue']:setVertexAttribute ( 2, 'size' )
mShader['level_blue']:setVertexAttribute ( 3, 'uv' )

mShader['level_blue']:load(vertex_level_blue, fragment_level_blue)




--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : LEVEL Purple


local vertex_level_purple = [[


uniform mat4 transform;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

void main() {

   colorVarying  = color;
   uvVarying     = uv;
   gl_PointSize  = size;
   gl_Position   = vec4(position.xyz, 1) * transform *vec4(1,-1,1,1);






}



  ]]



local fragment_level_purple = [[



varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

uniform sampler2D sampler;


void main() {


//** 4 X 4
//** vec2(0.25,0.25) : scale * quarter
//** point * scale + offset
//** mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.25,0.25)+vec2(0.75,0.00);
//** gl_FragColor  		  = texture2D(sampler, realTexCoord);


		mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.125,0.125)+uvVarying;
	    gl_FragColor  		  = texture2D(sampler, realTexCoord)*vec4(1,0,1,1);


}




]]



mShader['level_purple'] = MOAIShader.new ()

mShader['level_purple']:reserveUniforms(1)
mShader['level_purple']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX

mShader['level_purple']:setVertexAttribute ( 1, 'position' )
mShader['level_purple']:setVertexAttribute ( 2, 'size' )
mShader['level_purple']:setVertexAttribute ( 3, 'uv' )

mShader['level_purple']:load(vertex_level_purple, fragment_level_purple)






--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : ROTATE



local vertex_points = [[


uniform mat4 transform;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

attribute vec2 aRotation;


varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

varying mat2 vRotation;




	void main () {
	   colorVarying = color;
	   gl_PointSize = size;
	   uvVarying   = uv;
	   gl_Position  = vec4(position.xyz, 1) * transform*vec4(1,-1,1,1);
  	   vRotation    = mat2(aRotation[0],-aRotation[1],aRotation[1],aRotation[0]);
	}




]]



local fragment_points = [[


varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;
varying highp mat2 vRotation;

uniform sampler2D sampler;



void main() {


//highp mat2 rotation = mat2(cos(5.0), sin(5.0),-sin(5.0), cos(5.0));
//highp mat2 rotation = mat2(0.5,-0.5,0.5,0.5);
//highp mat2 rotation = vRotation;
//centeredPoint = vRotation * centeredPoint;
//GOOD SINGLE SPRITE
//highp vec2 center 		= vec2(0.5,0.5); //CENTER
//highp vec2 centeredPoint 	= (gl_PointCoord - center);
//gl_FragColor 				= texture2D(sampler, (vRotation * centeredPoint) + center)*colorVarying;
//TOP LEFT // GET TEXTURE
//START CORD + TO CORDS * sections
//mediump vec2 realTexCoord = vec2(0,0.5) + (gl_PointCoord)*vec2(0.5,0.5);
//gl_FragColor = texture2D(sampler, realTexCoord);
// DOING THE MATH OR SPERATE DRAW
//GOOD SINGLE SPRITE
//DON'T THINK THIS CAN BE DONE
//+ 0.00,	0.00 square
//+ 0.25,	0.00 triangle
//+ 0.00,	0.25 rect
//+ 0.25,	0.25 cirlce
//gl_FragColor 				= texture2D(sampler, vec2(-0.30,0.30)+((vRotation * centeredPoint) + center))*colorVarying; //CHANGE CENTER BY PLUS OR MINUE



//*******************************************************************************
//*******************************************************************************
//*******************************************************************************
//*******************************************************************************


// 1 : -0.30,-0.30
// 2 : 0.30,-0.30
// 3 : -0.30,0.30
// 4 :  0.30,0.30




highp vec2 center			= vec2(0.5,0.5);
highp vec2 centeredPoint 	= (gl_PointCoord-center)*vec2(0.5,0.5);
gl_FragColor 				= texture2D(sampler, uvVarying+((vRotation * centeredPoint) + center))*colorVarying; //CHANGE CENTER BY PLUS OR MINUES

		//mediump vec2 realTexCoord =  (gl_PointCoord)*vec2(0.125,0.125)+uvVarying;
	    //gl_FragColor  		  = texture2D(sampler, realTexCoord)*vec4(1,0,1,1);







}



]]




mShader['points_rot'] = MOAIShader.new ()
mShader['points_rot']:reserveUniforms(1)
mShader['points_rot']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX
mShader['points_rot']:setVertexAttribute ( 1, 'position' )
mShader['points_rot']:setVertexAttribute ( 2, 'color' )
mShader['points_rot']:setVertexAttribute ( 3, 'size' )
mShader['points_rot'] :setVertexAttribute ( 4, 'aRotation' )
mShader['points_rot'] :setVertexAttribute ( 5, 'uv' )
mShader['points_rot']:load(vertex_points, fragment_points)












--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : EFFECTS


	--TRANSFROM
		mTransform = {}
		mTransform['scale'] = MOAITransform.new ()
		mTransform['scale']:setScl(1,1,1) --SET DARK



local vertex_effects = [[


uniform mat4 transform;
uniform float Scale;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

attribute vec2 aRotation;


varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

varying mat2 vRotation;




	void main () {
	   colorVarying = color;
	   gl_PointSize = size*Scale-6.0;
	   uvVarying    = uv;
	   gl_Position  = vec4(position.xyz, 1) * transform*vec4(1,1,1,1);
 	   vRotation    = mat2(aRotation[0],-aRotation[1],aRotation[1],aRotation[0]);
	}







]]



local fragment_effects = [[


varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;
varying highp mat2 vRotation;

uniform sampler2D sampler;



void main() {

	
	//highp vec2 center			= vec2(0.5,0.5);
	//highp vec2 centeredPoint 	= (gl_PointCoord-center)*vec2(0.5,0.5);
	//gl_FragColor 				= texture2D(sampler, uvVarying+((vRotation * centeredPoint) + center))*colorVarying; 

	gl_FragColor 				= texture2D(sampler, gl_PointCoord )*colorVarying; 








}



]]




mShader['points_effect'] = MOAIShader.new ()
mShader['points_effect']:reserveUniforms(2)
mShader['points_effect']:declareUniform(1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX

mShader['points_effect']:declareUniformFloat  (2, 'Scale'		, MOAIShader.UNIFORM_FLOAT )
mShader['points_effect'] :setAttrLink (2, mTransform['scale'], MOAITransform.ATTR_X_SCL ) --ATTACH ALPHA FROM COLOR


mShader['points_effect']:setVertexAttribute ( 1, 'position' )
mShader['points_effect']:setVertexAttribute ( 2, 'color' )
mShader['points_effect']:setVertexAttribute ( 3, 'size' )
mShader['points_effect'] :setVertexAttribute ( 4, 'aRotation' )
mShader['points_effect'] :setVertexAttribute ( 5, 'uv' )
mShader['points_effect']:load(vertex_effects, fragment_effects)







--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--level





local vertex_level = [[


precision highp float;


uniform mat4 transform;
uniform highp float  Scale;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

varying vec4 colorVarying;
varying MEDP vec2 uvVarying;

void main() {

   colorVarying  = color;
   uvVarying     = uv;
   gl_PointSize  = size;
   gl_Position   = (vec4(position.xyz, 1) * transform)*vec4(1,-1,1,1);

}


]]



--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--BUG
print('SHIT')
if system['osType']  == 'android' then

--		vertex_level = [[
--
--
--		precision highp float;
--
--
--		uniform mat4 transform;
--		uniform highp float  Scale;
--
--		attribute vec4  position;
--		attribute vec4  color;
--		attribute vec2  uv;
--		attribute float size;
--
--		varying vec4 colorVarying;
--		varying MEDP vec2 uvVarying;
--
--		void main() {
--
--		   colorVarying  = color;
--		   uvVarying     = uv;
--		   gl_PointSize  = size*Scale;
--		     gl_Position  = vec4(position.xyz, 1) * transform*vec4(1,-1,1,1);
--
--		}
--
--
--		]]


end

--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************







local fragment_level = [[

precision highp float;

varying LOWP vec4 colorVarying;
varying MEDP vec2 uvVarying;

uniform sampler2D sampler;
uniform vec4 maskColor;


void main() {


		mediump vec2 realTexCoord 	= (gl_PointCoord)*vec2(0.125,0.125)+uvVarying;
	    gl_FragColor  		  		= texture2D(sampler, realTexCoord)*maskColor;


}




]]





mShader['level'] = MOAIShader.new ()
mShader['level']:reserveUniforms(3)
mShader['level']:declareUniform		  (1, 'transform'	, MOAIShader.UNIFORM_VIEW_PROJ) --MATRIX
mShader['level']:declareUniform 	  (2, 'maskColor'	, MOAIShader.UNIFORM_COLOR )
mShader['level']:declareUniformFloat  (3, 'Scale'		, MOAIShader.UNIFORM_FLOAT )

	--COLOR
		mColor['level'] = MOAIColor.new ()
		mColor['level']:setColor ( 0, 0, 0, 0 ) --SET DARK
		mColor['level']:seekColor(1,0,1,1,0.3,MOAIEaseType.LINEAR)  --FADE IN






	--LINK
		mShader['level'] :setAttrLink (2, mColor['level'], MOAIColor.COLOR_TRAIT ) --ATTACH ALPHA FROM COLOR
		mShader['level'] :setAttrLink (3, mTransform['scale'], MOAITransform.ATTR_X_SCL ) --ATTACH ALPHA FROM COLOR





mShader['level']:setVertexAttribute ( 1, 'position' )
mShader['level']:setVertexAttribute ( 2, 'size' )
mShader['level']:setVertexAttribute ( 3, 'uv' )

mShader['level']:load(vertex_level, fragment_level)











--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--POINTS : DOTS



local vertex_dots = [[


uniform mat4 transform;
uniform float Scale;

attribute vec4  position;
attribute vec4  color;
attribute vec2  uv;
attribute float size;

attribute vec2 aRotation;

varying vec4 colorVarying;
varying MEDP vec2 uvVarying;
varying mat2 vRotation;




	void main () {
	   colorVarying = color;
	   gl_PointSize = size*Scale-4.0;
	   uvVarying    = uv;
	   gl_Position  = vec4(position.xyz, 1) * transform*vec4(1,-1,1,1);
  	   vRotation    = mat2(aRotation[0],-aRotation[1],aRotation[1],aRotation[0]);
	}




]]



local fragment_dots = [[


varying LOWP vec4 colorVarying;


varying MEDP vec2 uvVarying;
varying highp mat2 vRotation;

uniform sampler2D sampler;
uniform  float maskColor;


void main() {


//highp vec2 center			= vec2(0.5,0.5);
//highp vec2 centeredPoint 	= (gl_PointCoord-center)*vec2(0.5,0.5);
//gl_FragColor 				= texture2D(sampler, uvVarying+((vRotation * centeredPoint) + center))*vec4(colorVarying.r,colorVarying.g,colorVarying.b,maskColor); 

	gl_FragColor 				= texture2D(sampler, gl_PointCoord )*colorVarying; 





}



]]



--COLOR
mColor['points_dots'] = MOAIColor.new ()
mColor['points_dots']:setColor ( 0, 0, 0, 0 ) --SET DARK
mColor['points_dots']:seekColor(0,0,0,1,0.3,MOAIEaseType.LINEAR)  --FADE IN



mShader['points_dots'] = MOAIShader.new ()
mShader['points_dots']:reserveUniforms(3)


--UNIFORM
mShader['points_dots']:declareUniform(		1, 'transform', MOAIShader.UNIFORM_VIEW_PROJ)

mShader['points_dots'] :declareUniform ( 	2, 'maskColor', MOAIShader.UNIFORM_FLOAT,1 ) 		
mShader['points_dots'] :setAttrLink ( 		2,  mColor['points_dots'], MOAIColor.ATTR_A_COL ) --ATTACH ALPHA FROM COLOR

mShader['points_dots']:declareUniformFloat  (3, 'Scale'		, MOAIShader.UNIFORM_FLOAT )
mShader['points_dots'] :setAttrLink (3, mTransform['scale'], MOAITransform.ATTR_X_SCL ) --ATTACH ALPHA FROM COLOR




mShader['points_dots']:setVertexAttribute ( 1, 'position' )
mShader['points_dots']:setVertexAttribute ( 2, 'color' )
mShader['points_dots']:setVertexAttribute ( 3, 'size' )
mShader['points_dots']:setVertexAttribute ( 4, 'aRotation' )
mShader['points_dots']:setVertexAttribute ( 5, 'uv' )

mShader['points_dots']:load(vertex_dots, fragment_dots)






--*************************************************************

--return mShader
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
end --END SQUISH FUNCTION
unit_shaders()
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
---system.lua


local function unit_system()
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--SYSTEM
--as
--system = {}


system['isFree'] 			= false --NEED TO BE A HOST CALL


system['useResource'] 	    = false
system['useStandAlone'] 	= false
system['useAtlas'] 			= true


--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************

system['isPC'] = false;





if (MOAIEnvironment['osBrand'] == 'Windows') then


			system['isPC'] 					= true;

			system['osType']   				= 'windows'

			system['gameDirectory'] 		= MOAIFileSystem.getWorkingDirectory()


--set cache directories
			system['baseDirectory'] 		= string.gsub(system['gameDirectory'], '/game/lua/', "/")  --back 2 directories
			system['documentsDirectory'] 	= system['baseDirectory']..'_system//windows_documents'
			system['cacheDirectory'] 		= system['baseDirectory']..'_system//windows_cache'
	 		system['resourceDirectory']  	= system['gameDirectory']


elseif (MOAIEnvironment['osBrand'] == 'OSX') and (MOAIEnvironment.OS_BRAND_OSX) then


			system['isPC'] 					= true;

			system['osType']   				= 'osx'

			system['gameDirectory'] 	  	= MOAIFileSystem.getWorkingDirectory()


--set cache directories
			system['baseDirectory'] 	  	= string.gsub(system['gameDirectory'], '/game/lua/', "/") --back 2 directories
			system['documentsDirectory'] 	= system['baseDirectory']..'_system//osx_documents'
			system['cacheDirectory'] 	  	= system['baseDirectory']..'_system//osx_cache'
	 		system['resourceDirectory']  	= system['gameDirectory']


elseif (MOAIEnvironment['osBrand'] == 'iOS') and (MOAIEnvironment.OS_BRAND_IOS) then




print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>IOS")

				system['isPC'] 				 = false;

				system['osType']   			 = 'ios'

		        system['gameDirectory'] 	 = MOAIFileSystem.getWorkingDirectory()
				system['documentsDirectory'] = MOAIEnvironment.documentDirectory
				system['cacheDirectory'] 	 = MOAIEnvironment.cacheDirectory
		 		system['resourceDirectory']  = MOAIEnvironment.resourceDirectory




elseif (MOAIEnvironment['osBrand'] == 'Android') then


			system['isPC'] 				 = false;


			--*************************************
			--ANDROID SOESN"T HAVE A CACHE
			system['osType']   				= 'android'

			--system['gameDirectory'] = MOAIEnvironment.resourceDirectory
			system['gameDirectory'] 	  	= MOAIFileSystem.getWorkingDirectory()
			system['documentsDirectory'] 	= MOAIEnvironment.documentDirectory
			system['cacheDirectory'] 	  	= MOAIEnvironment.documentDirectory
			system['resourceDirectory']  	= MOAIEnvironment.resourceDirectory

elseif (MOAIEnvironment['osBrand'] == 'HTML') then



--HTML HOST

			system['isPC'] 					= true

			system['isWIndow'] 				= true

			system['osType']   				= 'HTML'

			system['gameDirectory'] 		= MOAIFileSystem.getWorkingDirectory()


--set cache directories
			system['baseDirectory'] 		= string.gsub(system['gameDirectory'], '/game/lua/', "/")  --back 2 directories
			system['documentsDirectory'] 	= system['baseDirectory']..'_system//windows_documents'
			system['cacheDirectory'] 		= system['baseDirectory']..'_system//windows_cache'
	 		system['resourceDirectory']  	= system['gameDirectory']



end



--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--SET WINDOW : FOR PC
if 	system['isPC'] == true then
		MOAISim.openWindow ( '',  1280,720 )

--
--		MOAISim.setStep ( 1 / 60 )
--		MOAISim.clearLoopFlags ()
--		MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_ALLOW_BOOST )
--		MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_LONG_DELAY )
--		MOAISim.setBoostThreshold ( 0 )
end



--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--SET : RES
		system['SCREEN_W'] = MOAIEnvironment['horizontalResolution']
		system['SCREEN_H'] = MOAIEnvironment['verticalResolution']


--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--SET JSON
		system['baseEncode'] = MOAIDataBuffer['base64Encode']
		system['baseDecode'] = MOAIDataBuffer['base64Decode']
		system['jsonEncode'] = MOAIJsonParser['encode']
		system['jsonDecode'] = MOAIJsonParser['decode']		



--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--OUYA GAME PAD

 if MOAIEnvironment.devBrand == 'OUYA' then
    		system['gamepad'] = true
 else
    		system['gamepad'] = false
 end



--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************


system['screenRes'] = {

					--	{'default'	,800,600},
						
						---
						--{'icon',1024,1024},
						--{'icon',960,640},						
						--{'icon',1136,600},
						--{'icon',1024,768},
						
						
						
						
						
						--{'youtube'	,1280,720},
						{'iphone'	,480,320},
					--	{'iphone4'	,960,640},
						--{'ipad'		,1024,768},
						--{'ipad2'	,2048,1536},
						--{'macBook1'	,1366,768},
						--{'macBook2'	,1440,900},
						--{'macBookR'	,2560,1600},
						{'htc'		,320,240},
						{'htc'		,480,320},
						{'htc'		,800,480},
						
						{'htc'		,800,600},
						--{'htc'		,960,540},
						--{'one'		,1920,1080},
					--	{'galaxyS2'	,800,480},
						--{'galaxyS3'	,1280,720},
						--{'note'		,1280,800 },
						--{'note2'	,1280,720},
						--{'note10'	,1280,800},
						--{'nexuse10'	,2560,1600},

				}



system['screenCur'] = 1












--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************


--if 	system['isPC'] ~= true then

system['useDir'] 		=   system['cacheDirectory']
system['gameName'] 		= '//geohop'


--else
--
--system['useDir'] 		=  system['gameDirectory']
--system['gameName'] 		= 'vs'
--
--end
--




--OVERRIDES : FOR STANDALONE

--******************
--IFDEF_STANDALONE--
system["useDir"] 		=  system["gameDirectory"]
system["gameName"] 	= ""
--******************




--NEW LUA PATHS
--package.path = package.path..';'..system['useDir']..system['gameName']..'/app_lua/?.lua'
--package.path = package.path..';'..system['useDir']..system['gameName']..'/app_map/?.lua'

--package.path = package.path..';'..system['useDir']..system['gameName']..'/app_lua/?.luac'
--package.path = package.path..';'..system['useDir']..system['gameName']..'/app_map/?.luac'





--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--PATCH

system['pathSounds'] 	= system['useDir'] .. '/'..system['gameName'] ..'/app_sounds///'
system['pathImages'] 	= system['useDir'] .. '/'..system['gameName'] ..'/app_images//'
system['pathFont']      = system['useDir'] .. '/'..system['gameName'] ..'/app_fonts//'
system['pathMap']       = system['useDir'] .. '/'..system['gameName'] ..'/app_map//'
system['pathPck']       = system['useDir'] .. '/'..system['gameName'] ..'/app_pck//'

system['pathData']       = system['useDir'] .. '/'..system['gameName'] ..'/app_data//'
system['pathLevel']       = system['useDir'] .. '/'..system['gameName'] ..'/app_level//'

--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--DEBUG





print('')
print('')
print('')
print('')
print('')

print('devPlatform:',	MOAIEnvironment.devPlatform)
print('devProduct:',	MOAIEnvironment.devProduct)
print('devModel:',		MOAIEnvironment.devModel)
print('osVersion:',		MOAIEnvironment.osVersion)
print('osBrand:  ',		MOAIEnvironment.osBrand)

print('')
print('')
print('')
print('')
print('')

print('appDisplayName:________  ',	    	MOAIEnvironment.appDisplayName  )
print('appID:________________  ',	    			MOAIEnvironment.appID           )
print('appVersion:___________  ',	    		MOAIEnvironment.appVersion      )
print('cacheDirectory:_______  ',	    	MOAIEnvironment.cacheDirectory  )
print('carrierISOCountryCode:  ',	MOAIEnvironment.carrierISOCountryCode)
print('carrierMobileCountryCode:  ',MOAIEnvironment.carrierMobileCountryCode)
print('carrierMobileNetworkCode:  ',MOAIEnvironment.carrierMobileNetworkCode)
print('carrierName:__________  ',	    		MOAIEnvironment.carrierName)
print('connectionType:_______  ',	    	MOAIEnvironment.connectionType)
print('countryCode:__________  ',	    		MOAIEnvironment.countryCode)
print('cpuabi:_______________  ',	    			MOAIEnvironment.cpuabi)
print('devBrand:_____________  ',	    		MOAIEnvironment.devBrand)
print('devName:______________  ',	    			MOAIEnvironment.devName)
print('devManufacturer:______  ',	    	MOAIEnvironment.devManufacturer)
print('devModel:_____________  ',	    		MOAIEnvironment.devModel)
print('devPlatform:__________  ',	    		MOAIEnvironment.devPlatform)
print('devProduct:___________  ',	    		MOAIEnvironment.devProduct)
print('documentDirectory:____  ',	    MOAIEnvironment.documentDirectory)
print('iosRetinaDisplay:_____  ',	    MOAIEnvironment.iosRetinaDisplay)
print('languageCode:_________  ',	    	MOAIEnvironment.languageCode)
print('numProcessors:________  ',	    	MOAIEnvironment.numProcessors)
print('osBrand:______________  ',	    			MOAIEnvironment.osBrand)
print('osVersion:____________  ',	    		MOAIEnvironment.osVersion)
print('resourceDirectory:____  ',	    MOAIEnvironment.resourceDirectory)
print('screenDpi:____________  ',	    		MOAIEnvironment.screenDpi)
print('verticalResolution:___  ',	    MOAIEnvironment.verticalResolution)
print('horizontalResolution:_  ',	MOAIEnvironment.horizontalResolution)
print('udid:_________________  ',	    			MOAIEnvironment.udid)
print('openUdid:_____________  ',	    		MOAIEnvironment.openUdid)
print('tscreen Size-YES',MOAIEnvironment.horizontalResolution, MOAIEnvironment.verticalResolution)
print('tscreen Size-NO',MOAIEnvironment.screenWidth, MOAIEnvironment.screenHeight)
print('')
print('')
print('')
print('')
print('')






print('path>',system['pathSounds'])
print('path>',system['pathImages'])
print('path>',system['pathFont'])

print('')
print('')
print('')
print('')
print('')

print('gameDirectory>',			system['gameDirectory']      )
print('documentsDirectory>',	system['documentsDirectory'] )
print('cacheDirectory>',		system['cacheDirectory']     )
print('resourceDirectory>',		system['resourceDirectory']  )

print('')
print('')
print('')
print('')
print('')





--SHOULD BE SOMEWHERE ELSE

function system.resource_get(file_name)
	return  system['useDir']..system['gameName'] ..string.lower(file_name)
end



---*****************************************************************************
---*****************************************************************************
---*****************************************************************************
---*****************************************************************************
--DEBUG


local function traceError(message)

		local outString = '\n\n'..'<<HIT F12: ERROR>> '..message..'\n\n'
		
		outString = outString..debug.traceback()
		
		local time		= os.clock()
		local date 		= os.date("%Y_%m_%d_%H_%M_%S",time)
		
		local fileName 	= system['useDir']..system['gameName'].."//app_log//"..date
		
		
		--WRITE TO FILE
		local   taskData_Write = MOAIDataBuffer.new()
		taskData_Write:setString(outString)
		taskData_Write:save( fileName..'_'..time..".txt")   


end --END FUNCTION



--MOAISim.setTraceback(traceError)
















--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
end --END SQUISH FUNCTION
unit_system()
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
--&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
---LOADER



local function unit_loader()



local function load_game()


--IS MOBILE
if 	 (system['isFree'] == true) 
and  (system['isPC']   == false) 
then

		 print('>>> lua->  IS FREE',isFree)

		if 	system['osType'] =='ios' then

				print('>> INIT -IOS',MOAIChartBoost)

				MOAIChartBoost.init('546976c2bfe0845914424fc6', '1c6bce78f2c2ef10de5243e48403e964ab8da87e')
				MOAIChartBoost.loadInterstitial()

		elseif system['osType'] =='android' then


				print('>> lua->  INIT -ANDROID')
				MOAIChartBoost.init('54518cb7bfe0846e60a4eb3b', '7113f25b2ce89f6318c2cfeeef82f03a25bd6738')
				MOAIChartBoost.loadInterstitial()
				print('>> lua->  INIT - ANDROID - DONE')


		end


		--DONE
			MOAIChartBoost.setListener(MOAIChartBoost.INTERSTITIAL_DISMISSED,F._show_ad_done)
		--FAIl
			MOAIChartBoost.setListener(MOAIChartBoost.INTERSTITIAL_LOAD_FAILED,F._show_ad_done)


end






--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************


L._load_display()

L._load_text()

L._load_map()

L._load_music()

L._load_effect()

L._load_inputs()

F._game_restart()


--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--SPLASH



			--TEXTURE
				mTexture['moai'] = MOAITexture.new()
				mTexture['moai']:setFilter ( MOAITexture.GL_LINEAR ) --smooth
				mTexture['moai']:load( system['pathImages']..'//splash/splash_moai.png' , MOAIImage.PREMULTIPLY_ALPHA )


			--QUAD
				mQuad['moai'] = MOAIGfxQuad2D.new ()
				mQuad['moai']:setTexture ( mTexture['moai'])
				mQuad['moai']:setRect (0,0,480,320)
				mQuad['moai']:setUVRect ( 0, 0, 1, 1 )

				mProps['moai']  = MOAIProp2D.new ()
				mProps['moai']:setDeck(mQuad['moai'])
				mProps['moai']:setColor(1,1,1,1)
				mProps['moai'] :setPriority(10000)

			--INSERT
				--mLayer['display']:insertProp ( mProps['moai'] )


			--LOCK
				F._func_hero_lock()

				local function fade_done()
					--ULOCK
					print('fade done')
					F._func_hero_unlock()

					print('WTF',mLayer['display'], mProps['moai'])

					mLayer['display']:removeProp ( mProps['moai'] )

				end

				local function fade_pink()
						print('fade out')
					 	local action=mProps['moai']:seekColor ( 0, 0,0,0,1,MOAIEaseType.SOFT_SMOOTH )
					 	action:setListener ( MOAIAction.EVENT_STOP, fade_done )
				end


				print('fade in')
				local action=mProps['moai']:seekColor ( 1, 1,1,1,2,MOAIEaseType.SOFT_SMOOTH )
				action:setListener ( MOAIAction.EVENT_STOP, fade_pink )






			--*************************************************************
			--START THREAD
				mThread['enterframe'] = MOAICoroutine.new ()
				mThread['enterframe']:run ( A._enterframe )

				isLoaded = true








--***************************************************
--RESUME
local function callback_resume()
 	 print('RESUME')
	 F._show_ad()
end

	MOAISim.setListener ( MOAISim.EVENT_RESUME, callback_resume )



end --load game



--CALL LOAD
load_game()

































end --END SQUISH FUNCTION
unit_loader()
