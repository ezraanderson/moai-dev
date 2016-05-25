package com.chartboost.sdk.sample.cbtest;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.sample.R;
import com.chartboost.sdk.ChartboostDelegate;

public class CBTestActivityB extends Activity {

	private static final String TAG = "Chartboost";
	private Chartboost cb;
	
	private FrameLayout sv;

    private GLSurfaceView mGLView;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) { 
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		setContentView(R.layout.mainb);
		
        mGLView = new GLSurfaceView(this);
        mGLView.setRenderer(new ClearRenderer());
		
		sv = (FrameLayout)findViewById(R.id.surfaceViewParent);
		sv.addView(mGLView, new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
		//sv.getHolder().addCallback(this);

		// Configure Chartboost
		this.cb = Chartboost.sharedChartboost();
		String appId = "";
		String appSignature = "";
		this.cb.onCreate(this, appId, appSignature, this.chartBoostDelegate);
	}

	@Override
	protected void onStart() {
		super.onStart();
		this.cb.onStart(this);
	}

    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

	@Override
	protected void onStop() {
		super.onStop();
		this.cb.onStop(this);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		this.cb.onDestroy(this);
	}

	@Override
	public void onBackPressed() {
		if (this.cb.onBackPressed())
			return;
		else
			super.onBackPressed();
	}

	public void onLoadButtonClick(View view) {
		Log.i(TAG, "Load!");

		String toastStr = "Loading Interstitial";
		if (cb.hasCachedInterstitial())
			toastStr = "Loading Interstitial From Cache";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		this.cb.showInterstitial();
	}

	public void onMoreButtonClick(View view) {
		Log.i(TAG, "More!");
		String toastStr = "Loading More Apps";
		if (cb.hasCachedMoreApps())
			toastStr = "Loading More Apps From Cache";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		this.cb.showMoreApps();
	}

	static class ClearRenderer implements GLSurfaceView.Renderer {
	    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	        // Do nothing special.
	    }
	
	    public void onSurfaceChanged(GL10 gl, int w, int h) {
	        gl.glViewport(0, 0, w, h);
	    }
	
	    public void onDrawFrame(GL10 gl) {
	    	try {
	    		// without this, chartboost's animation would be choppy!
				Thread.sleep(15);
			} catch (InterruptedException e) {
				//
			}
	        gl.glClearColor(1, 0, 0, 0.0f);
	        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
	    }
	}

	public void gotoActivityC(View view) {
		this.startActivity(new Intent(this, CBTestActivityC.class));
	}

	private ChartboostDelegate chartBoostDelegate = new LoggingChartboostDelegate(this, TAG) {

		@Override
		public boolean shouldPauseClickForConfirmation(
				final CBAgeGateConfirmation callback) {
			AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
					CBTestActivityB.this);
	 
				// set title
				alertDialogBuilder.setTitle("Age Validation");
	 
				// set dialog message
				alertDialogBuilder
					.setMessage("Click yes if you are 18 year or older !")
					.setCancelable(false)
					.setPositiveButton("Yes",new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog,int id) {
							callback.execute(true);
						}
					  })
					.setNegativeButton("No",new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog,int id) {
							callback.execute(false);
						}
					});
	 
					// create alert dialog
					AlertDialog alertDialog = alertDialogBuilder.create();
	 
					// show it
					alertDialog.show();
					return true;
		}

	};
}