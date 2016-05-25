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

package com.ezraanderson.geohopfree;
import android.content.Context;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.Color;
import android.util.Log;
import android.view.SurfaceView;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.opengles.GL10;

import com.chartboost.sdk.Chartboost;
import com.ziplinegames.moai.Moai;
import com.ziplinegames.moai.MoaiLog;

public class MoaiRenderer implements GLView.Renderer{
  
  private int mHeight;
  private int mWidth;
  private boolean isUpdater = false;
  
  
    public MoaiRenderer(Context context) {
        mContext = context;    
    }

    public int[] getConfigSpec() {
      
      
        final int EGL_OPENGL_ES2_BIT = 4;
      
        
   //*******************************************************************************************
   //THIS IS WRONG ON SOME DEVICES BUT RETURN RGB_525 WHICH IS FASTER AND GIVES YOU BETTERS FPS     
      
     // int[] configSpec = {};     
        
        
        //CORRECT HIGH RES
        /*
              int[] configSpec = {
                   EGL10.EGL_DEPTH_SIZE, 16,
                   EGL10.EGL_NONE
            };
            */  
              
              
              
     /* 
        int[] configSpec ={          
             EGL10.EGL_RED_SIZE, 5,
             EGL10.EGL_GREEN_SIZE, 6,
             EGL10.EGL_BLUE_SIZE, 5,
             EGL10.EGL_NONE
             };       
      
      */
      
               
    //LOOKS BETTER BUT SLOWER FPS   
   // setEGLConfigChooser(8, 8, 8, 8, 0, 0);
        
        
      
    int[] configSpec = {
     //EGL10.EGL_STENCIL_SIZE, 1, 
     
      EGL10.EGL_RED_SIZE, 8,
      EGL10.EGL_GREEN_SIZE, 8,
      EGL10.EGL_BLUE_SIZE, 8,
      EGL10.EGL_ALPHA_SIZE, 8,
      
      EGL10.EGL_DEPTH_SIZE,16,    
      EGL10.EGL_NONE,
           
          };
  
       
     

     
     
     
        return configSpec;
    }

    

    
    
    public void surfaceCreated(GL10 gl) {         
    
    //************************
    //START-GAME
   if (isUpdater == false ) {     
   
       //Moai.runScripts ( new String [] { "../init.lua", "main.luac" } );
    Moai.runScripts ( new String [] { "../init.lua", "main.lua" } );
   }      
      
      
   //*******************************************   
   //START UPUDATER   
      if (isUpdater == true ) {
          Moai.runScripts ( new String [] { "../init.lua", "updater/main.lua" } );
      };
    
   
    
    
     // Moai.runScripts ( new String [] { "../init.lua", "main.luac" } );
    
    
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
      
      
      Log.v("EGL", "***** trace-screen--> sizeChanged-moaisize: "+w+" "+h); 
      
        Moai.detectGraphicsContext ();
        
      // DOESN"T WORK IS SUPPOSE TO HELP HTC  
      //gl.glViewport(0, 0, mWidth, mHeight);          
     
    }
    
    

    
    

    private Context mContext;
  

}



