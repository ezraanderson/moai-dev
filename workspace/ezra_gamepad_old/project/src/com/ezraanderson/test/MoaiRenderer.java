/*
 * Copyright (C) 2008 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.ezraanderson.test;
import android.content.Context;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.Color;
import android.util.Log;
import android.view.SurfaceView;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.opengles.GL10;

import com.ziplinegames.moai.Moai;
import com.ziplinegames.moai.MoaiLog;

public class MoaiRenderer implements GLView.Renderer{
	
	private int mHeight;
	private int mWidth;

	
	
    public MoaiRenderer(Context context) {
        mContext = context;    
    }

    public int[] getConfigSpec() {
    	
    	
        final int EGL_OPENGL_ES2_BIT = 4;
    	
        
   //*******************************************************************************************
   //THIS IS WRONG ON SOME DEVICES BUT RETURN RGB_525 WHICH IS FASTER AND GIVES YOU BETTERS FPS     
    	
        
		//  Log.v("EGL", "pixel-3()");  
		//  Log.v("EGL", "pixel-3()");  
		//  Log.v("EGL", "pixel-3()");  
		//  Log.v("EGL", "pixel-3()");  
		  
		 // int[] configSpec = {};
		  
			   //     int[] configSpec = {
			   //          EGL10.EGL_DEPTH_SIZE, 16,
			   //          EGL10.EGL_NONE
			   //   };  
		  
	        int[] configSpec ={        	
	        		EGL10.EGL_RED_SIZE, 5,
	        		EGL10.EGL_GREEN_SIZE, 6,
	        		EGL10.EGL_BLUE_SIZE, 5,
	        		EGL10.EGL_NONE
	        		};   	  
		  
		  
    	
			  	   	
    //LOOKS BETTER BUT SLOWER FPS	 
   // setEGLConfigChooser(8, 8, 8, 8, 0, 0);
        
        
        
	//	 int[] configSpec = {
	//		EGL10.EGL_STENCIL_SIZE, 1, /* Don't change this position in array! */
	//		EGL10.EGL_RED_SIZE, 8,
	//	EGL10.EGL_GREEN_SIZE, 8,
	//		EGL10.EGL_BLUE_SIZE, 8,
	//		EGL10.EGL_ALPHA_SIZE, 8,
	//		EGL10.EGL_DEPTH_SIZE,8,
	//		EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	//		EGL10.EGL_NONE,
			     
	//		    };
  
        
        return configSpec;
    }

    

    
    
    public void surfaceCreated(GL10 gl) {    	
    	//Log.v("EGL", "TRACE --> run lua()");   	
    		
    }

    
    

    
    public void drawFrame(GL10 gl) {   
    //COULD PUT "MOAIupdate & MOAIRender" HERE
  
    }

    
    
//----------------------------------------------------------------//
public void setScreenDimensions ( int width, int height ) {
			Resources resources = mContext.getResources();
			Configuration config = resources.getConfiguration();
			
			if (config.orientation == Configuration.ORIENTATION_PORTRAIT) {
			mWidth = Math.min(width, height);
			mHeight = Math.max(width, height);
			} else if (config.orientation == Configuration.ORIENTATION_LANDSCAPE) {
			mWidth = Math.max(width, height);
			mHeight = Math.min(width, height);
			} else {
			mWidth = width;
			mHeight = height;
}
}  
    
    
    
    
    
    public void sizeChanged(GL10 gl, int w, int h) { 
    	
     	Moai.detectGraphicsContext (); 
    	setScreenDimensions ( w, h );
    	Moai.setViewSize ( w, h );
    	
     	
			//Log.v("EGL", "trace-screen--> sizeChanged-moaisize: "+w+" "+h);          	
			//surfaceView = new GLView(this);
			//surfaceView.getHolder().setFixedSize(1280, 720);
			
			//mGLView.surfaceChanged(mGLView.getHolder(), 1, 200,200);
			
			//SurfaceView surfaceView = null;
			//surfaceView.getHolder().setFixedSize(100, 200);
				
			 //Moai.setScreenSize (960,540 );                
			 //Moai.setViewSize (960,540 );	
			      	  
        	
     
    }

    private Context mContext;


}



