//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

//

//MANFEST
//android:largestWidthLimitDp="480"
//android:anyDensity    ="false"  force smallest size

package com.ezraanderson.geohopfree;

import tv.ouya.console.api.OuyaController;



import android.app.Activity;
import android.app.ActivityManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.pm.ConfigurationInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.ViewManager;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.chartboost.sdk.Chartboost;
import com.ezraanderson.geohopfree.R;



// Moai
import com.ziplinegames.moai.*;

import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import java.net.URI;
import android.content.Context;
import android.os.AsyncTask;
import android.net.Uri;
import android.provider.Settings.Secure;

//================================================================//
// MoaiActivity
//================================================================//
public class MoaiActivity extends Activity {

  private AccelerometerEventListener    mAccelerometerListener = null;
  private Sensor              mAccelerometerSensor = null;
  private Sensor              mMagnetometerSensor = null;
  private LocationEventListener      mLocationListener = null;
  private ConnectivityBroadcastReceiver   mConnectivityReceiver = null;
  //private MoaiView            mMoaiView = null;
  private SensorManager           mSensorManager = null;
  private LocationManager          mLocationManager = null;
  private boolean              mWaitingToResume = false;
  private boolean              mWindowFocusLost = false;
  private float []            mAccelerometerData = null;
    protected static int mGLMajor = 2; 
    protected static int mGLMinor = 0;
    public static GLView mGLView;  
    public static Activity         wtf = null;
    private static Chartboost cb;
  //----------------------------------------------------------------//
  static {
    
    MoaiLog.i ( "Loading libmoai.so" );
    
    System.loadLibrary ( "moai" );
  }

  //----------------------------------------------------------------//
    public void onActivityResult ( int requestCode, int resultCode, Intent data ) {
  
    super.onActivityResult ( requestCode, resultCode, data );
    Moai.onActivityResult ( requestCode, resultCode, data );
    }

  //----------------------------------------------------------------//
  protected void onCreate ( Bundle savedInstanceState ) {

    MoaiLog.i ( "MoaiActivity onCreate: activity CREATED" );


    
    //requestWindowFeature ( Window.FEATURE_NO_TITLE );
    
    
    super.onCreate ( savedInstanceState );
    
    Log.v("EGL", "trace-1 onCreate");  
    
    Moai.onCreate ( this );    
    Moai.createContext ();
    Moai.init ();    
    

    
    
    
    //**************************************************************
      //GL
    
      setContentView(R.layout.main);  
      mGLView = (GLView) findViewById(R.id.glview);  
            //mGLView.setPreserveEGLContextOnPause(true);    
      mGLView.setRenderer(new MoaiRenderer(this));
      mGLView.requestFocus();
     // mGLView.setZOrderOnTop(true);
   
   
    
    
    //**********************************************************************************
    try {
      
      ApplicationInfo myApp = getPackageManager ().getApplicationInfo ( getPackageName (), 0 );

      Moai.mount ( "bundle", myApp.sourceDir );
      Moai.setWorkingDirectory ( "bundle/assets/lua" );
    } catch ( NameNotFoundException e ) {

      MoaiLog.e ( "MoaiActivity onCreate: Unable to locate the application bundle" );
    }

    //**********************************************************************************
    if ( getFilesDir () != null ) {
     
       Moai.setDocumentDirectory ( getFilesDir ().getAbsolutePath ());
    } else {

      MoaiLog.e ( "MoaiActivity onCreate: Unable to set the document directory" );
    }
    
    //**********************************************************************************  
    if (  getCacheDir () != null ) {
     
       Moai.setCacheDirectory ( getCacheDir ().getAbsolutePath ());
    } else {

      MoaiLog.e ( "MoaiActivity onCreate: Unable to set the cache directory" );
    }
    
    //**********************************************************************************
    
    
    //Display display = (( WindowManager ) getSystemService ( Context.WINDOW_SERVICE )).getDefaultDisplay ();
    //ConfigurationInfo info = (( ActivityManager ) getSystemService ( Context.ACTIVITY_SERVICE )).getDeviceConfigurationInfo ();
     // mMoaiView = new MoaiView ( this, display.getWidth (), display.getHeight (), info.reqGlEsVersion );
      
      
      
      
      
      //******************************************************************************************
    mAccelerometerData     = new float[3];
    mSensorManager       = ( SensorManager ) getSystemService ( Context.SENSOR_SERVICE );
    mLocationManager    = ( LocationManager ) getSystemService ( Context.LOCATION_SERVICE );
    

   // ************************************* 
   // CRASHES 
      //startConnectivityReceiver ();
    
    
    
    
    //enableLocationEvents ( true );
    enableAccelerometerEvents ( true );
    
    
    
    
    //*****************************************************************************
    //LinearLayoutIMETrap con = MoaiKeyboard.getContainer ();
    //setContentView ( con );
    //con.addView ( mMoaiView );
    //con.addView ( MoaiKeyboard.getEditText ());
    
    
    
//*****************************************
//OUYA    
      //OuyaController.init(this);
    
    
    
    
    
    //************************************
    //ADS
    
    //cb = Chartboost.sharedChartboost();
    //String appId = "53f27760c26ee47f9ed1cbc8";
    //String appSignature = "65b15382dc89e9327b2c0df05daf261960a29111";
    //cb.onCreate(Moai.sActivity, appId, appSignature, null);
    //cb.onStart(this);
      //cb.cacheInterstitial();
        
        
        
      //cb.cacheInterstitial("b");
      //cb.cacheInterstitial("c");      
      //cb.showInterstitial("a");
      
    
    //wtf = this;
    
  }

  
  

  public void onConfigurationChanged(Configuration newConfig) {       
      super.onConfigurationChanged(newConfig);

      // -- stomp any attempts by the OS to resize my view.
      // -- Hardcoded values for illustration only. In real life
      // -- you'll need to save these when the surface view is originally created
      
      //HACK FOR HTC
      mGLView.getLayoutParams().width = Moai.mWidth;
      mGLView.getLayoutParams().height = Moai.mHeight;
  };
  
  
  
  
  //----------------------------------------------------------------//
  protected void onDestroy () {

    MoaiLog.i ( "MoaiActivity onDestroy: activity DESTROYED" );
    Log.v("EGL", "trace  onDestroy"); 
    
    super.onDestroy ();  
    

    
    
      //stopConnectivityReceiver (); 
  
  
    Moai.onDestroy ();    
         
    Moai.finish ();
    
  
    
    
  }
  
  //----------------------------------------------------------------//
  protected void onNewIntent ( Intent intent ) {
    
    MoaiLog.i ( "MoaiActivity onNewIntent: application started from NEW INTENT" );
    
    Uri data = intent.getData();
    if (data != null) {
      Moai.AppOpenedFromURL ( data.toString() );
    }
    setIntent ( intent );
  }

  //----------------------------------------------------------------//
  protected void onPause () {

    MoaiLog.i ( "MoaiActivity onPause: activity PAUSED" );
    Log.v("EGL", "trace  onPause"); 
    
    super.onPause ();
    
    
    
    
  //  glView.on
  //  mGLView.onPause();
    
    MoaiLog.i ( "MoaiActivity onPause: PAUSING now" );
    Moai.onPause ();
    Moai.pause (true);    
    
    if ( mAccelerometerListener != null ) {      
        mSensorManager.unregisterListener ( mAccelerometerListener );
    }
    
    if ( mLocationListener != null ) {
        mLocationManager.removeUpdates( mLocationListener );
    }
    
    
    
   // glView.removeView((View) v.getParent());
    
    
   // ((ViewManager)mGLView.getParent()).removeView(R.id.glview);
    //mGLView.removeAllViews();
    

    // If we've been paused, then we're assuming we've lost focus. 
    // This handles the case where the user presses the lock button
    // very quickly twice, in which case we do not receive the 
    // expected windows focus events.
    //mWindowFocusLost = true;


    //mMoaiView.pause ( true );  
    
    //Moai.setApplicationState ( Moai.ApplicationState.APPLICATION_PAUSED );    
    //Moai.endSession ();    
  }
  
  //----------------------------------------------------------------//
  protected void onResume () {

    MoaiLog.i ( "MoaiActivity onResume: activity RESUMED" );
    super.onResume (); 
  ///  mGLView.onPause();
   
    
    
    Moai.onResume ();
    Moai.pause (false);    
    if ( mAccelerometerListener != null ) {
      
      mSensorManager.registerListener ( mAccelerometerListener, mAccelerometerSensor, SensorManager.SENSOR_DELAY_NORMAL );
      mSensorManager.registerListener ( mAccelerometerListener, mMagnetometerSensor, SensorManager.SENSOR_DELAY_NORMAL );
    }

    if ( mLocationListener != null ) {

      mLocationManager.requestLocationUpdates ( LocationManager.NETWORK_PROVIDER, 0, 0, mLocationListener );
      mLocationManager.requestLocationUpdates ( LocationManager.GPS_PROVIDER, 0, 0, mLocationListener );
    }
  
    
    
    //********************************************************************
    //I DON'T LINK THIS
    //OUYA RESUME FOR PARTICLE SOUP    
        if (Moai.mGameLoad == true) {
            Moai.showDialogHelp(null, "Welcome To Particle Soup","Enter Simulator",null,null,true);
            
            
    
            
        }    
    
    
  
        
        
        
    // If we have not lost Window focus, then resume immediately; 
    // otherwise, wait to regain focus before we resume. All of 
    // this nonsense is to prevent audio from playing while the
    // screen is locked.
    //mWaitingToResume = mWindowFocusLost;
    //if ( !mWindowFocusLost ) {      
    //  MoaiLog.i ( "MoaiActivity onResume: RESUMING now" );
    //  mMoaiView.pause ( false );
    //}
    
    
    
  }

  

  //================================================================//
  // WindowEvent methods
  //================================================================//

  //----------------------------------------------------------------//
  public void onWindowFocusChanged ( boolean hasFocus ) {
    
    MoaiLog.i ( "MoaiActivity onWindowFocusChanged: activity FOCUS CHANGED" );
    
    super.onWindowFocusChanged ( hasFocus );
    
    // If we are waiting to resume and just got the window focus back, 
    // it's time to resume. All of this nonsense is to prevent audio 
    // from playing while the screen is locked.
 //   mWindowFocusLost = !hasFocus;
  
   // if ( mWaitingToResume && hasFocus ) {    
   //   mWaitingToResume = false;
   //   MoaiLog.i ( "MoaiActivity onWindowFocusChanged: RESUMING now" );
   // }
    if (hasFocus) {  
      mGLView.requestFocus();
    } else {
        //setContentView(R.layout.main);
    };
    
    
    
  }

  
  
  
  
  
  //----------------------------------------------------------------//
  protected void onStart () {
    
    MoaiLog.i ( "MoaiActivity onStart: activity STARTED" );
    super.onStart ();
    Moai.onStart ();
    
    
    
    //************************************
    //MIGHT HARD CODE THIS
    //cb.showInterstitial();
    
    
    
    
    
  }
  
  //----------------------------------------------------------------//
  protected void onStop () {

    MoaiLog.i ( "MoaiActivity onStop: activity STOPPED" );
    super.onStop ();
    Moai.onStop ();
  }
  
  
  //----------------------------------------------------------------//
  public static void killApp () {
    
    //Moai.onDestroy ();    
    //.stopConnectivityReceiver ();    
    //Moai.finish ();
    
    //MoaiActivity.onDestroy();
    //MoaiLog.i ( "MoaiActivity onStop: activity STOPPED" );
    //super.onStop ();
    //Moai.onStop ();
  }
  
  
  //================================================================//
  // Private methods
  //================================================================//

  //----------------------------------------------------------------//
  private void enableAccelerometerEvents ( boolean enabled ) {
    
    if ( !enabled ) {
      
      if ( mAccelerometerListener != null ) {

        mSensorManager.unregisterListener ( mAccelerometerListener );
        mAccelerometerListener = null;
      }

      if ( mAccelerometerSensor != null ) {
        
        mAccelerometerSensor = null;
      }
    } else if ( enabled ) {
      
      if ( mAccelerometerSensor == null ) {
        
        mAccelerometerSensor = mSensorManager.getDefaultSensor ( Sensor.TYPE_ACCELEROMETER );
        mMagnetometerSensor = mSensorManager.getDefaultSensor ( Sensor.TYPE_MAGNETIC_FIELD );
      }
      
      if ( mAccelerometerListener == null ) {

        mAccelerometerListener = new AccelerometerEventListener ();
        mSensorManager.registerListener ( mAccelerometerListener, mAccelerometerSensor, SensorManager.SENSOR_DELAY_NORMAL );
        mSensorManager.registerListener ( mAccelerometerListener, mMagnetometerSensor, SensorManager.SENSOR_DELAY_NORMAL );
      }
    }
  }

  //----------------------------------------------------------------//
  private void enableLocationEvents ( boolean enabled ) {
    
    if ( !enabled ) {
      
      if ( mLocationListener != null ) {

        mLocationManager.removeUpdates( mLocationListener );
        mLocationListener = null;
      }
    } else if ( enabled ) {
      
      if ( mLocationListener == null ) {

        mLocationListener = new LocationEventListener ();
        mLocationManager.requestLocationUpdates ( LocationManager.NETWORK_PROVIDER, 0, 0, mLocationListener );
        mLocationManager.requestLocationUpdates ( LocationManager.GPS_PROVIDER, 0, 0, mLocationListener );

      }
    }
  }
    
  //----------------------------------------------------------------//
  private void startConnectivityReceiver () {
    
    if ( mConnectivityReceiver == null ) {
      
      // mConnectivityReceiver = new ConnectivityBroadcastReceiver ();
      // IntentFilter filter = new IntentFilter ();
      // filter.addAction ( ConnectivityManager.CONNECTIVITY_ACTION );
      // this.registerReceiver ( mConnectivityReceiver, filter );
    }
    
  }
  
  //----------------------------------------------------------------//
  private void stopConnectivityReceiver () {
    
      //this.unregisterReceiver ( mConnectivityReceiver );
      //mConnectivityReceiver = null;
    
  }
  
  
  
  //================================================================//
  // KeyEvent methods
  //================================================================//
  
  //----------------------------------------------------------------//
  /*
  public boolean onKeyDown ( int keyCode, KeyEvent event ) {

    MoaiLog.i ("MoaiActivity onKeyDown, keycode " + keyCode + " event: " + event );
    if ( keyCode == KeyEvent.KEYCODE_BACK ) {
          
      if ( Moai.backButtonPressed ()) {
        
        return true;
      }
    }
    return super.onKeyDown ( keyCode, event );
  }
  */
  
  //================================================================//
  // ConnectivityBroadcastReceiver
  //================================================================//

  private class ConnectivityBroadcastReceiver extends BroadcastReceiver {

    //----------------------------------------------------------------//
    @Override
    public void onReceive ( Context context, Intent intent ) {
      
      ConnectivityManager manager = ( ConnectivityManager )context.getSystemService ( Context.CONNECTIVITY_SERVICE );
      NetworkInfo networkInfo = manager.getActiveNetworkInfo ();
      Moai.ConnectionType connectionType = Moai.ConnectionType.CONNECTION_NONE;
      
      if ( networkInfo != null ) {
        
         switch ( networkInfo.getType () ) {
         
          case ConnectivityManager.TYPE_MOBILE: {
            connectionType = Moai.ConnectionType.CONNECTION_WWAN;
            break;
          }
          case ConnectivityManager.TYPE_WIFI: {
            connectionType = Moai.ConnectionType.CONNECTION_WIFI;
            break;
          }
         }
      }
      
      MoaiLog.i ( "ConnectivityBroadcastReceiver onReceive: Connection = " + connectionType );
      
      Moai.setConnectionType (( long )connectionType.ordinal ());
    }
  };
  
  //================================================================//
  // AccelerometerEventListener
  //================================================================//

  private class AccelerometerEventListener implements SensorEventListener {
    
    private float [] mGravity;
    private float [] mGeomagnetic;
    private float mRotationMatrixA [] = new float [ 9 ];
    private float mRotationMatrixB [] = new float [ 9 ];
    private float orientation [] = new float [ 3 ];

    //----------------------------------------------------------------//
    public void onAccuracyChanged ( Sensor sensor, int accuracy ) {
      
    }

    // Thanks to NVIDIA for this useful canonical-to-screen orientation function.
    public void canonicalOrientationToScreenOrientation ( int displayRotation, float[] canVec, float[] screenVec ) { 
        
       final int axisSwap[][] = {
         { 1,-1, 1, 0 },   // ROTATION_0
         { 1, 1, 0, 1 },   // ROTATION_90
         {-1,-1, 1, 0 },   // ROTATION_180
         { 1,-1, 0, 1 } }; // ROTATION_270

       final int[] as = axisSwap[displayRotation];
       screenVec[0] = (float)as[0] * canVec[ as[2] ];
       screenVec[1] = (float)as[1] * canVec[ as[3] ];
       screenVec[2] = canVec[2];
    }
    
    //----------------------------------------------------------------//
    public void onSensorChanged ( SensorEvent event ) {

      if ( event.sensor.getType () == Sensor.TYPE_ACCELEROMETER ) {

        Display display = (( WindowManager ) getSystemService ( Context.WINDOW_SERVICE )).getDefaultDisplay ();
        canonicalOrientationToScreenOrientation ( display.getRotation (), event.values, mAccelerometerData );
                
        float x = mAccelerometerData [ 0 ];
        float y = mAccelerometerData [ 1 ];
        float z = mAccelerometerData [ 2 ];
                
        mGravity = mAccelerometerData;

        int deviceId = Moai.InputDevice.INPUT_DEVICE.ordinal ();
        int sensorId = Moai.InputSensor.SENSOR_LEVEL.ordinal ();
                
        // normalize the vector
        double mag = Math.sqrt ( x * x + y * y + z * z );
        x = x / ( float ) mag;
        y = y / ( float ) mag;
        z = z / ( float ) mag;

        Moai.enqueueLevelEvent ( deviceId, sensorId, x, y, z );
      }
      else if ( event.sensor.getType () == Sensor.TYPE_MAGNETIC_FIELD )
        mGeomagnetic = event.values;

      if ( mGravity != null && mGeomagnetic != null && SensorManager.getRotationMatrix( mRotationMatrixA, null, mGravity, mGeomagnetic ) ) {

        int deviceId = Moai.InputDevice.INPUT_DEVICE.ordinal ();
        int sensorId = Moai.InputSensor.SENSOR_COMPASS.ordinal ();

        SensorManager.remapCoordinateSystem (
          mRotationMatrixA,
          SensorManager.AXIS_X,
          SensorManager.AXIS_Z,
          mRotationMatrixB );

        SensorManager.getOrientation ( mRotationMatrixB, orientation );
        float heading = orientation [0] * 57.2957795f; 
        if ( heading < 0 ) heading += 360;

        Moai.enqueueCompassEvent ( deviceId, sensorId, heading );
      }
    }
  };

  //================================================================//
  // LocationEventListener
  //================================================================//

  private class LocationEventListener implements LocationListener {
    
    //----------------------------------------------------------------//
    public void onLocationChanged ( Location location ) {

      double longitude = location.getLongitude ();
      double latitude = location.getLatitude ();
      double altitude = location.getAltitude ();
      float hAccuracy = location.getAccuracy ();
      float vAccuracy = location.getAccuracy ();
      float speed = location.getSpeed ();

      int deviceId = Moai.InputDevice.INPUT_DEVICE.ordinal ();
      int sensorId = Moai.InputSensor.SENSOR_LOCATION.ordinal ();

      Moai.enqueueLocationEvent ( deviceId, sensorId, longitude, latitude, altitude, hAccuracy, vAccuracy, speed );
    }

    //----------------------------------------------------------------//
    public void onStatusChanged ( String provider, int status, Bundle extras ) {}

    //----------------------------------------------------------------//
    public void onProviderEnabled ( String provider ) {}

    //----------------------------------------------------------------//
    public void onProviderDisabled ( String provider ) {}
  };
  
  
  
  //**************************************************************************************************
  //**************************************************************************************************
  //**************************************************************************************************
  //**************************************************************************************************  
  
  
  //----------------------------------------------------------------//
  @Override
  public boolean onTouchEvent ( MotionEvent event ) {

  boolean isDown = true;
          
  

  
  
  switch( event.getActionMasked() )
  {
  case MotionEvent.ACTION_CANCEL:
  /*Moai.enqueueTouchEventCancel(
  Moai.InputDevice.INPUT_DEVICE.ordinal (),
  Moai.InputSensor.SENSOR_TOUCH.ordinal ()
  );*/
  break;
  case MotionEvent.ACTION_UP:
  case MotionEvent.ACTION_POINTER_UP:
  isDown = false;
  case MotionEvent.ACTION_DOWN:
  case MotionEvent.ACTION_POINTER_DOWN:
  {
  final int pointerIndex = event.getActionIndex();
  int pointerId = event.getPointerId ( pointerIndex );
  Moai.enqueueTouchEvent (
  Moai.InputDevice.INPUT_DEVICE.ordinal (),
  Moai.InputSensor.SENSOR_TOUCH.ordinal (),
  pointerId,
  isDown,
  Math.round ( event.getX ( pointerIndex )),
  Math.round ( event.getY ( pointerIndex )),
  1
  );
  break;
  }
  case MotionEvent.ACTION_MOVE:
  default:
  {
  final int pointerCount = event.getPointerCount ();
  for ( int pointerIndex = 0; pointerIndex < pointerCount; ++pointerIndex ) {

  int pointerId = event.getPointerId ( pointerIndex );
  Moai.enqueueTouchEvent (
  Moai.InputDevice.INPUT_DEVICE.ordinal (),
  Moai.InputSensor.SENSOR_TOUCH.ordinal (),
  pointerId,
  isDown,
  Math.round ( event.getX ( pointerIndex )),
  Math.round ( event.getY ( pointerIndex )),
  1
  );
  }
  break;
  }
  }

  return true;
  }

  
  //**************************************************************************************************
  //**************************************************************************************************
  //**************************************************************************************************
  //**************************************************************************************************  
  
  
  
  
  // ================================================================//
  // OuyaGamePad Button Down
  // ================================================================//

  
  @Override
  public boolean onKeyDown(int keyCode, KeyEvent event) {

  //boolean handled = OuyaController.onKeyDown(keyCode, event);
  //int idPlayer     = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
  //Moai.enqueueGameButtonEvent(0,Moai.InputSensor.SENSOR_GAMEBUTTON.ordinal(), idPlayer, true,keyCode);  
	  
	  
    if (keyCode == KeyEvent.KEYCODE_BACK) {
    	Log.v("EGL", " trace - back button PHONE"); 
      	Moai.showDialogExit(null, "Do you want to close this application?","No",null,"Yes",true);     
    }

    // OUYA QUICK EXIT
    if (keyCode == 82) {
    	Log.v("EGL", "BACKBUTTON - OUYA"); 
    }

   

    return  super.onKeyDown(keyCode, event);
  }
  
  

  // ================================================================//
  // OuyaGamePad Button Up
  // ================================================================//

  @Override
  public boolean onKeyUp(int keyCode, KeyEvent event) {

    //boolean handled = OuyaController.onKeyUp(keyCode, event);
    
    //int idPlayer = OuyaController.getPlayerNumByDeviceId(event .getDeviceId());
    //Moai.enqueueGameButtonEvent(0,Moai.InputSensor.SENSOR_GAMEBUTTON.ordinal(), idPlayer, false,keyCode);
    
    
    return  super.onKeyUp(keyCode, event);
    

  }

  // ================================================================//
  // OuyaGamePad
  // ================================================================//

  @Override
  public boolean onGenericMotionEvent(MotionEvent event) {

    // if (isOUYA == true) {}//IS OUYA

    
  /*  
    boolean handled = OuyaController.onGenericMotionEvent(event);
    int   player   = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());

    if ((event.getSource() & InputDevice.SOURCE_CLASS_POINTER) != 0) {

  
    } else {
      float leftAxisX = event.getAxisValue(OuyaController.AXIS_LS_X);
      float leftAxisY = event.getAxisValue(OuyaController.AXIS_LS_Y);
      float rightAxisX = event.getAxisValue(OuyaController.AXIS_RS_X);
      float rightAxisY = event.getAxisValue(OuyaController.AXIS_RS_Y);
      float l2Axis = event.getAxisValue(OuyaController.AXIS_L2);
      float r2Axis = event.getAxisValue(OuyaController.AXIS_R2);

      boolean callNotification = false;
      float c_minStickDistance = OuyaController.STICK_DEADZONE * OuyaController.STICK_DEADZONE;

      if (leftAxisX * leftAxisX + leftAxisY * leftAxisY < c_minStickDistance) {
        leftAxisX = leftAxisY = 0.0f;
      } else {

        callNotification = true;
      }

      if (rightAxisX * rightAxisX + rightAxisY * rightAxisY < c_minStickDistance) {
        rightAxisX = rightAxisY = 0.0f;
        callNotification = true;
      } else {
        callNotification = true;
      }

      if (l2Axis > 0.0f || r2Axis > 0.0f) {
        callNotification = true;
      }

      if (callNotification) {
        Moai.enqueueGameAnalogEvent(0,
            Moai.InputSensor.SENSOR_GAMEANALOG.ordinal(), player, leftAxisX, leftAxisY, rightAxisX, rightAxisY);

      }
    }
    */
    

    return  super.onGenericMotionEvent(event);


  }
  
  
  
  
}
