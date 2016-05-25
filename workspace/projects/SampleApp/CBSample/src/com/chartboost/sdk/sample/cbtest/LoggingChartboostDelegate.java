package com.chartboost.sdk.sample.cbtest;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.ChartboostDelegate;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

public class LoggingChartboostDelegate implements ChartboostDelegate {
	
	private String TAG;
	private Context ctx;
	
	public LoggingChartboostDelegate(Context cx, String tag) {
		TAG = tag;
		ctx = cx;
	}

	/**
	 * Interstital
	 */
	@Override
	public boolean shouldRequestInterstitial(String location) {
		Log.i(TAG, "SHOULD REQUEST INSTERSTITIAL '"+location+ "'?");
		return true;
	}

	@Override
	public boolean shouldDisplayInterstitial(String location) {
		Log.i(TAG, "SHOULD DISPLAY INTERSTITIAL '"+location+ "'?");
		return true;
	}

	@Override
	public void didCacheInterstitial(String location) {
		Log.i(TAG, "INTERSTITIAL '"+location+"' CACHED");
		Toast.makeText(ctx, "Interstitial '"+location+"' Cached",
				Toast.LENGTH_SHORT).show();
	}

	@Override
	public void didFailToLoadInterstitial(String location, CBImpressionError error) {
		Log.i(TAG, "INTERSTITIAL '"+location+"' REQUEST FAILED - " + error.name());
		Toast.makeText(ctx, "Interstitial '"+location+"' Load Failed",
				Toast.LENGTH_SHORT).show();
	}

	@Override
	public void didDismissInterstitial(String location) {
		Log.i(TAG, "INTERSTITIAL '"+location+"' DISMISSED");
	}

	@Override
	public void didCloseInterstitial(String location) {
		Log.i(TAG, "INSTERSTITIAL '"+location+"' CLOSED");
	}

	@Override
	public void didClickInterstitial(String location) {
		Log.i(TAG, "DID CLICK INTERSTITIAL '"+location+"'");
	}

	@Override
	public void didShowInterstitial(String location) {
		Log.i(TAG, "INTERSTITIAL '" + location + "' SHOWED");
	}

	@Override
	public boolean shouldDisplayLoadingViewForMoreApps() {
		return true;
	}

	@Override
	public boolean shouldRequestMoreApps() {
		Log.i(TAG, "SHOULD REQUEST MORE APPS?");
		return true;
	}

	@Override
	public boolean shouldDisplayMoreApps() {
		Log.i(TAG, "SHOULD DISPLAY MORE APPS?");
		return true;
	}

	@Override
	public void didFailToLoadMoreApps(CBImpressionError error) {
		Log.i(TAG, "MORE APPS REQUEST FAILED - " + error.name());
		Toast.makeText(ctx, "More Apps Load Failed",
				Toast.LENGTH_SHORT).show();
	}

	@Override
	public void didCacheMoreApps() {
		Log.i(TAG, "MORE APPS CACHED");
		Toast.makeText(ctx, "More Apps Cached",
				Toast.LENGTH_SHORT).show();
	}

	@Override
	public void didDismissMoreApps() {
		Log.i(TAG, "MORE APPS DISMISSED");
	}

	@Override
	public void didCloseMoreApps() {
		Log.i(TAG, "MORE APPS CLOSED");
	}

	@Override
	public void didClickMoreApps() {
		Log.i(TAG, "MORE APPS CLICKED");
	}

	@Override
	public void didShowMoreApps() {
		Log.i(TAG, "MORE APPS SHOWED");
	}

	@Override
	public boolean shouldRequestInterstitialsInFirstSession() {
		return true;
	}

	@Override
	public void didFailToRecordClick(String uri, CBClickError error) {
		Log.i(TAG, "FAILED TO RECORD CLICK " + (uri != null ? uri : "null") + ", error: " + error.name());
	}

	@Override
	public boolean shouldPauseClickForConfirmation(final CBAgeGateConfirmation callback) {
		return false;
	}

	/* not supported yet
	@Override
	public void didCacheRewardedVideo(String location) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void didClickRewardedVideo(String location) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void didCloseRewardedVideo(String location) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void didCompleteRewardedVideo(int reward, String location) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void didDismissRewardedVideo(String location) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void didFailToLoadRewardedVideo(String location,
			CBImpressionError error) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean shouldDisplayRewardedVideo(String location) {
		// TODO Auto-generated method stub
		return true;
	} */

}
