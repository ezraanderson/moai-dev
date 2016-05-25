package com.chartboost.sdk.sample.cbtest;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Toast;

import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostActivity;
import com.chartboost.sdk.sample.R;

public class CBTestActivitySimple extends ChartboostActivity {

    private static final String TAG = "Chartboost";
    private Chartboost cb;
    
    
    /* The following three methods use the app ID, signature, and public key
     * found on the Chartboost dashboard. */

    @Override
    protected String getChartboostAppID() {
        return "";
    }

    @Override
    protected String getChartboostAppSignature() {
        return "";
    }
    
    
    /* Set up the activity, and save a reference to Chartboost to interact with it. */

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.simple);

		// Configure Chartboost
		this.cb = Chartboost.sharedChartboost();
	}
    
	
    /* Override any Chartboost delegate methods you need.
     * This activity serves as its own delegate. */

    @Override
    public boolean shouldDisplayInterstitial(String location) {
        Log.i(TAG, "SHOULD DISPLAY INTERSTITIAL '"+location+ "'?");
        return true;
    }

    @Override
    public void didDismissInterstitial(String location) {
        Log.i(TAG, "INTERSTITIAL '"+location+"' DISMISSED");
        Toast.makeText(this, "Dismissed Interstitial '"+location+"'",
                Toast.LENGTH_SHORT).show();
    }
    
    
    /* The following methods reflect the buttons in our UI. */

	public void onLoadButtonClick(View view) {
		String toastStr = "Loading Interstitial";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		this.cb.showInterstitial();
	}

	public void onMoreButtonClick(View view) {
		String toastStr = "Loading More Apps";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		this.cb.showMoreApps();
	}

	public void gotoActivityB(View view) {
		this.startActivity(new Intent(this, CBTestActivityB.class));
	}

	protected String getChartboostAppPublicKey() {
		// TODO Auto-generated method stub
		return null;
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