//----------------------------------------------------------------//
// Copyright (c) 2010-2013 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.ziplinegames.moai;

import com.ezraanderson.*;
import com.ezraanderson.particlesoup_free.MoaiActivity;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.ComponentName;
import android.net.Uri;
import android.net.Uri.Builder;
import android.os.Bundle;
import android.util.Log;

//================================================================//
// MoaiBrowser
//================================================================//
public class MoaiBrowser {
  private static Activity sActivity = null;

    //----------------------------------------------------------------//
  public static void onCreate ( Activity activity ) {
    Log.v("EGL", "URL CREATED: "+activity); 
    sActivity = activity;
    
  };

    //----------------------------------------------------------------//
  public static boolean canOpenURL ( String url ) {
    //try {
      
      
      Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.ezraanderson.com"));
      MoaiActivity.mActivity.startActivity(browserIntent);
      
      
      //PackageManager packageManager = sActivity.getPackageManager();
      
      //Intent intent = new Intent ( Intent.ACTION_VIEW, Uri.parse ( url ) );
      //ComponentName componentName = intent.resolveActivity( packageManager );

      //if ( componentName == null ) {
      //  return false;
            //}

      //MoaiLog.i ( "getPackage() = " + componentName.getPackageName() + " class=" + componentName.getClassName() );
      //return true;
    //} catch ( Exception e) {
      //MoaiLog.e ( "Error checking package ", e);
      //return false;
    //}
    
    return true;
    //return false;
  }
  

  //----------------------------------------------------------------//
  public static void openURL ( final String url ) {
    Log.v("EGL", "URL: "+url);                
            Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
            MoaiActivity.mActivity.startActivity(browserIntent);
              
    
    
  }

    //----------------------------------------------------------------//
  public static void openURLWithParams ( String url, Bundle parameters ) {
        Uri.Builder builder = Uri.parse ( url ).buildUpon ( );
        for ( String key : parameters.keySet() ) {
            builder.appendQueryParameter( key, parameters.getString( key ) );
        }
        Uri uri = builder.build ( );
    sActivity.startActivity ( new Intent ( Intent.ACTION_VIEW, uri ) );
  }
}
