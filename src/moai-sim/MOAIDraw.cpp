// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIAnimCurve.h>
#include <moai-sim/MOAIDraw.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIShaderMgr.h>
#include <moai-sim/MOAIVertexFormatMgr.h>
#include <moai-sim/MOAITexture.h>
#include <moai-sim/MOAIQuadBrush.h>

#include <moai-sim/MOAIFont.h>

#define DEFAULT_ELLIPSE_STEPS 64


float rect_x =0;
float rect_y =0;
float rect_step =-1;


//================================================================//
// text drawing stuff
//================================================================//
/*
	TODO: I want to refactor/rewrite this stuff to consolidate the glyph layout and buffering
	under a single code path - there's some redundancy here with MOAITextBox that can probably
	be smoothed away.
*/

struct GlyphPlacement {

	MOAIGlyph* glyph;
	float x;
	float y;
};

struct TextDrawContext {
		
	// Text
	STLList < GlyphPlacement > mGlyphs;

	// Text data
	MOAIFont* mFont;
	float mScale;
	float mFontSize;
	float mShadowOffsetX;
	float mShadowOffsetY;
};

static TextDrawContext g_TextDrawContext;
static TextDrawContext* g_CurrentTextDrawContext = 0;

//----------------------------------------------------------------//
void MOAIDraw::BeginDrawString ( float scale, MOAIFont& font, float fontSize, float shadowOffsetX, float shadowOffsetY ) {
	
	assert ( g_CurrentTextDrawContext == 0 );

	g_CurrentTextDrawContext                    = &g_TextDrawContext;
	g_CurrentTextDrawContext->mFont             = &font;
	g_CurrentTextDrawContext->mFontSize         = fontSize;
	g_CurrentTextDrawContext->mScale            = scale;
	g_CurrentTextDrawContext->mShadowOffsetX    = shadowOffsetX;
	g_CurrentTextDrawContext->mShadowOffsetY    = shadowOffsetY;
}

//----------------------------------------------------------------//
void MOAIDraw::DrawString ( cc8* text, float x, float y, float width, float height,int align ) {

	// Sanity check
	size_t textLength = strlen ( text );
	if ( textLength <= 0 ) return;
	
	// Get the context data
	assert ( g_CurrentTextDrawContext );

	// Transform the center into 'world' space
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

    //gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE );
    gfxDevice.SetShaderPreset ( MOAIShaderMgr::FONT_SHADER );


	const ZLMatrix4x4& orgWorldTransform = gfxDevice.GetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	USVec2D pos ( x, y );
	orgWorldTransform.Transform ( pos );
	x = pos.mX;
	y = pos.mY;

	// Extract the 'state'
	MOAIFont& font      = *g_CurrentTextDrawContext->mFont;
	float scale         = g_CurrentTextDrawContext->mScale;
	float fontSize      = g_CurrentTextDrawContext->mFontSize;
	
	MOAIGlyphSet* glyphSet = font.GetGlyphSet ( fontSize );
	assert ( glyphSet );

	// Let's draw the string!
	float cursorX = x;
	float cursorY = y + glyphSet->GetAscent() * scale;
	MOAIGlyph* prevGlyph = 0;   

	// Update the glyph cache
	for ( size_t i = 0; i < textLength; i++ ) {

		cc8 c = text [ i ];
		if ( c != '\n' ) {
			font.AffirmGlyph ( fontSize, c );
		}
	}
	
	font.ProcessGlyphs ();
	glyphSet = font.GetGlyphSet ( fontSize );
	assert ( glyphSet );


//************************************************************************************************************
//LEFT
if (align == 1) {

	for ( size_t i = 0; i < textLength; i++ ) {

		cc8 c = text [ i ];
		if ( c == '\n' ) {

			// Move to the next line
			cursorX = x;
			cursorY += glyphSet->GetHeight () * scale;
			prevGlyph = 0;

			if ( height > 0 && (cursorY - y) > height ) {
				break;
			}
		}
		else {

			if ( width > 0 && (cursorX - x) > width ) {
				continue;
			}

			// Get the glyph for the current character
			MOAIGlyph* glyph = glyphSet->GetGlyph ( c );
			if ( glyph ) {

				// Draw the current glyph
				MOAITextureBase* glyphTexture = font.GetGlyphTexture ( *glyph );
				if ( glyphTexture ) {

					GlyphPlacement placement = { glyph, cursorX, cursorY };
					g_CurrentTextDrawContext->mGlyphs.push_back( placement );
				}

				// Apply kerning
				if ( prevGlyph ) {

					MOAIKernVec kern = prevGlyph->GetKerning ( glyph->GetCode () );
					cursorX += kern.mX * scale;
				}

				// Move the cursor
				cursorX += glyph->GetAdvanceX () * scale;
			}

			prevGlyph = glyph;
		}
	} //I

} //LEFT


//************************************************************************************************************
//RIGHT
if (align == 2) {

for (int i = textLength; i --> 0; ) {

		cc8 c = text [ i ];
		if ( c == '\n' ) {

			// Move to the next line
			cursorX = x;
			cursorY += glyphSet->GetHeight () * scale;
			prevGlyph = 0;

			if ( height > 0 && (cursorY - y) > height ) {
				break;
			}
		}
		else {
			
			// Move the cursor
		// Get the glyph for the current character
			MOAIGlyph* glyph = glyphSet->GetGlyph ( c );

			cursorX -= glyph->GetAdvanceX () * scale;


			if ( width > 0 && (cursorX - x) > width ) {
				continue;
			}

	
			if ( glyph ) {

				// Draw the current glyph
				MOAITextureBase* glyphTexture = font.GetGlyphTexture ( *glyph );
				if ( glyphTexture ) {

					GlyphPlacement placement = { glyph, cursorX, cursorY };
					g_CurrentTextDrawContext->mGlyphs.push_back( placement );
				}

				// Apply kerning
				if ( prevGlyph ) {

					MOAIKernVec kern = prevGlyph->GetKerning ( glyph->GetCode () );
					cursorX += kern.mX * scale;
				}

			}

			prevGlyph = glyph;
		}
	} //I

} //LEFT








}

//----------------------------------------------------------------//
void MOAIDraw::DrawString	( cc8* text, float x, float y, float scale, MOAIFont& font, float fontSize, float shadowOffsetX, float shadowOffsetY, float width, float height,int align ) {

	BeginDrawString ( scale, font, fontSize, shadowOffsetX, shadowOffsetY );
	DrawString ( text, x, y, width, height, align);
	EndDrawString ();
}




//----------------------------------------------------------------//
void MOAIDraw::EndDrawString () {

	// Setup for drawing
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	// Get current state
	const ZLMatrix4x4& orgWorldTransform = gfxDevice.GetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );

	u32 orgVtxModeInput, orgVtxModeOutput;
	gfxDevice.GetVertexMtxMode ( orgVtxModeInput, orgVtxModeOutput );

	// TODO
	//int orgSrcBlend, orgDestBlend;
	//glGetIntegerv ( GL_BLEND_SRC, &orgSrcBlend );
	//glGetIntegerv ( GL_BLEND_DST, &orgDestBlend );

	// Apply render state

	gfxDevice.SetShaderPreset ( MOAIShaderMgr::FONT_SHADER );
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_WORLD, MOAIGfxDevice::VTX_STAGE_PROJ );
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

	//BROKEN
		gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );
	//WORKS
		gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );


	MOAIQuadBrush::BindVertexFormat ( gfxDevice );

	// Get the context data
	assert( g_CurrentTextDrawContext );
	
	MOAIFont& font = *g_CurrentTextDrawContext->mFont;
	float scale = g_CurrentTextDrawContext->mScale;
	float shadowOffsetX = g_CurrentTextDrawContext->mShadowOffsetX;
	float shadowOffsetY = g_CurrentTextDrawContext->mShadowOffsetY;

	bool drawDropShadows = fabsf ( shadowOffsetX ) > 0.0001 && fabsf ( shadowOffsetY ) > 0.0001;

	u32 numPasses = 1;
	float offsetX = 0;
	float offsetY = 0;
	ZLColorVec penColor = gfxDevice.GetPenColor ();
	if ( drawDropShadows ) {

		numPasses = 2;		
		gfxDevice.SetPenColor ( 0, 0, 0, 1 );
		offsetX = shadowOffsetX;
		offsetY = shadowOffsetY;
	}

	for ( u32 pass = 0; pass < numPasses; pass++ ) {

		if ( pass == 1 || numPasses == 1 ) {
			gfxDevice.SetPenColor ( penColor );
			offsetX = 0;
			offsetY = 0;
		}

		STLList < GlyphPlacement >::const_iterator it;
		for ( it = g_CurrentTextDrawContext->mGlyphs.begin (); it != g_CurrentTextDrawContext->mGlyphs.end (); ++it ) {
			const GlyphPlacement& glyphPlacement = *it;
			MOAIGlyph* glyph = glyphPlacement.glyph;
			MOAITextureBase* glyphTexture = font.GetGlyphTexture ( *glyph );
			glyph->Draw ( *glyphTexture, glyphPlacement.x + offsetX, glyphPlacement.y + offsetY, scale );
		}
	}

	// Restore render state
	Bind();

	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM, orgWorldTransform );
	gfxDevice.SetVertexMtxMode ( orgVtxModeInput, orgVtxModeOutput );

	//gfxDevice.SetBlendMode ( orgSrcBlend, orgDestBlend ); // TODO
	//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ZERO );

	gfxDevice.Flush();

	// Clear context
	g_CurrentTextDrawContext->mFont = 0;
	g_CurrentTextDrawContext->mGlyphs.clear();
	g_CurrentTextDrawContext = 0;
}

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
int MOAIDraw::_drawAnimCurve ( lua_State* L ) {

	MOAILuaState state ( L );

	MOAIAnimCurve* curve	= state.GetLuaObject < MOAIAnimCurve >( 1, true );
	u32 resolution			= state.GetValue < u32 >( 2, 1 );

	if ( curve ) {
		MOAIDraw::DrawAnimCurve ( *curve, resolution );
	}
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIDraw::_drawAxisGrid ( lua_State* L ) {
	UNUSED ( L );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawBoxOutline
	@text	Draw a box outline.
	
	@in		number x0
	@in		number y0
	@in		number z0
	@in		number x1
	@in		number y1
	@in		number z1
	@out	nil
*/
int MOAIDraw::_drawBoxOutline ( lua_State* L ) {

	MOAILuaState state ( L );

	ZLBox box;
	box.mMin.mX = state.GetValue < float >( 1, 0.0f );
	box.mMin.mY = state.GetValue < float >( 2, 0.0f );
	box.mMin.mZ = state.GetValue < float >( 3, 0.0f );
	box.mMax.mX = state.GetValue < float >( 4, box.mMin.mX );
	box.mMax.mY = state.GetValue < float >( 5, box.mMin.mY );
	box.mMax.mZ = state.GetValue < float >( 6, box.mMin.mZ );
	MOAIDraw::DrawBoxOutline(box);
	return 0;

}

//----------------------------------------------------------------//
/**	@name	drawCircle
	@text	Draw a circle.
	
	@in		number x
	@in		number y
	@in		number r
	@in		number steps
	@out	nil
*/
int MOAIDraw::_drawCircle ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x0	= state.GetValue < float >( 1, 0.0f );
	float y0	= state.GetValue < float >( 2, 0.0f );
	float r		= state.GetValue < float >( 3, 0.0f );
	u32 steps	= state.GetValue < u32 >( 4, DEFAULT_ELLIPSE_STEPS );

	MOAIDraw::DrawEllipseOutline ( x0, y0, r, r, steps );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawEllipse
	@text	Draw an ellipse.
	
	@in		number x
	@in		number y
	@in		number xRad
	@in		number yRad
	@in		number steps
	@out	nil
*/
int MOAIDraw::_drawEllipse ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x		= state.GetValue < float >( 1, 0.0f );
	float y		= state.GetValue < float >( 2, 0.0f );
	float xRad	= state.GetValue < float >( 3, 0.0f );
	float yRad	= state.GetValue < float >( 4, 0.0f );
	
	u32 steps = state.GetValue < u32 >( 5, DEFAULT_ELLIPSE_STEPS );

	MOAIDraw::DrawEllipseOutline ( x, y, xRad, yRad, steps );
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIDraw::_drawGrid ( lua_State* L ) {
	UNUSED ( L );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawLine
	@text	Draw a line.
	
	@in		... vertices		List of vertices (x, y) or an array of vertices
								{ x0, y0, x1, y1, ... , xn, yn }
	@out	nil
*/
int MOAIDraw::_drawLine ( lua_State* L ) {

	if ( lua_istable ( L, -1 ) ) {
		MOAIDraw::DrawLuaArray ( L, ZGL_PRIM_LINE_STRIP );
	} else {
		MOAIDraw::DrawLuaParams ( L, ZGL_PRIM_LINE_STRIP );
	}
	return 0;
}


int MOAIDraw::_drawVertics ( lua_State* L ) {

	if ( lua_istable ( L, -1 ) ) {
		MOAIDraw::DrawLuaArray ( L, ZGL_PRIM_TRIANGLE_STRIP );
	} else {
		MOAIDraw::DrawLuaParams ( L, ZGL_PRIM_TRIANGLE_STRIP );
	}
	return 0;
}


//----------------------------------------------------------------//
/**	@name	drawPoints
	@text	Draw a list of points.
	
	@in		... vertices		List of vertices (x, y) or an array of vertices
								{ x0, y0, x1, y1, ... , xn, yn }
	@out	nil
*/
int MOAIDraw::_drawPoints ( lua_State* L ) {
	
	if ( lua_istable ( L, -1 ) ) {
		MOAIDraw::DrawLuaArray ( L, ZGL_PRIM_POINTS );
	} else {
		MOAIDraw::DrawLuaParams ( L, ZGL_PRIM_POINTS );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawRay
	@text	Draw a ray.
	
	@in		number x
	@in		number y
	@in		number dx
	@in		number dy
	@out	nil
*/
int MOAIDraw::_drawRay ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x		= state.GetValue < float >( 1, 0.0f );
	float y		= state.GetValue < float >( 2, 0.0f );
	float dx	= state.GetValue < float >( 3, 0.0f );
	float dy	= state.GetValue < float >( 4, 0.0f );

	MOAIDraw::DrawRay ( x, y, dx, dy );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawRect
	@text	Draw a rectangle.
	
	@in		number x0
	@in		number y0
	@in		number x1
	@in		number y1
	@out	nil
*/
int MOAIDraw::_drawRect ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x0 = state.GetValue < float >( 1, 0.0f );
	float y0 = state.GetValue < float >( 2, 0.0f );
	float x1 = state.GetValue < float >( 3, 0.0f );
	float y1 = state.GetValue < float >( 4, 0.0f );

	MOAIDraw::DrawRectOutline ( x0, y0, x1, y1 );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	fillCircle
	@text	Draw a filled circle.
	
	@in		number x
	@in		number y
	@in		number r
	@in		number steps
	@out	nil
*/
int MOAIDraw::_fillCircle ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x0	= state.GetValue < float >( 1, 0.0f );
	float y0	= state.GetValue < float >( 2, 0.0f );
	float r		= state.GetValue < float >( 3, 0.0f );
	u32 steps	= state.GetValue < u32 >( 4, DEFAULT_ELLIPSE_STEPS );

	MOAIDraw::DrawEllipseFill ( x0, y0, r, r, steps );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	fillEllipse
	@text	Draw a filled ellipse.
	
	@in		number x
	@in		number y
	@in		number xRad
	@in		number yRad
	@in		number steps
	@out	nil
*/
int MOAIDraw::_fillEllipse ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x		= state.GetValue < float >( 1, 0.0f );
	float y		= state.GetValue < float >( 2, 0.0f );
	float xRad	= state.GetValue < float >( 3, 0.0f );
	float yRad	= state.GetValue < float >( 4, 0.0f );
	
	u32 steps = state.GetValue < u32 >( 5, DEFAULT_ELLIPSE_STEPS );

	MOAIDraw::DrawEllipseFill ( x, y, xRad, yRad, steps );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	fillFan
	@text	Draw a filled fan.
	
	@in		... vertices		List of vertices (x, y) or an array of vertices
								{ x0, y0, x1, y1, ... , xn, yn }
	@out	nil
*/
int MOAIDraw::_fillFan ( lua_State* L ) {

	if ( lua_istable ( L, -1 ) ) {
		MOAIDraw::DrawLuaArray( L, ZGL_PRIM_TRIANGLE_FAN );
	} else {
		MOAIDraw::DrawLuaParams( L, ZGL_PRIM_TRIANGLE_FAN );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	fillRect
	@text	Draw a filled rectangle.
	
	@in		number x0
	@in		number y0
	@in		number x1
	@in		number y1
	@out	nil
*/
int MOAIDraw::_fillRect ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x0 = state.GetValue < float >( 1, 0.0f );
	float y0 = state.GetValue < float >( 2, 0.0f );
	float x1 = state.GetValue < float >( 3, 0.0f );
	float y1 = state.GetValue < float >( 4, 0.0f );

	MOAIDraw::DrawRectFill ( x0, y0, x1, y1,true );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawTexture
	@text	Draw a filled rectangle.
	
	@in		number x0
	@in		number y0
	@in		number x1
	@in		number y1
	@in		MOAITexture texture
	@out	nil
*/
int MOAIDraw::_drawTexture ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x0 = state.GetValue < float >( 1, 0.0f );
	float y0 = state.GetValue < float >( 2, 0.0f );
	float x1 = state.GetValue < float >( 3, 0.0f );
	float y1 = state.GetValue < float >( 4, 0.0f );
	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 5 );

	MOAIDraw::DrawTexture ( x0, y0, x1, y1, texture );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	drawText
	@text	Draws a string.
	
	@in		MOAIFont font
	@in		number size		Font size
	@in		string text
	@in		number x		Left position
	@in		number y		Top position
	@in		number scale
	@in		number shadowOffsetX
	@in		number shadowOffsetY
	@out	nil
*/
int MOAIDraw::_drawText ( lua_State* L ) {

	MOAILuaState state ( L );
	cc8* text = lua_tostring ( state, 3 );

	if ( text ) {

	float x = state.GetValue < float >( 4, 0.0f );
	float y = state.GetValue < float >( 5, 0.0f );
	float scale = state.GetValue < float >( 6, 1.0f );

	float shadowOffsetX = state.GetValue < float >( 7, 0.0f );
	float shadowOffsetY = state.GetValue < float >( 8, 0.0f );

	int align = state.GetValue < int >( 9, 1 );

		MOAIFont* font = state.GetLuaObject < MOAIFont >( 1, true );
		if ( font ) {
			float fontSize = state.GetValue < float >( 2, font->GetDefaultSize () );
			MOAIDraw::DrawString ( text, x, y, scale, *font, fontSize, shadowOffsetX, shadowOffsetY, 0, 0,align );
		};
	};
	return 0;
};






//================================================================//
// MOAIDraw
void MOAIDraw::Bind () {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	gfxDevice.SetTexture ();
	gfxDevice.SetShaderPreset ( MOAIShaderMgr::LINE_SHADER );
	gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWC );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawAnimCurve ( const MOAIAnimCurve& curve, u32 resolution ) {

	curve.Draw ( resolution );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawAxisGrid ( USVec2D loc, USVec2D vec, float size ) {

	ZLMatrix4x4 mtx = MOAIGfxDevice::Get ().GetViewProjMtx ();
	
	ZLMatrix4x4 invMtx;
	invMtx.Inverse ( mtx );
	
	// Set the axis to the grid length so we can get the length back post-transform
	vec.SetLength ( size );
	
	mtx.Transform ( loc );
	mtx.TransformVec ( vec );

	// Get the axis unit vector
	USVec2D norm = vec;
	size = norm.NormSafe ();
	
	// Get the axis normal
	USVec2D perpNorm ( norm.mY, -norm.mX );
	
	// Project the corners of the viewport onto the axis to get the mix/max bounds
	float dot;
	float min;
	float max;
	
	USVec2D corner;
	
	// left, top
	corner.Init ( -1.0f, 1.0f );
	corner.Sub ( loc );
	dot = norm.Dot ( corner );
	
	min = dot;
	max = dot;
	
	// right, top
	corner.Init ( 1.0f, 1.0f );
	corner.Sub ( loc );
	dot = norm.Dot ( corner );
	
	min = ( dot < min ) ? dot : min;
	max = ( dot > max ) ? dot : max;
	
	// right, bottom
	corner.Init ( 1.0f, -1.0f );
	corner.Sub ( loc );
	dot = norm.Dot ( corner );
	
	min = ( dot < min ) ? dot : min;
	max = ( dot > max ) ? dot : max;
	
	// left, bottom
	corner.Init ( -1.0f, -1.0f );
	corner.Sub ( loc );
	dot = norm.Dot ( corner );
	
	min = ( dot < min ) ? dot : min;
	max = ( dot > max ) ? dot : max;
	
	// Get the start andstop grids
	s32 start = ( s32 )( min / size ) - 1;
	s32 stop = ( s32 )( max / size ) + 1;
	
	// Set the pen to the first...
	USVec2D pen = norm;
	pen.Scale (( float )start * size );
	pen.Add ( loc );
	
	// Step along the axis to draw perpendicular grid lines
	ZLRect viewRect;
	viewRect.Init ( -1.0f, -1.0f, 1.0f, 1.0f );
	
	for ( ; start < stop; ++start ) {
		
		USVec2D p0;
		USVec2D p1;
		
		if ( viewRect.GetIntersection ( pen, perpNorm, p0, p1 )) {
			
			invMtx.Transform ( p0 );
			invMtx.Transform ( p1 );
			
			MOAIDraw::DrawLine ( p0, p1 );
		}
		
		pen.Add ( vec );
	}
}

//----------------------------------------------------------------//
void MOAIDraw::DrawBoxOutline ( const ZLBox& box ) {

	MOAIDraw::DrawLine ( box.mMin.mX, box.mMin.mY, box.mMin.mZ, box.mMax.mX, box.mMin.mY, box.mMin.mZ );
	MOAIDraw::DrawLine ( box.mMin.mX, box.mMin.mY, box.mMin.mZ, box.mMin.mX, box.mMax.mY, box.mMin.mZ );
	MOAIDraw::DrawLine ( box.mMin.mX, box.mMin.mY, box.mMin.mZ, box.mMin.mX, box.mMin.mY, box.mMax.mZ );
	
	MOAIDraw::DrawLine ( box.mMax.mX, box.mMax.mY, box.mMax.mZ, box.mMin.mX, box.mMax.mY, box.mMax.mZ );
	MOAIDraw::DrawLine ( box.mMax.mX, box.mMax.mY, box.mMax.mZ, box.mMax.mX, box.mMin.mY, box.mMax.mZ );
	MOAIDraw::DrawLine ( box.mMax.mX, box.mMax.mY, box.mMax.mZ, box.mMax.mX, box.mMax.mY, box.mMin.mZ );
	
	MOAIDraw::DrawLine ( box.mMax.mX, box.mMin.mY, box.mMin.mZ, box.mMax.mX, box.mMax.mY, box.mMin.mZ );
	MOAIDraw::DrawLine ( box.mMax.mX, box.mMin.mY, box.mMin.mZ, box.mMax.mX, box.mMin.mY, box.mMax.mZ );

	MOAIDraw::DrawLine ( box.mMin.mX, box.mMax.mY, box.mMin.mZ, box.mMax.mX, box.mMax.mY, box.mMin.mZ );
	MOAIDraw::DrawLine ( box.mMin.mX, box.mMax.mY, box.mMin.mZ, box.mMin.mX, box.mMax.mY, box.mMax.mZ );
	
	MOAIDraw::DrawLine ( box.mMin.mX, box.mMin.mY, box.mMax.mZ, box.mMax.mX, box.mMin.mY, box.mMax.mZ );
	MOAIDraw::DrawLine ( box.mMin.mX, box.mMin.mY, box.mMax.mZ, box.mMin.mX, box.mMax.mY, box.mMax.mZ );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawEllipseFill ( const ZLRect& rect, u32 steps ) {

	float xRad = ( rect.mXMax - rect.mXMin ) * 0.5f;
	float yRad = ( rect.mYMax - rect.mYMin ) * 0.5f;

	MOAIDraw::DrawEllipseFill ( rect.mXMin + xRad, rect.mYMin + yRad, xRad, yRad, steps );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawEllipseFill ( float x, float y, float xRad, float yRad, u32 steps ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	float angle = ( float )TWOPI / ( float )steps;
	float angleStep = ( float )PI;
	
	gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );
	
	for ( u32 i = 0; i < steps; ++i, angleStep += angle ) {
		gfxDevice.WriteVtx (
			x + ( Sin ( angleStep ) * xRad ),
			y + ( Cos ( angleStep ) * yRad ),
			0.0f
		);
		gfxDevice.WriteFinalColor4b ();
	}
	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
void MOAIDraw::DrawEllipseOutline ( const ZLRect& rect, u32 steps ) {
	
	float xRad = ( rect.mXMax - rect.mXMin ) * 0.5f;
	float yRad = ( rect.mYMax - rect.mYMin ) * 0.5f;

	MOAIDraw::DrawEllipseOutline ( rect.mXMin + xRad, rect.mYMin + yRad, xRad, yRad, steps );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawEllipseOutline ( float x, float y, float xRad, float yRad, u32 steps ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	float angle = ( float )TWOPI / ( float )steps;
	float angleStep = ( float )PI;
	
	gfxDevice.BeginPrim ( ZGL_PRIM_LINE_LOOP );
	
	for ( u32 i = 0; i < steps; ++i, angleStep += angle ) {
		gfxDevice.WriteVtx (
			x + ( Sin ( angleStep ) * xRad ),
			y + ( Cos ( angleStep ) * yRad ),
			0.0f
		);
		gfxDevice.WriteFinalColor4b ();
	}
	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
void MOAIDraw::DrawGrid ( const ZLRect& rect, u32 xCells, u32 yCells ) {

	if ( xCells > 1 ) {
		float xStep = rect.Width () / ( float )xCells;
		for ( u32 i = 1; i < xCells; ++i ) {
			float x = rect.mXMin + (( float )i * xStep );
			USVec2D v0 ( x, rect.mYMin );
			USVec2D v1 ( x, rect.mYMax );
			
			MOAIDraw::DrawLine ( v0, v1 );
		}
	}

	if ( yCells > 1 ) {
		float yStep = rect.Height () / ( float )yCells;
		for ( u32 i = 1; i < yCells; ++i ) {
			float y = rect.mYMin + (( float )i * yStep );
			USVec2D v0 ( rect.mXMin, y );
			USVec2D v1 ( rect.mXMax, y );
			
			MOAIDraw::DrawLine ( v0, v1 );
		}
	}

	MOAIDraw::DrawRectOutline ( rect );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawLine ( const USVec2D& v0, const USVec2D& v1 ) {

	MOAIDraw::DrawLine ( v0.mX, v0.mY, v1.mX, v1.mY );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawLine ( float x0, float y0, float x1, float y1 ) {
	
	MOAIDraw::DrawLine ( x0, y0, 0.0f, x1, y1, 0.0f );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawLine ( const ZLVec3D& v0, const ZLVec3D& v1 ) {

	MOAIDraw::DrawLine ( v0.mX, v0.mY, v0.mZ, v1.mX, v1.mY, v1.mZ );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawLine ( float x0, float y0, float z0, float x1, float y1, float z1 ) {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	gfxDevice.SetPrimType ( ZGL_PRIM_LINES );

	gfxDevice.BeginPrim ();
	
		gfxDevice.WriteVtx ( x0, y0, z0 );
		gfxDevice.WriteFinalColor4b ();
		
		gfxDevice.WriteVtx ( x1, y1, z1 );
		gfxDevice.WriteFinalColor4b ();
	
	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
void MOAIDraw::DrawLuaParams ( lua_State* L, u32 primType ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	MOAILuaState state ( L );

	u32 total = state.GetTop () >> 1;
	
	gfxDevice.BeginPrim ( primType );
	
	for ( u32 i = 0; i < total; ++i ) {
		
		u32 idx = ( i << 1 ) + 1;
		
		float x = state.GetValue < float >( idx, 0.0f );
		float y = state.GetValue < float >( idx + 1, 0.0f );
		
		gfxDevice.WriteVtx ( x, y, 0.0f );
		gfxDevice.WriteFinalColor4b ();
	}
	
	gfxDevice.EndPrim ();
}


//----------------------------------------------------------------//
void MOAIDraw::DrawLuaArray ( lua_State* L, u32 primType ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	MOAILuaState state ( L );

	float x = 0.0f;
	float y = 0.0f;
	
	gfxDevice.BeginPrim ( primType );

	/*
	See http://www.lua.org/manual/5.0/manual.html#3.11 for iterator explanation
	*/
	u32 counter = 0;
	lua_pushnil ( L );
    while ( lua_next ( L, 1 ) != 0 ) {
		// Assuming odd-numbered array entries to be x-coordinate (abscissa),
		// even-numbered array entries to be y-coordinate (oordinate).
		if ( counter % 2 == 0 ) {
			x = state.GetValue < float >( -1, 0.0f );
		} else {
			y = state.GetValue < float >( -1, 0.0f );
			gfxDevice.WriteVtx ( x, y );
			gfxDevice.WriteFinalColor4b ();
		}
		++counter;
		lua_pop ( L, 1 );
	}

	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
void MOAIDraw::DrawPoint ( const USVec2D& loc ) {

	MOAIDraw::DrawPoint ( loc.mX, loc.mY );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawPoint ( float x, float y ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	gfxDevice.SetPrimType ( ZGL_PRIM_POINTS );

	gfxDevice.BeginPrim ();
		gfxDevice.WriteVtx ( x, y, 0.0f );
		gfxDevice.WriteFinalColor4b ();
	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
void MOAIDraw::DrawQuad ( const ZLQuad& quad ) {

	MOAIDraw::DrawLine ( quad.mV [ 0 ].mX, quad.mV [ 0 ].mY, quad.mV [ 1 ].mX, quad.mV [ 1 ].mY );
	MOAIDraw::DrawLine ( quad.mV [ 1 ].mX, quad.mV [ 1 ].mY, quad.mV [ 2 ].mX, quad.mV [ 2 ].mY );
	MOAIDraw::DrawLine ( quad.mV [ 2 ].mX, quad.mV [ 2 ].mY, quad.mV [ 3 ].mX, quad.mV [ 3 ].mY );
	MOAIDraw::DrawLine ( quad.mV [ 3 ].mX, quad.mV [ 3 ].mY, quad.mV [ 0 ].mX, quad.mV [ 0 ].mY );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawRay ( float x, float y, float dx, float dy ) {
	
	USVec2D loc ( x, y );
	USVec2D vec ( dx, dy );
	
	ZLMatrix4x4 mtx = MOAIGfxDevice::Get ().GetViewProjMtx ();
	
	ZLMatrix4x4 invMtx;
	invMtx.Inverse ( mtx );
	
	mtx.Transform ( loc );
	mtx.TransformVec ( vec );
	
	ZLRect viewRect;
	viewRect.Init ( -1.0f, -1.0f, 1.0f, 1.0f );
	
	USVec2D p0;
	USVec2D p1;
	
	if ( viewRect.GetIntersection ( loc, vec, p0, p1 )) {
		
		invMtx.Transform ( p0 );
		invMtx.Transform ( p1 );
		
		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
		
		gfxDevice.BeginPrim ( ZGL_PRIM_LINES );
		
			gfxDevice.WriteVtx ( p0.mX, p0.mY, 0.0f );
			gfxDevice.WriteFinalColor4b ();
			
			gfxDevice.WriteVtx ( p1.mX, p1.mY, 0.0f );
			gfxDevice.WriteFinalColor4b ();

		gfxDevice.EndPrim ();
	}
}

//----------------------------------------------------------------//
void MOAIDraw::DrawRectEdges ( ZLRect rect, u32 edges ) {

	rect.Bless ();
	
	// right
	if ( edges & ZLRect::kRight ) {
		MOAIDraw::DrawLine ( rect.mXMax, rect.mYMin, rect.mXMax, rect.mYMax );
	}

	// top
	if ( edges & ZLRect::kTop ) {			
		MOAIDraw::DrawLine ( rect.mXMin, rect.mYMin, rect.mXMax, rect.mYMin );
	}

	// left
	if ( edges & ZLRect::kLeft ) {			
		MOAIDraw::DrawLine ( rect.mXMin, rect.mYMin, rect.mXMin, rect.mYMax );
	}

	// bottom
	if ( edges & ZLRect::kBottom ) {			
		MOAIDraw::DrawLine ( rect.mXMin, rect.mYMax, rect.mXMax, rect.mYMax );
	}	
}



//----------------------------------------------------------------//
void MOAIDraw::DrawRectFill ( ZLRect rect, bool asTriStrip ) {
	rect.Bless ();
	MOAIDraw::DrawRectFill ( rect.mXMin, rect.mYMin, rect.mXMax, rect.mYMax, asTriStrip );
}


//----------------------------------------------------------------//
void MOAIDraw::DrawRectFill ( float left, float top, float right, float bottom, bool asTriStrip ) {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	if ( asTriStrip ) {

		gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_STRIP );
	
			gfxDevice.WriteVtx ( left, top, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( right, top, 0.0f);
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( left, bottom, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( right, bottom, 0.0f);
			gfxDevice.WriteFinalColor4b ();
	
		gfxDevice.EndPrim ();
	}
	else {
		
		// Tri 1
		gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLES );
	
			gfxDevice.WriteVtx ( left, top, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( right, top, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( right, bottom, 0.0f );
			gfxDevice.WriteFinalColor4b ();
			
		gfxDevice.EndPrim ();
		
		// Tri 2
		gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLES );

			gfxDevice.WriteVtx ( right, bottom, 0.0f );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left, bottom, 0.0f );
			gfxDevice.WriteFinalColor4b ();
			
			gfxDevice.WriteVtx ( left, top, 0.0f );
			gfxDevice.WriteFinalColor4b ();
	
		gfxDevice.EndPrim ();
	}
}

//----------------------------------------------------------------//
void MOAIDraw::DrawRectOutline ( const ZLRect& rect ) {
	
	MOAIDraw::DrawRectOutline ( rect.mXMin, rect.mYMin, rect.mXMax, rect.mYMax );
}

//----------------------------------------------------------------//
void MOAIDraw::DrawRectOutline ( float left, float top, float right, float bottom ) {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	gfxDevice.BeginPrim ( ZGL_PRIM_LINE_LOOP );
	
		gfxDevice.WriteVtx ( left, top, 0.0f );
		gfxDevice.WriteFinalColor4b ();
		
		gfxDevice.WriteVtx ( right, top, 0.0f );
		gfxDevice.WriteFinalColor4b ();
		
		gfxDevice.WriteVtx ( right, bottom, 0.0f );
		gfxDevice.WriteFinalColor4b ();
		
		gfxDevice.WriteVtx ( left, bottom, 0.0f );
		gfxDevice.WriteFinalColor4b ();
	
	gfxDevice.EndPrim ();
}





//----------------------------------------------------------------//
void MOAIDraw::DrawTextureUV (MOAITexture* texture,
							  float left, float top, float right, float bottom, 							
							  float rot,
							  float u0,float v0,float u1,float v1) {

	if ( texture ) {	

		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
		gfxDevice.SetTexture ( texture );
		gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );
		MOAIQuadBrush::BindVertexFormat ( gfxDevice );
	
		ZLAffine3D mtx;	
		mtx.RotateZ(rot);	
		//mtx.TransformZ(-1);
	
		
		MOAIQuadBrush quad;	
		quad.SetVerts ( left, top, right, bottom );	
		quad.SetUVs ( u0, v0, u1, v1 );

		quad.TransformVerts(mtx);		
		quad.Draw ();



	   MOAIDraw::Bind ();

	}
}

int MOAIDraw::_drawTextureUV ( lua_State* L ) {

	MOAILuaState state ( L );
	
	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 1 );

	float x0 = state.GetValue < float >( 2, 0.0f );
	float y0 = state.GetValue < float >( 3, 0.0f );
	float x1 = state.GetValue < float >( 4, 0.0f );
	float y1 = state.GetValue < float >( 5, 0.0f );

	//float sclX = state.GetValue < float >( 6, 0.0f );
	//float sclY = state.GetValue < float >( 7, 0.0f );

	float rot = state.GetValue < float >( 6, 0.0f );

	float u0 = state.GetValue < float >( 7, 0.0f );
	float v0 = state.GetValue < float >( 8, 0.0f );
	float u1 = state.GetValue < float >( 9, 0.0f );
	float v1 = state.GetValue < float >( 10, 0.0f );


	MOAIDraw::DrawTextureUV (texture, 
							x0, y0, x1, y1, 
							rot,
							u0,v0,u1,v1 
							);
	return 0;
}






//----------------------------------------------------------------//
void MOAIDraw::DrawTexture ( float left, float top, float right, float bottom, MOAITexture* texture ) {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	if ( texture ) {	

	
		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ZERO );
		gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA ); //DEFUALT

		gfxDevice.SetTexture ( texture );
		gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );	
		
		MOAIQuadBrush::BindVertexFormat ( gfxDevice );

		MOAIQuadBrush quad;
		quad.SetVerts ( left, top, right, bottom );
		quad.SetUVs ( 0, 0, 1, 1 );		
		quad.Draw ();	

		//THIS JUST RESETESTS NOR NEEDED
		//MOAIDraw::Bind ();

	}
}

//----------------------------------------------------------------//
void MOAIDraw::DrawVertexArray ( const ZLVec3D* verts, u32 count, u32 color, u32 primType ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	gfxDevice.SetPrimType ( primType );
	gfxDevice.SetPenColor ( color );
	
	gfxDevice.BeginPrim ();
	
	for ( u32 i = 0; i < count; ++i ) {
		const ZLVec3D& vtx = verts [ i ];
		gfxDevice.WriteVtx ( vtx );
		gfxDevice.WriteFinalColor4b ();
	}

	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
void MOAIDraw::DrawVertexArray2D ( const float* verts, u32 count, u32 color, u32 primType ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	gfxDevice.SetPrimType ( primType );
	gfxDevice.SetPenColor ( color );
	
	gfxDevice.BeginPrim ();
	
	for ( u32 i = 0; i < count; ++i ) {
		u32 v = i << 1;
		gfxDevice.WriteVtx ( verts [ v ], verts [ v + 1 ], 0.0f );
		gfxDevice.WriteFinalColor4b ();
	}

	gfxDevice.EndPrim ();
}



//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//**************************************************************************************************
//SHADER
int	MOAIDraw::_setShader ( lua_State* L ) {

    MOAILuaState state ( L );        
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
    MOAIShader  * shader = state.GetLuaObject < MOAIShader >( 1, true );
    gfxDevice.SetShader(shader);

return 0;
};


//***********************************************************************
//***********************************************************************
//***********************************************************************
int MOAIDraw::_drawRingList ( lua_State* L ) {   
	MOAILuaState state ( L );

	float x   = 0.0f;
	float y   = 0.0f;
    float rad = 0.0f;

    float red    = 0.0f;
    float green  = 0.0f;
    float blue   = 0.0f;
    float alpha  = 0.0f;

    u32 steps = 1;

  

	float angle     = ( float )TWOPI / ( float )steps;
	float angleStep = ( float )PI;


    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
    gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );
    
       //  gfxDevice.setPrimeSize(50000000000);


    gfxDevice.SetPrimType (  ZGL_PRIM_LINES );
 



    u32 counter = 0;    
    u32 total   = 0;
    lua_pushnil ( L );


    	gfxDevice.BeginPrim ();


 while ( lua_next ( L, 1 ) != 0 ) {


        //CORDINATE
		if (counter == 0) {x    =state.GetValue < float >( -1, 0.0f );};
		if (counter == 1) {y    =state.GetValue < float >( -1, 0.0f );};
        if (counter == 2) {rad  =state.GetValue < float >( -1, 0.0f );};
        //COLOR    
		if (counter == 3) {red    =state.GetValue < float >( -1, 0.0f );};
		if (counter == 4) {green  =state.GetValue < float >( -1, 0.0f );};
		if (counter == 5) {blue   =state.GetValue < float >( -1, 0.0f );};
		if (counter == 6) {alpha  =state.GetValue < float >( -1, 0.0f );};

        // printf("\n");

        ///DRAW
		if (counter == 6) {
            counter = -1;
         
    
                   //COLOR
                   // gfxDevice.SetPenColor (red,green,blue,alpha );	

	               for ( u32 j = 0; j < steps; ++j, angleStep += angle ) {

                       //gfxDevice.WriteVtx ( 0,0,0);
                      // gfxDevice.WriteFinalColor4b ();
                      //  total++;

                               gfxDevice.WriteVtx (  x + ( Sin ( angleStep )* rad ),y + ( Cos ( angleStep )* rad ), 0.0f);
		                        gfxDevice.WriteFinalColor4b ();
                                total++;


                                gfxDevice.WriteVtx (  x + ( Sin ( angleStep )* rad ),y + ( Cos ( angleStep )* rad ), 0.0f);
		                        gfxDevice.WriteFinalColor4b ();
                                total++; 
                       
                           // printf("total %i \n",total);

                               // gfxDevice.WriteVtx ( x + ( Sin ( angleStep+angle )* rad ),y + ( Cos ( angleStep+angle )* rad ), 0.0f);
		                       // gfxDevice.WriteFinalColor4b ();
                                //total++; 
	                };


       };

		++counter;
		lua_pop ( L, 1 );
 };


 //    printf(">>>CARSH total %i \n",total);
    	gfxDevice.EndPrim ();    


   
  

    return true;

};
//***********************************************************************
//***********************************************************************
//***********************************************************************


int MOAIDraw::_drawCircleList ( lua_State* L ) {

    return true;

};




//***********************************************************************
//***********************************************************************
//***********************************************************************

int MOAIDraw::_drawRectList ( lua_State* L ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	MOAILuaState state ( L );

	float left   = 0.0f;
	float top    = 0.0f;
	float right  = 0.0f;
	float bottom = 0.0f;

    float red    = 0.0f;
    float green  = 0.0f;
    float blue   = 0.0f;
    float alpha  = 0.0f;

	float cacheA = 0.0f;
	float cacheB = 0.0f;

	int total    = 0;

    gfxDevice.SetPrimType (  ZGL_PRIM_TRIANGLE_STRIP );
 
    //gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );
	

    //prop[i]:setBlendMode(MOAIProp2D.GL_SRC_ALPHA, MOAIProp2D.GL_ONE_MINUS_SRC_ALPHA)

    //gfxDevice.Flush ();
   // gfxDevice.ResetState();




//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
//DRAW LOOP
//
//u32 counter = 0;
//
//gfxDevice.BeginPrim ();
//
//
//    for(int y=0; y<125; y++) {
//
//           for(int x=0; x<125; x++) {
//
//
//              float loc_x =x*5;
//               float loc_y =y*5;
//
//
//               if (counter > 0) {
//
//                      // //CACHE
//	                 gfxDevice.WriteVtx ( cacheA, cacheB);
//	                 gfxDevice.WriteFinalColor4b ();
//
//	               // //NEW
//	                 gfxDevice.WriteVtx (loc_x, loc_y);
//	                 gfxDevice.WriteFinalColor4b ();
//
//               };         
//  
// 
//
//                //COLOR
//                        gfxDevice.SetPenColor (1,0,0,1 );	
//
//                        //TOP LEFT
//                        gfxDevice.WriteVtx ( loc_x, loc_y);
//                        gfxDevice.WriteFinalColor4b ();	
//	
//                        //TOP RIGHT	
//                        gfxDevice.WriteVtx ( loc_x, loc_y+4);
//                        gfxDevice.WriteFinalColor4b ();	
//
//                        //BOTTOM LEFT						
//                        gfxDevice.WriteVtx ( loc_x+4, loc_y);
//                        gfxDevice.WriteFinalColor4b ();	
//
//                        //BOTTOM RIGHT
//                        gfxDevice.WriteVtx ( loc_x+4, loc_y+4);
//                        gfxDevice.WriteFinalColor4b ();	
//
//                            //******************************
//                            //CACHE
//                            cacheA = loc_x+4;
//                            cacheB = loc_y+4;
////       
//
//               ++counter;
//           };          
//    };
//
//gfxDevice.EndPrim ();
















//********************************************************************************************************
//********************************************************************************************************
//********************************************************************************************************
//********************************************************************************************************
//FAST GEO

gfxDevice.BeginPrim ();

	u32 counter = 0;
	lua_pushnil ( L );

    while ( lua_next ( L, 1 ) != 0 ) {


        //CORDINATE
		if (counter == 0)       left    =state.GetValue < float >( -1, 0.0f );
		else if (counter == 1)  top     =state.GetValue < float >( -1, 0.0f );
		else if (counter == 2)  right   =state.GetValue < float >( -1, 0.0f );
		else if (counter == 3)  bottom  =state.GetValue < float >( -1, 0.0f );		
        //COLOR    
		else if (counter == 4)  red    =state.GetValue < float >( -1, 0.0f );
		else if (counter == 5)  green  =state.GetValue < float >( -1, 0.0f );
		else if (counter == 6)  blue   =state.GetValue < float >( -1, 0.0f );
		else if (counter == 7) {            
                                alpha  =state.GetValue < float >( -1, 0.0f );	

		//if (counter == 7) {

            counter = -1;
            total++; //TOTAL NUMBER


            ////JUMP
            if (total != 1) {

	           // //CACHE
	             gfxDevice.WriteVtx ( cacheA, cacheB);
	             gfxDevice.WriteFinalColor4b ();

	           // //NEW
	             gfxDevice.WriteVtx ( left, top);
	             gfxDevice.WriteFinalColor4b ();

            };


                //COLOR
                gfxDevice.SetPenColor (red,green,blue,alpha );	

                        //TOP LEFT
                        gfxDevice.WriteVtx ( left, top);
                        gfxDevice.WriteFinalColor4b ();	
	
                        //TOP RIGHT	
                        gfxDevice.WriteVtx ( left, bottom);
                        gfxDevice.WriteFinalColor4b ();	

                        //BOTTOM LEFT						
                        gfxDevice.WriteVtx ( right, top);
                        gfxDevice.WriteFinalColor4b ();	

                        //BOTTOM RIGHT
                        gfxDevice.WriteVtx ( right, bottom);
                        gfxDevice.WriteFinalColor4b ();	



                            //******************************
                            //CACHE
                            cacheA = right;
                            cacheB = bottom;



		};

		++counter;
		lua_pop ( L, 1 );

	}
	


	gfxDevice.EndPrim ();





//********************************************************************************************************
//********************************************************************************************************
//********************************************************************************************************
//********************************************************************************************************
//BORDER
//
//gfxDevice.SetPrimType (  ZGL_PRIM_LINES );
//gfxDevice.setPrimeSize((total*2)*4);
//gfxDevice.BeginPrim ( );
//
//
//
// counter = 0;
// total   = 0;
//
//	lua_pushnil ( L );
//
//    while ( lua_next ( L, 1 ) != 0 ) {
//
//
//        //CORDINATE
//		if (counter == 0) {left    =state.GetValue < float >( -1, 0.0f );};
//		if (counter == 1) {top     =state.GetValue < float >( -1, 0.0f );};
//		if (counter == 2) {right   =state.GetValue < float >( -1, 0.0f );};
//		if (counter == 3) {bottom  =state.GetValue < float >( -1, 0.0f );};		
//        //COLOR    
//		if (counter == 4) {red    =state.GetValue < float >( -1, 0.0f );};
//		if (counter == 5) {green  =state.GetValue < float >( -1, 0.0f );};
//		if (counter == 6) {blue   =state.GetValue < float >( -1, 0.0f );};
//		if (counter == 7) {alpha  =state.GetValue < float >( -1, 0.0f );};	
//
//		if (counter == 7) {
//
//               counter = -1;
//
//                //COLOR
//                gfxDevice.SetPenColor (red,green,blue,1 );
//  
//
//                //TOP
//                gfxDevice.WriteVtx ( left,top );
//		        gfxDevice.WriteFinalColor4b ();
//		
//		        gfxDevice.WriteVtx ( right, top );
//		        gfxDevice.WriteFinalColor4b ();
//
//                //LEFT
//                gfxDevice.WriteVtx ( left,top);
//		        gfxDevice.WriteFinalColor4b ();
//		
//		        gfxDevice.WriteVtx ( left, bottom );
//		        gfxDevice.WriteFinalColor4b ();
//
//              //RIGHT
//                gfxDevice.WriteVtx ( right,top);
//		        gfxDevice.WriteFinalColor4b ();
//		
//		        gfxDevice.WriteVtx ( right, bottom );
//		        gfxDevice.WriteFinalColor4b ();
//
//
//              //BOTTOM
//                gfxDevice.WriteVtx ( right,bottom );
//		        gfxDevice.WriteFinalColor4b ();
//		
//		        gfxDevice.WriteVtx ( left, bottom );
//		        gfxDevice.WriteFinalColor4b ();
//
//
//		};
//
//		++counter;
//		lua_pop ( L, 1 );
//
//	}
//	
//	
//	gfxDevice.EndPrim ();
//
//


    return 1;

}

//*************************************************************************************
//*************************************************************************************
//*************************************************************************************
int MOAIDraw::_drawLineList ( lua_State* L ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	MOAILuaState state ( L );

    //float send_size = state.GetValue < float >( 1, 0.0f );

    //print()


  


	float x1   = 0.0f;
	float y1    = 0.0f;
	float x2  = 0.0f;
	float y2 = 0.0f;

    float red    = 0.0f;
    float green  = 0.0f;
    float blue   = 0.0f;
    float alpha  = 0.0f;

	int total    = 0;

    ///gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );
    gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

	gfxDevice.SetPrimType (  ZGL_PRIM_LINES ); 


    gfxDevice.BeginPrim ();

	u32 counter = 0;

	lua_pushnil ( L );

    while ( lua_next ( L, 1 ) != 0 ) {


        //CORDINATE
		if (counter == 0) {x1    =state.GetValue < float >( -1, 0.0f );};
		if (counter == 1) {y1     =state.GetValue < float >( -1, 0.0f );};
		if (counter == 2) {x2   =state.GetValue < float >( -1, 0.0f );};
		if (counter == 3) {y2  =state.GetValue < float >( -1, 0.0f );};		
        //COLOR    
		if (counter == 4) {red    =state.GetValue < float >( -1, 0.0f );};
		if (counter == 5) {green  =state.GetValue < float >( -1, 0.0f );};
		if (counter == 6) {blue   =state.GetValue < float >( -1, 0.0f );};
		if (counter == 7) {alpha  =state.GetValue < float >( -1, 0.0f );};	

		if (counter == 7) {

            counter = -1;
            total++; 

                //COLOR
                gfxDevice.SetPenColor (red,green,blue,alpha );  

                //POINTS
                gfxDevice.WriteVtx ( x1,y1 );
		        gfxDevice.WriteFinalColor4b ();
		
		        gfxDevice.WriteVtx ( x2, y2 );
		        gfxDevice.WriteFinalColor4b ();


		};

		++counter;
		lua_pop ( L, 1 );

	};
	

      //gfxDevice.setPrimeSize(total*2);
	gfxDevice.EndPrim ();


return true;


};



//*******************************************************
//PRIME

int MOAIDraw::_rectStart ( lua_State* L ) {

     MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
     gfxDevice.SetPrimType (  ZGL_PRIM_TRIANGLE_STRIP );
     gfxDevice.BeginPrim ();
     rect_x = 0;
     rect_x = 0;
     rect_step = 0;

    return true;
}


int MOAIDraw::_rectEnd ( lua_State* L ) {
     MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.EndPrim ();
      rect_step = -1;
     return true;
}

int MOAIDraw::_rectDraw ( lua_State* L ) {

    MOAILuaState state ( L );
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

    float left = state.GetValue < float >( 1, 0.0f );
	float top   = state.GetValue < float >( 2, 0.0f );
	float right = state.GetValue < float >( 3, 0.0f );
	float bottom = state.GetValue < float >( 4, 0.0f );


    float red = state.GetValue < float >( 5, 0.0f );
	float green = state.GetValue < float >( 6, 0.0f );
	float blue = state.GetValue < float >( 7, 0.0f );
	float alpha = state.GetValue < float >( 8, 0.0f );

    gfxDevice.SetPenColor (red,green,blue,alpha );  

    ++rect_step;

        if (rect_step > 1) {

                gfxDevice.WriteVtx ( rect_x, rect_y, 0.0f );
			    gfxDevice.WriteFinalColor4b ();

    		    gfxDevice.WriteVtx ( left, top, 0.0f );
			    gfxDevice.WriteFinalColor4b ();	
			
        };


    		gfxDevice.WriteVtx ( left, top, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( right, top, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( left, bottom, 0.0f );
			gfxDevice.WriteFinalColor4b ();
		
			gfxDevice.WriteVtx ( right, bottom, 0.0f );
			gfxDevice.WriteFinalColor4b ();

            rect_x = right;
            rect_y = bottom;

            //WRITE CACHE



     return true;
}




//
//
//int MOAIDraw::_textureStart ( lua_State* L ) {
//MOAILuaState state ( L );
//MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
//gfxDevice.SetPrimType (  ZGL_PRIM_TRIANGLE_STRIP );
//// glShadeModel(GL_FLAT);
//gfxDevice.BeginPrim ();
//return 0;
//};
//
//int MOAIDraw::_textureColor ( lua_State* L ) {
//MOAILuaState state ( L );
//float red = state.GetValue < float >( 1, 0.0f );
//float green = state.GetValue < float >( 2, 0.0f );
//float blue = state.GetValue < float >( 3, 0.0f );
//float alpha = state.GetValue < float >( 4, 0.0f );
//MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
//gfxDevice.SetPenColor (red,green,blue,alpha ); 
//return 0;
//};
//
//
//int MOAIDraw::_shadowEnd ( lua_State* L ) {
//MOAILuaState state ( L );
//MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
//gfxDevice.EndPrim ();
//return 0;
//};


//***********************************************************************************
//***********************************************************************************
//***********************************************************************************
//***********************************************************************************

int MOAIDraw::_shadowStart ( lua_State* L ) {
MOAILuaState state ( L );
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetPrimType (  ZGL_PRIM_TRIANGLE_STRIP );
	gfxDevice.BeginPrim ();
return 0;
};

int MOAIDraw::_shadowColor ( lua_State* L ) {
MOAILuaState state ( L );
float red = state.GetValue < float >( 1, 0.0f );
float green = state.GetValue < float >( 2, 0.0f );
float blue = state.GetValue < float >( 3, 0.0f );
float alpha = state.GetValue < float >( 4, 0.0f );
MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
gfxDevice.SetPenColor (red,green,blue,alpha ); 
return 0;
};


int MOAIDraw::_shadowVtx ( lua_State* L ) {
MOAILuaState state ( L );
float x = state.GetValue < float >( 1, 0.0f );
float y = state.GetValue < float >( 2, 0.0f );
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	//printf("%f %f",x,y);
	gfxDevice.WriteVtx ( x,y );
	gfxDevice.WriteFinalColor4b ();
return 0;
};



int MOAIDraw::_shadowEnd ( lua_State* L ) {
MOAILuaState state ( L );
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.EndPrim ();
return 0;
};


//***********************************************************************************
//***********************************************************************************
//***********************************************************************************

int MOAIDraw::_shadowFan( lua_State* L ) {
MOAILuaState state ( L );
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 2 );
	gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );	//SHADER		
	gfxDevice.SetTexture ( texture );							//TEXTURE	
	gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE



	float x = 0.0f;
	float y = 0.0f;
	
	gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );


	u32 counter = 0;
	lua_pushnil ( L );

	printf("\n");

    while ( lua_next ( L, 1 ) != 0 ) {

		if ( counter % 2 == 0 ) {
			x = state.GetValue < float >( -1, 0.0f );
		} else {
			y = state.GetValue < float >( -1, 0.0f );
			gfxDevice.WriteVtx ( x, y );
			//printf("%f %f \n",x,y);
			gfxDevice.WriteUV(0.0f,1.0f);	
			gfxDevice.WriteFinalColor4b ();

						
				

		}
		++counter;
		lua_pop ( L, 1 );
	}

	gfxDevice.EndPrim ();

return 0;
};






//**********************************************************************


int MOAIDraw::_drawLight ( lua_State* L ) {

	MOAILuaState state ( L );
	
	float x		 = state.GetValue < float >( 1, 0.0f );
	float y		 = state.GetValue < float >( 2, 0.0f );
	float radius = state.GetValue < float >( 3, 0.0f );

	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 4 );

	float step = state.GetValue < float >( 5, 0.0f );
	radius = radius - (step*0.5);
	//float mod = (step*0.5);

	if ( texture ) {	
	
		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

						//printf("2\n");
						//gfxDevice.ResetState();
						//gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ ); //TO VIEWPORT ?? NOT SURE
						//gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_MODEL );
						//gfxDevice.SetUVMtxMode ( MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE );





		gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );	//SHADER		
		gfxDevice.SetTexture ( texture );							//TEXTURE	
		gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE

							//gfxDevice.SetDepthMask(true);	
							//gfxDevice.SetDepthFunc ( ( u32 )ZGL_DEPTH_LEQUAL );	
							//gfxDevice.SetDepthFunc ( ( u32 )ZGL_DEPTH_NEVER );

		gfxDevice.BeginPrim (ZGL_PRIM_TRIANGLE_STRIP ); //PRIME

	
		//CONVERT TO TOP LEFT ??


		
			
					
			//****************************************************************************
			//DRAW STRIPS OVER LIGHT
					gfxDevice.SetPenColor (0,0,0,1 );

				//TRI-ANGLE
					gfxDevice.WriteVtx ( x-50, y-50, step );
					gfxDevice.WriteUV(0.0f,1.0f);			
					gfxDevice.WriteFinalColor4b ();

					gfxDevice.WriteVtx ( x+50, y-50, step );	
					gfxDevice.WriteUV(1.0f,1.0f);					
					gfxDevice.WriteFinalColor4b ();

					gfxDevice.WriteVtx (x-50, y+50, step);
					gfxDevice.WriteUV(0.0f,0.0f);			
					gfxDevice.WriteFinalColor4b ();

	
//***************************************************************************************************
//DEGEN

					gfxDevice.SetPenColor (0,0,0,0 );
					gfxDevice.WriteVtx (x-50, y+50, step);
					gfxDevice.WriteUV(0.0f,0.0f);			
					gfxDevice.WriteFinalColor4b ();

					gfxDevice.WriteVtx (x-radius, y-radius, step-0.1 );
					gfxDevice.WriteUV(0.0f,0.0);			
					gfxDevice.WriteFinalColor4b ();	


//***************************************************************************************

					gfxDevice.SetPenColor (1,0,1,1 );

				//TRI-ANGLE
					gfxDevice.WriteVtx ( x-radius, y-radius, step-0.1 );
					gfxDevice.WriteUV(0.0f,1.0f);			
					gfxDevice.WriteFinalColor4b ();

					gfxDevice.WriteVtx ( x+radius, y-radius, step-0.1);	
					gfxDevice.WriteUV(1.0f,1.0f);					
					gfxDevice.WriteFinalColor4b ();

					gfxDevice.WriteVtx (x-radius, y+radius, step-0.1 );
					gfxDevice.WriteUV(0.0f,0.0f);			
					gfxDevice.WriteFinalColor4b ();

					gfxDevice.WriteVtx (x+radius, y+radius,step-0.1 );
					gfxDevice.WriteUV(1.0f,0.0f);			
					gfxDevice.WriteFinalColor4b ();

//***************************************************************************************************
//DEGEN
//
//					gfxDevice.WriteVtx (x+radius, y+radius, -1 );
//					gfxDevice.WriteUV(1.0f,0.0f);			
//					gfxDevice.WriteFinalColor4b ();
//
//					gfxDevice.WriteVtx ( x-50, y-50, 1 );
//					gfxDevice.WriteUV(0.0f,1.0f);			
//					gfxDevice.WriteFinalColor4b ();
//
//
//
////***************************************************************************************************
//					gfxDevice.SetPenColor (0,0,1,1 );
//
//					gfxDevice.WriteVtx ( x-50, y-50, 1 );
//					gfxDevice.WriteUV(1.0f,0.0f);			
//					gfxDevice.WriteFinalColor4b ();
//
//					gfxDevice.WriteVtx ( x+50, y-50, 1 );	
//					gfxDevice.WriteUV(1.0f,1.0f);				
//					gfxDevice.WriteFinalColor4b ();
//
//					gfxDevice.WriteVtx (x-50, y+50, 1 );
//					gfxDevice.WriteUV(1.0f,0.0f);		
//					gfxDevice.WriteFinalColor4b ();
//




	gfxDevice.EndPrim (); //END


	//gfxDevice.Flush();
	//gfxDevice.ResetState();

	//RESET PEN TO WHIE
	//gfxDevice.SetPenColor (0,0,0,1 );

	} //IF TEXTURE & SHADER

	return 0;

};



//----------------------------------------------------------------//
MOAIDraw::MOAIDraw () {
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIDraw::~MOAIDraw () {
}

//----------------------------------------------------------------//
void MOAIDraw::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED ( state );

	luaL_Reg regTable [] = {
		{ "drawAnimCurve",			_drawAnimCurve },
		//{ "drawAxisGrid",			_drawAxisGrid }, // TODO
		{ "drawBoxOutline",			_drawBoxOutline },
		{ "drawCircle",				_drawCircle },
		{ "drawEllipse",			_drawEllipse },
		//{ "drawGrid",				_drawGrid }, // TODO
		{ "drawLine",				_drawLine },
		{ "drawPoints",				_drawPoints },
		{ "drawRay",				_drawRay },
		{ "drawRect",				_drawRect },
		{ "fillCircle",				_fillCircle },
		{ "fillEllipse",			_fillEllipse },
		{ "fillFan",				_fillFan },
		{ "fillRect",				_fillRect },
		{ "drawText",				_drawText },
		{ "drawTexture",			_drawTexture },
		{ "drawTextureUV",			_drawTextureUV },
        ///
        { "drawRectList",		    _drawRectList },
        { "drawLineList",		    _drawLineList },
        { "drawRingList",		    _drawRingList },
        { "drawCircleList",		    _drawCircleList },
        { "rectStart" ,            _rectStart},
        { "rectEnd"  ,             _rectEnd},
        { "rectDraw" ,             _rectDraw},


        { "drawVertics" ,          _drawVertics},
		{ "drawLight",			   _drawLight },
		

        { "setShader",		    _setShader },

		{ "shadowStart",	    _shadowStart },
		{ "shadowEnd",			_shadowEnd },
		{ "shadowColor",		_shadowColor },
		{ "shadowVtx",			_shadowVtx },
		{ "shadowFan",			_shadowFan },

		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}
