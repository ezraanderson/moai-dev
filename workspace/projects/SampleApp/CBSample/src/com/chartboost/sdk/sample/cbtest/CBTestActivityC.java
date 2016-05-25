package com.chartboost.sdk.sample.cbtest;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;

import com.chartboost.sdk.CBPreferences;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.sample.R;
import com.chartboost.sdk.ChartboostDelegate;

public class CBTestActivityC extends Activity {

	private static final String TAG = "Chartboost";
	private Chartboost cb;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) { 
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		setContentView(R.layout.mainc);

		// Configure Chartboost
		this.cb = Chartboost.sharedChartboost();
		String appId = "";
		String appSignature = "";
		this.cb.onCreate(this, appId, appSignature, this.chartBoostDelegate);

		CheckBox chk = (CheckBox)findViewById(R.id.chkImpUseAct);
		chk.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton arg0, boolean arg1) {
				CBPreferences.getInstance().setImpressionsUseActivities(arg1);
			}
		});
		chk.setChecked(CBPreferences.getInstance().getImpressionsUseActivities());
	}

	@Override
	protected void onStart() {
		super.onStart();
		this.cb.onStart(this);
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

	private ChartboostDelegate chartBoostDelegate = new LoggingChartboostDelegate(this, TAG) {
		@Override
		public boolean shouldPauseClickForConfirmation(
				final CBAgeGateConfirmation callback) {
			AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
					CBTestActivityC.this);
	 
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