package com.chartboost.sdk.sample.cbtest;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.Spinner;

import com.chartboost.sdk.CBPreferences;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;
import com.chartboost.sdk.Libraries.CBOrientation;
import com.chartboost.sdk.sample.R;

public class CBTestActivityA extends Activity {

	private static final String TAG = "Chartboost";
	private Chartboost cb;
	private CBPreferences cbPref;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) { 
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		setContentView(R.layout.main);
		
		// Configure Chartboost
		this.cb = Chartboost.sharedChartboost();
		this.cbPref = CBPreferences.getInstance();
		
		String appId = "";
		String appSignature = "";
		
		// create!
		this.cb.onCreate(this, appId, appSignature, this.chartBoostDelegate);
		
		// testSpecialDataFeatures();
		
		// NOTE: THIS DOES NOT WORK PROPERLY AS THE TARGETSDKVERSION IS SET TO 15
		configureSpinner();
		CheckBox chk = (CheckBox)findViewById(R.id.chkImpUseAct);
		chk.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton arg0, boolean arg1) {
				cbPref.setImpressionsUseActivities(arg1);
			}
		});
		chk.setChecked(cbPref.getImpressionsUseActivities());
	}

	private void configureSpinner() {
		Spinner spinner = (Spinner)this.findViewById(R.id.spinner);
		spinner.setOnItemSelectedListener(new OnItemSelectedListener() {
			private CBOrientation[] choices = new CBOrientation[] {
				CBOrientation.UNSPECIFIED,
				CBOrientation.PORTRAIT,
				CBOrientation.LANDSCAPE,
				CBOrientation.PORTRAIT_REVERSE,
				CBOrientation.LANDSCAPE_REVERSE
			};
			
			@Override
			public void onItemSelected(AdapterView<?> parent, View view,
					int position, long id) {
				CBTestActivityA.this.cbPref.setOrientation(choices[position]);
			}

			@Override
			public void onNothingSelected(AdapterView<?> parent) {
				//
			}
		});
	}

	@Override
	protected void onStart() {
		super.onStart();
		this.cb.onStart(this);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
	}
	
	@Override
	protected void onPause() {
		super.onPause();
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
		String toastStr = "Loading Interstitial";
		if (cb.hasCachedInterstitial())
			toastStr = "Loading Interstitial From Cache";
		Log.i(TAG, toastStr);
		this.cb.showInterstitial();
	}

	public void onMoreButtonClick(View view) {
		String toastStr = "Loading More Apps";
		if (cb.hasCachedMoreApps())
			toastStr = "Loading More Apps From Cache";
		Log.i(TAG, toastStr);
		this.cb.showMoreApps();
	}

	public void onPreloadClick(View v) {
		Log.i(TAG, "Preloading Interstitial Ad");
		cb.cacheInterstitial();
	}

	public void onPreloadMoreAppsClick(View v) {
		Log.i(TAG, "Preloading Interstitial Ad");
		cb.cacheMoreApps();
	}

	public void onPreloadClearClick(View v) {
		Log.i(TAG, "Clearing preload ad data");
		cb.clearCache();
	}

	public void onPerformTestClick(View view) {
		Log.i(TAG, "Perform test!");

		try {

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void gotoActivityB(View view) {
		this.startActivity(new Intent(this, CBTestActivityB.class));
	}

	public void gotoActivityC(View view) {
		this.startActivity(new Intent(this, CBTestActivityC.class));
	}
	
	// not supported yet
	public void onLoadVideoClick(View view) {
		/*String toastStr = "Loading Rewarded Interstitial";
		if (cb.hasRewardedVideo(CBLocation.CBLocationAchievements))
			toastStr = "Loading Rewarded Interstitial From Cache";
		Log.i(TAG, toastStr);
		this.cb.showRewardedVideo(CBLocation.CBLocationAchievements); */
	}

	public void onPreloadVideoClick(View v) {
		/*Log.i(TAG, "Preloading Rewarded Interstitial Ad");
		cb.cacheRewardedVideo(CBLocation.CBLocationAchievements);*/
	}
	private ChartboostDelegate chartBoostDelegate = new LoggingChartboostDelegate(this, TAG);
	
}