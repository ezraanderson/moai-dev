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

package com.ezraanderson.geobyte;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.ArrayList;
import java.util.concurrent.Semaphore;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGL11;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL;
import javax.microedition.khronos.opengles.GL10;

import com.ziplinegames.moai.Moai;

/**
 * An implementation of SurfaceView that uses the dedicated surface for
 * displaying an OpenGL animation. This allows the animation to run in a
 * separate thread, without requiring that it be driven by the update mechanism
 *'90 of the view hierarchy.
 * 
 * The application-specific rendering code is delegated to a GLView.Renderer
 * instance.
 */
class GLView extends SurfaceView implements SurfaceHolder.Callback {
  GLView(Context context) {
    super(context);
    init();
  }

  // public void setPreserveEGLContextOnPause(boolean preserveOnPause) {
  // Log.v("EGL", "trace-0: mPre mPreserveEGLContextOnPause");
  // mPreserveEGLContextOnPause = preserveOnPause;
  // }

  public GLView(Context context, AttributeSet attrs) {
    super(context, attrs);
    init();
  }

  private void init() {
    // Install a SurfaceHolder.Callback so we get notified when the
    // underlying surface is created and destroyed
    mHolder = getHolder();
    mHolder.addCallback(this);

    // mHolder.setType(SurfaceHolder.SURFACE_TYPE_GPU);
  }

  public void setGLWrapper(GLWrapper glWrapper) {
    mGLWrapper = glWrapper;
  }

  public void setRenderer(Renderer renderer) {
    mGLThread = new GLThread(renderer);
    mGLThread.start();

  }

  public void surfaceCreated(SurfaceHolder holder) {
    mGLThread.surfaceCreated();

  }

  public void surfaceDestroyed(SurfaceHolder holder) {
    // Surface will be destroyed when we return
    mGLThread.surfaceDestroyed();
  }

  // WHY IS THIS NOT PUBLIC
  public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    // Surface size or format has changed. This should not happen in this
    // example.

    int width = w;
    int height = h;  
    
    
//******************************************************************************    
//TRYING TO FIGURE OUT HOW TO CHANGE WINDOWS SIZE AFTER THE GAMES IS STARTED    
//MY OUYA RETURNS RESULTION AT   960x540
//1920x1080 is really slow
//1280x720 is the best
    
    
// synchronized(this) {
// mHolder.lockCanvas();
// mHolder.setFixedSize(w,h );
// setViewportWidth(w);
// setViewportHeight(h);  


//width = 1280;
//height = 720;  

//width = 960;
//height = 540;

//width = 800;
//height = 480;    

///640x480 

//width = 1920;
//height = 1080;

//width = w;
//height = h;
    

    //FULL SCREEN NO MATER WHAT
    

    Log.d("EGL", "trace-screen-->surfaceChanged: " + width + " " + height+ " " + format);

    Moai.mHeight = height;
    Moai.mWidth  = width;
    
    Moai.setScreenSize(width, height);
    Moai.setViewSize(width, height);

    mHolder.setFixedSize(width, height); // CALLS SURFACE CHANGE
    mGLThread.onWindowResize(width, height);
    
    

    // Log.d("EGL", "trace-screen-->crash-->2: " + w+" "+h+" "+format);
    // mHolder.
    // }
    // mHolder.setFixedSize(600, );

    // mHolder.se

    // mGLThread.onWindowResize(960, 540);
    // mHolder.setFixedSize(960, 540 );

    // mGLThread.onWindowResize(1280, 720);
    // mHolder.setFixedSize(1280, 720 );

    // mGLThread.onWindowResize(1920, 1080);
    // mHolder.setFixedSize(1920, 1080 );

    // mGLThread.onWindowResize(960, 540);
    // mHolder.setFixedSize(960, 540 );
    
    
    
    //******************************************************************
    
    
        //THIS IS IN THE WRONG PLACE
       

    
  }
  
  
  

  
  
  
  
  

  /**
   * Inform the view that the activity is paused.
   */
  public void onPause() {
    mGLThread.onPause();
  }

  
  
  
  
  
  public void onScreen() {

    //TRYING TO FROUCE RES CHANGES
    // surfaceChanged(getHolder(), 1, 200,200);
    // synchronized(this) {}
    //Log.v("IAP", "trace-screen-->CRASH");
    // mHolder.setFixedSize(1280,720 ); //CALLS SURFACE CHANGE
    //surfaceChanged(getHolder(), 4, 200, 200);

    // mHasSurface = false;
    // mHolder.
    // mGLThread.onWindowResize(1920, 1080);
    // mGLThread.onPause();
    // mGLThread.onWindowResize(100,100);
    // Moai.setScreenSize (100,100 );
    // Moai.setViewSize (100,100);

    // GLView.surfaceChanged

    // mHolder.setFixedSize(1920,1080 );
    // mGLThread.mPaused = false;

  }

  /**
   * Inform the view that the activity is resumed.
   */
  public void onResume() {
    mGLThread.onResume();
  }

  /**
   * Inform the view that the window focus has changed.
   */
  @Override
  public void onWindowFocusChanged(boolean hasFocus) {
    super.onWindowFocusChanged(hasFocus);
    mGLThread.onWindowFocusChanged(hasFocus);
  }

  /**
   * Queue an "event" to be run on the GL rendering thread.
   * 
   * @param r
   *            the runnable to be run on the GL rendering thread.
   */
  public void queueEvent(Runnable r) {
    mGLThread.queueEvent(r);
  }

  @Override
  protected void onDetachedFromWindow() {
    super.onDetachedFromWindow();
    mGLThread.requestExitAndWait();
  }

  // ----------------------------------------------------------------------

  public interface GLWrapper {
    GL wrap(GL gl);
  }

  // ----------------------------------------------------------------------

  /**
   * A generic renderer interface.
   */
  public interface Renderer {
    /**
     * @return the EGL configuration specification desired by the renderer.
     */
    int[] getConfigSpec();

    /**
     * Surface created. Called when the surface is created. Called when the
     * application starts, and whenever the GPU is reinitialized. This will
     * typically happen when the device awakes after going to sleep. Set
     * your textures here.
     */
    void surfaceCreated(GL10 gl);

    /**
     * Surface changed size. Called after the surface is created and
     * whenever the OpenGL ES surface size changes. Set your viewport here.
     * 
     * @param gl
     * @param width
     * @param height
     */
    void sizeChanged(GL10 gl, int width, int height);

    /**
     * Draw the current frame.
     * 
     * @param gl
     */
    void drawFrame(GL10 gl);
  }

  /**
   * An EGL helper class.
   */

  private class EglHelper {
    public EglHelper() {

    }

    /**
     * Initialize EGL for a given configuration spec.
     * 
     * @param configSpec
     */
    public void start(int[] configSpec) {
      /*
       * Get an EGL instance
       */
      mEgl = (EGL10) EGLContext.getEGL();

      /*
       * Get to the default display.
       */
      mEglDisplay = mEgl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);

      /*
       * We can now initialize EGL for that display
       */
      int[] version = new int[2];
      mEgl.eglInitialize(mEglDisplay, version);

      EGLConfig[] configs = new EGLConfig[1];
      int[] num_config = new int[1];
      mEgl.eglChooseConfig(mEglDisplay, configSpec, configs, 1,
          num_config);
      mEglConfig = configs[0];

      /*
       * Create an OpenGL ES context. This must be done only once, an
       * OpenGL context is a somewhat heavy object.
       */

      int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

      int contextAttrs[] = new int[] { EGL_CONTEXT_CLIENT_VERSION,
          MoaiActivity.mGLMajor, EGL10.EGL_NONE };

      mEglContext = mEgl.eglCreateContext(mEglDisplay, mEglConfig,
          EGL10.EGL_NO_CONTEXT, contextAttrs);

      mEglSurface = null;
    }

    /*
     * Create and return an OpenGL surface
     */
    public GL createSurface(SurfaceHolder holder) {
      /*
       * The window size has changed, so we need to create a new surface.
       */
      if (mEglSurface != null) {

        /*
         * Unbind and destroy the old EGL surface, if there is one.
         */
        mEgl.eglMakeCurrent(mEglDisplay, EGL10.EGL_NO_SURFACE,
            EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        mEgl.eglDestroySurface(mEglDisplay, mEglSurface);
      }

      /*
       * Create an EGL surface we can render into.
       */
      mEglSurface = mEgl.eglCreateWindowSurface(mEglDisplay, mEglConfig,
          holder, null);

      /*
       * Before we can issue GL commands, we need to make sure the context
       * is current and bound to a surface.
       */
      mEgl.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface,
          mEglContext);

      GL gl = mEglContext.getGL();
      if (mGLWrapper != null) {
        gl = mGLWrapper.wrap(gl);
      }
      return gl;
    }

    /**
     * Display the current render surface.
     * 
     * @return false if the context has been lost.
     */
    public boolean swap() {

      // Moai.update();
      // EGL10 egl = (EGL10)EGLContext.getEGL();
      // mEgl.eglWaitNative(EGL10.EGL_CORE_NATIVE_ENGINE, null);
      // Moai.update ();

      
     // mEgl.eglWaitGL();
  
  //************************************    
  //COULD ADD RENDER HERE ALSO    
      Moai.update();    
    
      
      mEgl.eglSwapBuffers(mEglDisplay, mEglSurface);

      /*
       * Always check for EGL_CONTEXT_LOST, which means the context and
       * all associated data were lost (For instance because the device
       * went to sleep). We need to sleep until we get a new surface.
       */
      return mEgl.eglGetError() != EGL11.EGL_CONTEXT_LOST;
    }

    public void finish() {
      if (mEglSurface != null) {
        mEgl.eglMakeCurrent(mEglDisplay, EGL10.EGL_NO_SURFACE,
            EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        mEgl.eglDestroySurface(mEglDisplay, mEglSurface);
        mEglSurface = null;
      }
      if (mEglContext != null) {
        mEgl.eglDestroyContext(mEglDisplay, mEglContext);
        mEglContext = null;
      }
      if (mEglDisplay != null) {
        mEgl.eglTerminate(mEglDisplay);
        mEglDisplay = null;
      }
    }

    EGL10 mEgl;
    EGLDisplay mEglDisplay;
    EGLSurface mEglSurface;
    EGLConfig mEglConfig;
    EGLContext mEglContext;
  }

  /**
   * A generic GL Thread. Takes care of initializing EGL and GL. Delegates to
   * a Renderer instance to do the actual drawing.
   * 
   */

  class GLThread extends Thread {
    GLThread(Renderer renderer) {
      super();
      mDone = false;
      mWidth = 0;
      mHeight = 0;
      mRenderer = renderer;
      setName("GLThread");
    }

    @Override
    public void run() {
      /*
       * When the android framework launches a second instance of an
       * activity, the new instance's onCreate() method may be called
       * before the first instance returns from onDestroy().
       * 
       * This semaphore ensures that only one instance at a time accesses
       * EGL.
       */
      try {
        try {
          sEglSemaphore.acquire();
        } catch (InterruptedException e) {
          return;
        }
        guardedRun();
      } catch (InterruptedException e) {
        // fall thru and exit normally
      } finally {
        sEglSemaphore.release();
      }
    }

    private void guardedRun() throws InterruptedException {
      mEglHelper = new EglHelper();
      /*
       * Specify a configuration for our opengl session and grab the first
       * configuration that matches is
       */
      int[] configSpec = mRenderer.getConfigSpec();
      mEglHelper.start(configSpec);

      GL10 gl = null;
      boolean tellRendererSurfaceCreated = true;
      boolean tellRendererSurfaceChanged = true;

      /*
       * This is our main activity thread's loop, we go until asked to
       * quit.
       */
      while (!mDone) {

        /*
         * Update the asynchronous state (window size)
         */

        int w, h;
        boolean changed;
        boolean needStart = false;
        synchronized (this) {

          Runnable r;
          while ((r = getEvent()) != null) {
            r.run();
          }

          if (mPaused) {
            mEglHelper.finish();
            needStart = true;
          }

          if (needToWait()) {
            while (needToWait()) {
              wait();
            }
          }

          if (mDone) {
            break;
          }

          changed = mSizeChanged;
          w = mWidth;
          h = mHeight;
          mSizeChanged = false;
        }

        if (needStart) {
          mEglHelper.start(configSpec);
          tellRendererSurfaceCreated = true;
          changed = true;
        }

        if (changed) {

          gl = (GL10) mEglHelper.createSurface(mHolder);
          tellRendererSurfaceChanged = true;
        }

        if (tellRendererSurfaceCreated) {

          mRenderer.surfaceCreated(gl);
          tellRendererSurfaceCreated = false;
        }

        if (tellRendererSurfaceChanged) {

          Log.v("EGL", "trace-screen-->loop");

          mRenderer.sizeChanged(gl, w, h);

          tellRendererSurfaceChanged = false;
        }

        // RENDER
        if ((w > 0) && (h > 0)) {
          /* draw a frame here */

          mRenderer.drawFrame(gl);

          /*
           * Once we're done with GL, we need to call swapBuffers() to
           * instruct the system to display the rendered frame
           */
          mEglHelper.swap();
        }
      }

      /*
       * clean-up everything...
       */
      mEglHelper.finish();
    }

    private boolean needToWait() {
      return (mPaused || (!mHasFocus) || (!mHasSurface) || mContextLost)
          && (!mDone);
    }

    public void surfaceCreated() {
      synchronized (this) {
        mHasSurface = true;
        mContextLost = false;
        notify();
      
        
      }
    }

    public void surfaceDestroyed() {
      synchronized (this) {
        mHasSurface = false;
        notify();
      }
    }

    public void onPause() {
      synchronized (this) {
        mPaused = true;
      }
    }

    public void onResume() {
      synchronized (this) {
        mPaused = false;
        notify();
      }
    }

    public void onWindowFocusChanged(boolean hasFocus) {
      synchronized (this) {
        mHasFocus = hasFocus;
        if (mHasFocus == true) {
          notify();
        }
      }
    }

    public void onWindowResize(int w, int h) {
      synchronized (this) {

        // Log.v("EGL", "trace-screen-->onWindowResize");
        // mHolder.setFixedSize(w,h );
        // Log.v("EGL", "trace-screen-->no crash");

        mWidth = w;
        mHeight = h;
        mSizeChanged = true;
      }
    }

    public void requestExitAndWait() {
      // don't call this from GLThread thread or it is a guaranteed
      // deadlock!
      synchronized (this) {
        mDone = true;
        notify();
      }
      try {
        join();
      } catch (InterruptedException ex) {
        Thread.currentThread().interrupt();
      }
    }

    /**
     * Queue an "event" to be run on the GL rendering thread.
     * 
     * @param r
     *            the runnable to be run on the GL rendering thread.
     */
    public void queueEvent(Runnable r) {
      synchronized (this) {
        mEventQueue.add(r);
      }
    }

    private Runnable getEvent() {
      synchronized (this) {
        if (mEventQueue.size() > 0) {
          return mEventQueue.remove(0);
        }

      }
      return null;
    }

    private boolean mDone;
    private boolean mPaused;
    private boolean mHasFocus;

    private boolean mContextLost;
    private int mWidth;
    private int mHeight;
    private int mWait;

    private Renderer mRenderer;

    private ArrayList<Runnable> mEventQueue = new ArrayList<Runnable>();
    private EglHelper mEglHelper;
  }

  private static final Semaphore sEglSemaphore = new Semaphore(1);
  private boolean mSizeChanged = true;
  private boolean mHasSurface;
  public SurfaceHolder mHolder;
  private GLThread mGLThread;
  private GLWrapper mGLWrapper;
  // private boolean mPreserveEGLContextOnPause;

  // TODO Auto-generated method stub
  
  

}
