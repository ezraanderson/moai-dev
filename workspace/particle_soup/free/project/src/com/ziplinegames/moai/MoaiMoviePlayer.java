//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

package com.ziplinegames.moai;
import com.ezraanderson.particlesoup_free.MoaiActivity;
import com.ezraanderson.particlesoup_free.R;

import android.app.Activity;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.ViewGroup.LayoutParams;
import android.widget.RelativeLayout;
import android.widget.VideoView;

import java.io.IOException;

// TODO:
// Allow orientation control.
// MoaiView overlay.
// Allow on-screen controls to be specified.
// Support playing video over WIFI only.
// Support multiple videos to be played in order.
// On backgrounding... Lock screen...

//================================================================//
// MoaiMoviePlayer
//================================================================//
public class MoaiMoviePlayer extends Activity implements OnCompletionListener, OnPreparedListener {

  private static Activity     sActivity = null;
  private static MoaiMoviePlayer  sMovie = null;

  protected static native void AKUNotifyMoviePlayerReady    ();
  protected static native void AKUNotifyMoviePlayerCompleted  ();

  private VideoView  mVideoView = null;

  //----------------------------------------------------------------//
  public static void onCreate ( Activity activity ) {
    
    MoaiLog.i ( "MoaiMoviePlayer onCreate: Initializing Movie Player" );
    
    sActivity = activity;
  }
  
  //================================================================//
  // MoviePlayer JNI callback methods
  //================================================================//
  
  //----------------------------------------------------------------//
  public static void init ( String url ) {
    
    if ( sMovie != null ) {
      
      sMovie.finish ();
    }
  
    Intent movie = new Intent ( MoaiActivity.mActivity.getApplication (), MoaiMoviePlayer.class );
    movie.putExtra ( "url", url );
    MoaiActivity.mActivity.startActivity ( movie );
  }

  //----------------------------------------------------------------//
  public static void play () {
    
    if ( sMovie != null ) {
      
      sMovie.startPlayback ();
    }
  }
  
  //----------------------------------------------------------------//
  public static void pause () {
    
    if ( sMovie != null ) {
      
      sMovie.pausePlayback ();
    }
  }

  //----------------------------------------------------------------//
  public static void stop () {
    
    if ( sMovie != null ) {
      
      sMovie.stopPlayback ();
    }
  }
  
  //================================================================//
  // MoaiMoviePlayer instance methods
  //================================================================//
  
  //----------------------------------------------------------------//
  public void onCreate ( Bundle savedInstanceState ) {

    MoaiLog.i ( "MoaiMoviePlayer onCreate: activity CREATED" );
    
    super.onCreate ( savedInstanceState );

    
    
        sMovie = this;    
        RelativeLayout layout = new RelativeLayout ( this );
        layout.setGravity ( Gravity.CENTER );    
        mVideoView = new VideoView ( this );
        mVideoView.setOnPreparedListener ( this );
            mVideoView.setOnCompletionListener ( this );
            
        
        

        layout.addView ( mVideoView, new RelativeLayout.LayoutParams ( LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT ));
        setContentView ( layout );    
    
        //String url = this.getIntent ().getStringExtra ( "url" );  
        //MoaiLog.i ( "MoaiMoviePlayer onCreate: Initializing video player with media URL " + url );
        //mVideoView.setVideoURI ( Uri.parse ( url ));
        //mVideoView.requestFocus ();      
        
        
        String url = this.getIntent ().getStringExtra ( "url" );  
        Log.v("EGL", "URL: "+url);
        String uri = "android.resource://" + getPackageName() + "/raw/"+url;
        mVideoView.setVideoURI(Uri.parse(uri));
        mVideoView.start();           
    
  }  

  //----------------------------------------------------------------//
  protected void onDestroy () {
    
    super.onDestroy ();
    
    sMovie = null;
  }
  
  //----------------------------------------------------------------//
  public void startPlayback () {
    
    if ( mVideoView.isPlaying ()) {

      mVideoView.resume ();
    } else {

      mVideoView.start ();
    }
  }
  
  //----------------------------------------------------------------//
  public void pausePlayback () {
    
    mVideoView.pause ();
  }

  //----------------------------------------------------------------//
  public void stopPlayback () {

    mVideoView.stopPlayback ();
  }

  //================================================================//
  // OnPreparedListener methods
  //================================================================//

  public void onPrepared ( MediaPlayer mediaPlayer ) {

    MoaiLog.i ( "MoaiMoviePlayer onPrepared" );
    
    AKUNotifyMoviePlayerReady ();
  }

  //================================================================//
  // OnCompletionListener methods
  //================================================================//

  public void onCompletion ( MediaPlayer mediaPlayer ) {

    MoaiLog.i ( "MoaiMoviePlayer onCompletion" );
    
    AKUNotifyMoviePlayerCompleted ();
  }
}
