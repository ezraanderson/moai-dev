

#include "pch.h"
#include <moai-chipmunk7/MOAICpDebugDraw.h>



#define LINE_COLOR 0.0f, 1.0f, 0.0f
#define COLLISION_COLOR 1.0f, 0.0f, 0.0f
#define BODY_COLOR 0.0f, 0.0f, 1.0f
#define BB_COLOR 0.3f, 0.5f, 0.3f
#define CONSTRAINT_COLOR 0.5f, 1.0f, 0.5f

static const float circleVAR[] = {
	 0.0000f,  1.0000f, 0.0f,
	 0.2588f,  0.9659f, 0.0f,
	 0.5000f,  0.8660f, 0.0f,
	 0.7071f,  0.7071f, 0.0f,
	 0.8660f,  0.5000f, 0.0f,
	 0.9659f,  0.2588f, 0.0f,
	 1.0000f,  0.0000f, 0.0f,
	 0.9659f, -0.2588f, 0.0f,
	 0.8660f, -0.5000f, 0.0f,
	 0.7071f, -0.7071f, 0.0f,
	 0.5000f, -0.8660f, 0.0f,
	 0.2588f, -0.9659f, 0.0f,
	 0.0000f, -1.0000f, 0.0f,
	-0.2588f, -0.9659f, 0.0f,
	-0.5000f, -0.8660f, 0.0f,
	-0.7071f, -0.7071f, 0.0f,
	-0.8660f, -0.5000f, 0.0f,
	-0.9659f, -0.2588f, 0.0f,
	-1.0000f, -0.0000f, 0.0f,
	-0.9659f,  0.2588f, 0.0f,
	-0.8660f,  0.5000f, 0.0f,
	-0.7071f,  0.7071f, 0.0f,
	-0.5000f,  0.8660f, 0.0f,
	-0.2588f,  0.9659f, 0.0f,
	 0.0000f,  1.0000f, 0.0f,
	 0.0f, 0.0f, 0.0f, // For an extra line to see the rotation.
};

static const float pillVAR[] = {
	 0.0000f,  1.0000f, 1.0f,
	 0.2588f,  0.9659f, 1.0f,
	 0.5000f,  0.8660f, 1.0f,
	 0.7071f,  0.7071f, 1.0f,
	 0.8660f,  0.5000f, 1.0f,
	 0.9659f,  0.2588f, 1.0f,
	 1.0000f,  0.0000f, 1.0f,
	 0.9659f, -0.2588f, 1.0f,
	 0.8660f, -0.5000f, 1.0f,
	 0.7071f, -0.7071f, 1.0f,
	 0.5000f, -0.8660f, 1.0f,
	 0.2588f, -0.9659f, 1.0f,
	 0.0000f, -1.0000f, 1.0f,

	 0.0000f, -1.0000f, 0.0f,
	-0.2588f, -0.9659f, 0.0f,
	-0.5000f, -0.8660f, 0.0f,
	-0.7071f, -0.7071f, 0.0f,
	-0.8660f, -0.5000f, 0.0f,
	-0.9659f, -0.2588f, 0.0f,
	-1.0000f, -0.0000f, 0.0f,
	-0.9659f,  0.2588f, 0.0f,
	-0.8660f,  0.5000f, 0.0f,
	-0.7071f,  0.7071f, 0.0f,
	-0.5000f,  0.8660f, 0.0f,
	-0.2588f,  0.9659f, 0.0f,
	 0.0000f,  1.0000f, 0.0f,
};

static const float springVAR[] = {
	0.00f, 0.0f, 0.0f,
	0.20f, 0.0f, 0.0f,
	0.25f, 3.0f, 0.0f,
	0.30f,-6.0f, 0.0f,
	0.35f, 6.0f, 0.0f,
	0.40f,-6.0f, 0.0f,
	0.45f, 6.0f, 0.0f,
	0.50f,-6.0f, 0.0f,
	0.55f, 6.0f, 0.0f,
	0.60f,-6.0f, 0.0f,
	0.65f, 6.0f, 0.0f,
	0.70f,-3.0f, 0.0f,
	0.75f, 6.0f, 0.0f,
	0.80f, 0.0f, 0.0f,
	1.00f, 0.0f, 0.0f,
};

static const int circleVAR_count = sizeof(circleVAR)/sizeof(float)/3;
static const int pillVAR_count = sizeof(pillVAR)/sizeof(float)/3;
static const int springVAR_count = sizeof(springVAR)/sizeof(float)/3;

//----------------------------------------------------------------//
static void draw_shape_verts ( const float* verts, u32 count, u32 color, bool drawFilled ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
	const ZLFrustum& viewVolume = gfxDevice.GetViewVolume ();



	bool draw = false;
	//***************************************************
	for ( u32 i = 0; i < count; ++i ) {
		u32 v = i << 1;
		if (viewVolume.Cull(ZLVec3D(verts [ v ],verts [ v + 1 ],0.0f)) == false){
			draw = true;
			break;
		};
	}


	//***************************************************
	if (draw == true) {
		if ( drawFilled ) {

			MOAIDraw::DrawVertexArray2D ( verts, count, color, ZGL_PRIM_TRIANGLE_FAN );			
			color = ZLColor::PackRGBA ( LINE_COLOR, 1.0f );
			MOAIDraw::DrawVertexArray2D ( verts, count, color, ZGL_PRIM_LINE_LOOP );
		}
	
	};


			//MOAIDraw::DrawVertexArray2D ( verts, count, color, ZGL_PRIM_TRIANGLE_FAN );			
			//color = ZLColor::PackRGBA ( LINE_COLOR, 1.0f );
			//MOAIDraw::DrawVertexArray2D ( verts, count, color, ZGL_PRIM_LINE_LOOP );


}

//----------------------------------------------------------------//
static u32 color_from_pointer(void *ptr) {

	unsigned long val = (long)ptr;
	
	// hash the pointer up nicely
	val = ( val + 0x7ed55d16 ) + ( val << 12 );
	val = ( val ^ 0xc761c23c ) ^ ( val >> 19 );
	val = ( val + 0x165667b1 ) + ( val << 5 );
	val = ( val + 0xd3a2646c ) ^ ( val << 9 );
	val = ( val + 0xfd7046c5 ) + ( val << 3 );
	val = ( val ^ 0xb55a4f09 ) ^ ( val >> 16 );
	
	int r = ( val >> 0 ) & 0xFF;
	int g = ( val >> 8 ) & 0xFF;
	int b = ( val >> 16 ) & 0xFF;
	
	int max = r > g ? ( r > b ? r : b) : ( g > b ? g : b );
	
	const int mult = 127;
	const int add = 63;
	r = (( r * mult ) / max ) + add;
	g = (( g * mult ) / max ) + add;
	b = (( b * mult ) / max ) + add;
	
	return ZLColor::PackRGBA ( r, g, b, 1 );
}

//----------------------------------------------------------------//
static u32 color_for_shape ( cpShape *shape, cpSpace *space ) {

	cpBody *body = cpShapeGetBody(shape);
	if ( body ) {
		//EZRA ERROR
		if ( body->sleeping.next ) {
			float v = 0.25f;
			return ZLColor::PackRGBA ( v, v, v, 1.0f );
		}
		else if ( body->sleeping.idleTime > space->sleepTimeThreshold ) {
			float v = 0.9f;
			return ZLColor::PackRGBA ( v, v, v, 1.0f );
		}
	}
	
	return color_from_pointer ( shape );
}

//----------------------------------------------------------------//
static void drawCircleShape(cpBody *body, cpCircleShape *circle, cpSpace *space) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );

	//printf("DRAW CIRCLE\n");
	const ZLFrustum& viewVolume = gfxDevice.GetViewVolume ();
	cpVect center = circle->tc;

	ZLBox box;	
	box.mMin.mX =center.x-( float )circle->r;
	box.mMin.mY =center.y-( float )circle->r;
	box.mMin.mZ = 0.0f;
	
	box.mMax.mX =center.x+( float )circle->r;
	box.mMax.mY =center.y+( float )circle->r;
	box.mMax.mZ = 0.0f;

	if (viewVolume.Cull(box) == false) {
	   u32 color = color_for_shape (( cpShape* )circle, space );
	   MOAIDraw::DrawEllipseOutline ( center.x, center.y, ( float )circle->r, ( float )circle->r, 32 );	
	};



	
	
	
   	
	//ZLAffine3D mtx;
	//mtx.ScRoTr (
	//	( float )circle->r, ( float )circle->r, 1.0f,
	//	0.0f, 0.0f, ( float )( body->a * 180.0 / M_PI ),
	//	( float )center.x, ( float )center.y, 0.0f
	//);
	//draw_shape_verts ( circleVAR, circleVAR_count, color, ( circle->shape.sensor == 0 ));
	//MOAIDraw::DrawVertexArray2D ( verts, count, color, ZGL_PRIM_LINE_LOOP );
	
	//gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM, mtx );
	//gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
}

//----------------------------------------------------------------//
static void drawSegmentShape ( cpBody* body, cpSegmentShape* seg, cpSpace* space ) {
	UNUSED ( body );

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );

	cpVect a = seg->ta;
	cpVect b = seg->tb;
	
	if ( seg->r ){
		
		cpVect d = cpvsub(b, a);
		cpVect r = cpvmult(d, seg->r/cpvlength(d));

		ZLMatrix4x4 mtx;
		
		mtx.m [ 0 ] = ( float )r.x;
		mtx.m [ 1 ] = ( float )r.y;
		mtx.m [ 2 ] = 0.0f;
		mtx.m [ 3 ] = 0.0f;
		
		mtx.m [ 4 ] = ( float )-r.y;
		mtx.m [ 5 ] = ( float )r.x;
		mtx.m [ 6 ] = 0.0f;
		mtx.m [ 7 ] = 0.0f;
		
		mtx.m [ 8 ] = ( float )d.x;
		mtx.m [ 9 ] = ( float )d.y;
		mtx.m [ 10 ] = 0.0f;
		mtx.m [ 11 ] = 0.0f;
		
		mtx.m [ 12 ] = ( float )a.x;
		mtx.m [ 13 ] = ( float )a.y;
		mtx.m [ 14 ] = 0.0f;
		mtx.m [ 15 ] = 0.0f;
		
		gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM, mtx );
		
		u32 color = color_for_shape (( cpShape* )seg, space );
		draw_shape_verts ( pillVAR, pillVAR_count, color, ( seg->shape.sensor == 0 ));
		
		gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );

	}
	else {
	
		gfxDevice.SetPrimType ( ZGL_PRIM_LINES );
		gfxDevice.SetPenColor ( ZLColor::PackRGBA ( LINE_COLOR, 1.0f ));
		
		gfxDevice.WriteVtx (( float )a.x, ( float )a.y, 0.0f );
		gfxDevice.WriteFinalColor4b ();
		
		gfxDevice.WriteVtx (( float )b.x, ( float )b.y, 0.0f );
		gfxDevice.WriteFinalColor4b ();
		
		gfxDevice.Flush ();
	}
}

//----------------------------------------------------------------//
static void drawPolyShape ( cpBody* body, cpPolyShape* poly, cpSpace* space ) {
	UNUSED ( body );

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_WORLD, MOAIGfxDevice::VTX_STAGE_PROJ );


	// https://github.com/moai/moai-beta/blob/master/src/moaicore/MOAICpDebugDraw.cpp


		static const u32 MAX = 2048;
		float verts [ MAX ];
		
		int cnt = 0;
		int unsigned  count = cpPolyShapeGetCount(( cpShape* )poly);
		for ( u32 i = 0; i < count; ++i ) {
				cpVect vec = cpBodyLocalToWorld(body,cpPolyShapeGetVert(( cpShape* )poly,i));
				//printf("x %f y %f \n",vec.x,vec.y);			
				verts[cnt] =  ( float )vec.x;	
				cnt = cnt+ 1;
				verts[cnt] =  ( float )vec.y;
				cnt = cnt+ 1;
			
		};


	u32 color = color_for_shape (( cpShape* )poly, space );
	draw_shape_verts (( float* )verts, count, color, ( poly->shape.sensor == 0 ));
}












//----------------------------------------------------------------//
static void drawObject ( cpShape *shape, cpSpace *space ) {

	cpBody *body = shape->body;
	
	switch(shape->klass->type){
		case CP_CIRCLE_SHAPE:
			drawCircleShape(body, (cpCircleShape *)shape, space);
			break;
		case CP_SEGMENT_SHAPE:
			drawSegmentShape(body, (cpSegmentShape *)shape, space);
			break;
		case CP_POLY_SHAPE:
			drawPolyShape(body, (cpPolyShape *)shape, space);
			break;
		default:
			//printf("Bad enumeration in drawObject().\n");
			break;
	}
}















//----------------------------------------------------------------//
static void drawSpring ( cpDampedSpring* spring, cpBody* body_a, cpBody* body_b ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );

	//cpVect a = cpvadd ( body_a->p, cpvrotate ( spring->anchr1, body_a->rot ));
	//cpVect b = cpvadd ( body_b->p, cpvrotate ( spring->anchr2, body_b->rot ));


	cpVect a = cpvadd(cpBodyGetPosition(body_a), cpvrotate(spring->anchorA, cpBodyGetRotation( body_a)));
	cpVect b = cpvadd(cpBodyGetPosition(body_b), cpvrotate(spring->anchorB, cpBodyGetRotation(body_b)));


	gfxDevice.SetPointSize ( 5.0f );

	MOAIDraw::DrawPoint (( float )a.x, ( float )a.y );
	MOAIDraw::DrawPoint (( float )b.x, ( float )b.y );

	cpVect delta = cpvsub ( b, a );
	float cos = ( float )delta.x;
	float sin = ( float )delta.y;
	float s = ( float )( 1.0 / cpvlength ( delta ));
	
	ZLMatrix4x4 mtx;
	
	mtx.m [ 0 ] = cos;
	mtx.m [ 1 ] = sin;
	mtx.m [ 2 ] = 0.0f;
	mtx.m [ 3 ] = 0.0f;
	
	mtx.m [ 4 ] = -sin * s;
	mtx.m [ 5 ] = cos * s;
	mtx.m [ 6 ] = 0.0f;
	mtx.m [ 7 ] = 0.0f;
	
	mtx.m [ 8 ] = 0.0f;
	mtx.m [ 9 ] = 0.0f;
	mtx.m [ 10 ] = 1.0f;
	mtx.m [ 11 ] = 0.0f;
	
	mtx.m [ 12 ] = ( float )a.x;
	mtx.m [ 13 ] = ( float )a.y;
	mtx.m [ 14 ] = 0.0f;
	mtx.m [ 15 ] = 1.0f;
	
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM, mtx );
	
	gfxDevice.SetPrimType ( ZGL_PRIM_LINE_STRIP );
	gfxDevice.SetPenColor ( ZLColor::PackRGBA ( LINE_COLOR, 1.0f ));
	
	MOAIDraw::DrawVertexArray2D ( springVAR, springVAR_count, ZLColor::PackRGBA ( LINE_COLOR, 1.0f ), ZGL_PRIM_LINE_STRIP );
	
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
}

//----------------------------------------------------------------//
static void drawConstraint ( cpConstraint* constraint ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_WORLD, MOAIGfxDevice::VTX_STAGE_PROJ );

	cpBody* body_a =cpConstraintGetBodyA(constraint);
	cpBody* body_b = cpConstraintGetBodyB(constraint);


	if ( cpBool( true) == cpConstraintIsPinJoint(constraint)) {
		
		cpPinJoint* joint = ( cpPinJoint* )constraint;	


		cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchorA,cpBodyGetRotation( body_a)));
		cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchorB, cpBodyGetRotation( body_b)));

		//cpVect a = cpvadd(cpBodyGetPosition(body_a), cpvrotate(cpPinJointGetAnchorA(constraint), cpBodyGetRotation( body_a)));
		//cpVect b = cpvadd(cpBodyGetPosition(body_b), cpvrotate(cpPinJointGetAnchorB(constraint), cpBodyGetRotation(body_b)));

		gfxDevice.SetPointSize ( 5.0f );
		
		MOAIDraw::DrawPoint (( float )a.x, ( float )a.y );
		MOAIDraw::DrawPoint (( float )b.x, ( float )b.y );
		MOAIDraw::DrawLine (( float )a.x, ( float )a.y, ( float )b.x, ( float )b.y );
	}
	else if ( cpBool( true) == cpConstraintIsSlideJoint (constraint)) {
		
		cpSlideJoint *joint = (cpSlideJoint *)constraint;
	
		cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchorA,cpBodyGetRotation( body_a)));
		cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchorB, cpBodyGetRotation( body_b)));

		//cpVect a = cpvadd(cpBodyGetPosition(body_a), cpvrotate(cpSlideJointGetAnchorA(constraint), cpBodyGetRotation( body_a)));
		//cpVect b = cpvadd(cpBodyGetPosition(body_b), cpvrotate(cpSlideJointGetAnchorB(constraint), cpBodyGetRotation(body_b)));

		gfxDevice.SetPointSize ( 5.0f );

		MOAIDraw::DrawPoint (( float )a.x, ( float )a.y );
		MOAIDraw::DrawPoint (( float )b.x, ( float )b.y );
	}
	else if ( cpBool( true) == cpConstraintIsPivotJoint (constraint)){
	
		cpPivotJoint *joint = (cpPivotJoint *)constraint;
	
		cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchorA, cpBodyGetRotation( body_a)));
		cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchorB, cpBodyGetRotation( body_b)));

		//cpVect a = cpvadd(cpBodyGetPosition(body_a), cpvrotate(cpPivotJointGetAnchorA(constraint), cpBodyGetRotation( body_a)));
		//cpVect b = cpvadd(cpBodyGetPosition(body_b), cpvrotate(cpPivotJointGetAnchorB(constraint), cpBodyGetRotation(body_b)));

		gfxDevice.SetPointSize ( 10.0f );
		
		MOAIDraw::DrawPoint (( float )a.x, ( float )a.y );
		MOAIDraw::DrawPoint (( float )b.x, ( float )b.y );
	}
	else if ( cpBool( true) == cpConstraintIsGrooveJoint (constraint)){
	
		cpGrooveJoint *joint = (cpGrooveJoint *)constraint;
	
		cpVect a = cpvadd(body_a->p, cpvrotate(joint->grv_a, cpBodyGetRotation( body_a)));
		cpVect b = cpvadd(body_a->p, cpvrotate(joint->grv_b, cpBodyGetRotation( body_b)));

		//cpVect a = cpvadd(cpBodyGetPosition(body_a), cpvrotate(cpGrooveJointGetGrooveA(constraint), cpBodyGetRotation( body_a)));
		//cpVect b = cpvadd(cpBodyGetPosition(body_b), cpvrotate(cpGrooveJointGetGrooveB(constraint), cpBodyGetRotation(body_b)));

		cpVect c = cpvadd(cpBodyGetPosition(body_b), cpvrotate(cpGrooveJointGetAnchorB(constraint), cpBodyGetRotation( body_b)));

		gfxDevice.SetPointSize ( 5.0f );
		
		MOAIDraw::DrawPoint (( float )c.x, ( float )c.y );
		MOAIDraw::DrawLine (( float )a.x, ( float )a.y, ( float )b.x, ( float )b.y );
	}
	else if ( cpBool( true) == cpConstraintIsDampedSpring (constraint)) {
		drawSpring((cpDampedSpring *)constraint, body_a, body_b);
	}
	else {
		//printf("Cannot draw constraint\n");
	}
}

//----------------------------------------------------------------//
static void drawBB ( cpShape *shape, void *unused ) {
	UNUSED ( unused );

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_WORLD, MOAIGfxDevice::VTX_STAGE_PROJ );
	gfxDevice.SetPrimType ( ZGL_PRIM_LINE_LOOP );

	gfxDevice.WriteVtx (( float )shape->bb.l, ( float )shape->bb.b, 0.0f );
	gfxDevice.WriteFinalColor4b ();
	
	gfxDevice.WriteVtx (( float )shape->bb.l, ( float )shape->bb.t, 0.0f );
	gfxDevice.WriteFinalColor4b ();
	
	gfxDevice.WriteVtx (( float )shape->bb.r, ( float )shape->bb.t, 0.0f );
	gfxDevice.WriteFinalColor4b ();
	
	gfxDevice.WriteVtx (( float )shape->bb.r, ( float )shape->bb.b, 0.0f );
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.Flush ();
}

//----------------------------------------------------------------//
// copied from cpSpaceHash.c
static inline cpHashValue hash_func ( cpHashValue x, cpHashValue y, cpHashValue n ) {
	return ( x*1640531513ul ^ y*2654435789ul ) % n;
}

//----------------------------------------------------------------//
// TODO
//static void drawSpatialHash ( cpSpaceHash *hash ) {
//
//	cpBB bb = cpBBNew ( -320, -240, 320, 240 );
//	
//	cpFloat dim = hash->celldim;
//	int n = hash->numcells;
//	
//	int l = (int)floor(bb.l/dim);
//	int r = (int)floor(bb.r/dim);
//	int b = (int)floor(bb.b/dim);
//	int t = (int)floor(bb.t/dim);
//	
//	float vtx [ 8 ];
//	
//	for(int i=l; i<=r; i++){
//		for(int j=b; j<=t; j++){
//			int cell_count = 0;
//			
//			int index = hash_func(i,j,n);
//			for(cpSpaceHashBin *bin = hash->table[index]; bin; bin = bin->next)
//				cell_count++;
//			
//			GLfloat v = 1.0f - (GLfloat)cell_count/10.0f;
//			glColor4f(v,v,v,1);
//			
//			float x1 = ( float )( i * dim );
//			float y1 = ( float )( j * dim );
//			float x2 = ( float )(( i + 1 ) * dim );
//			float y2 = ( float )(( j + 1 ) * dim );
//			
//			vtx [ 0 ] = x1;
//			vtx [ 1 ] = y2;
//			
//			vtx [ 2 ] = x2;
//			vtx [ 3 ] = y2;
//			
//			vtx [ 4 ] = x1;
//			vtx [ 5 ] = y1;
//			
//			vtx [ 6 ] = x2;
//			vtx [ 7 ] = y1;
//			
//			glVertexPointer ( 2, GL_FLOAT, 0, vtx );
//			glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );
//		}
//	}
//}

//----------------------------------------------------------------//
void MOAICpDebugDraw::DrawSpace ( cpSpace *space, MOAICpDebugDrawOptions *options ) {

	MOAIDraw::Bind ();

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	// clear out model to world transform
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );

	// TODO
	//if ( options->drawHash ) {
	//	glColorMask ( GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE );
	//	drawSpatialHash ( space->activeShapes );
	//	glColorMask ( GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE );
	//	drawSpatialHash ( space->staticShapes );
	//	glColorMask ( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
	//}
	
	gfxDevice.SetPenWidth ( options->lineThickness );
	if ( options->drawShapes ) {
	//	printf("DRAW \n");

		//cpSpaceHashEach ( space->activeShapes, ( cpSpaceHashIterator )drawObject, space );
		//cpSpaceHashEach ( space->staticShapes, ( cpSpaceHashIterator )drawObject, space );

		cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)drawObject, options);

	}
	
	gfxDevice.SetPenWidth ( 1.0f );
	if ( options->drawBBs ){
		gfxDevice.SetPenColor (  BB_COLOR, 1.0f );
		//cpSpaceHashEach ( space->activeShapes, ( cpSpaceHashIterator )drawBB, NULL );
		//cpSpaceHashEach ( space->staticShapes, ( cpSpaceHashIterator )drawBB, NULL );
	}

	gfxDevice.SetPenColor ( CONSTRAINT_COLOR, 1.0f );
	cpArray *constraints = space->constraints;
	for ( int i = 0, count = constraints->num; i < count; i++ ){
		drawConstraint (( cpConstraint* )constraints->arr [ i ]);
	}
	
	if ( options->bodyPointSize ) {
		
		gfxDevice.SetPointSize ( options->bodyPointSize );
		gfxDevice.SetPenColor ( LINE_COLOR, 1.0f );
		
		cpArray *bodies = space->dynamicBodies;
		for ( int i=0, count = bodies->num; i<count; i++ ){
			cpBody* body = ( cpBody* )bodies->arr [ i ];
			MOAIDraw::DrawPoint (( float )body->p.x, ( float )body->p.y );
		}
	}

	if ( options->collisionPointSize ) {
		
		gfxDevice.SetPointSize ( options->collisionPointSize );
		gfxDevice.SetPenColor ( COLLISION_COLOR, 1.0f );
		
		cpArray *arbiters = space->arbiters;
		for ( int i = 0; i < arbiters->num; i++ ) {
			
			cpArbiter* arb = ( cpArbiter* )arbiters->arr [ i ];
			for ( int j = 0; j < arb->count; j++ ){
				//cpVect v = arb->contacts [ j ].r1;
				//MOAIDraw::DrawPoint (( float )v.x, ( float )v.y );
			}
		}
	}
}
