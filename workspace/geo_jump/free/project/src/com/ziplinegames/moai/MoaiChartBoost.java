package com.ziplinegames.moai;

import android.app.Activity;
import android.util.Log;

import com.chartboost.sdk.*;
//import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
//import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

class MoaiChartBoost {

	protected static native void AKUNotifyChartBoostInterstitialDismissed();
	protected static native void AKUNotifyChartBoostInterstitialLoadFailed();
	
	private static int     ad_step = 0; 
	private static  Activity sActivity = null;
	private static  MoaiChartBoost instance = null;
	private static  Chartboost cb;


	private static ChartboostDelegate delegate = new ChartboostDelegate() {
	
	    
		public void dismiss(){
			sActivity.runOnUiThread(new Runnable() {
			    public void run() {		
						    synchronized ( Moai.sAkuLock ) {
						    	AKUNotifyChartBoostInterstitialDismissed();
						    };
			    }
			});
		};
		
	    //*********************************************************
		//ADS
		
	    @Override
	    public void didDismissInterstitial(String location) {
	    	Log.v("LOG", "didDismissInterstitial"); 
	    	dismiss();
	    	
	    	
	    	
	    	
	    	
	    	//AKUNotifyChartBoostInterstitialDismissed();	  
	    }

	    @Override
	    public void didCloseInterstitial(String location) {
	    	Log.v("LOG", "didCloseInterstitial"); 
	    	dismiss();
	    	//AKUNotifyChartBoostInterstitialDismissed();
	    }

	    @Override
	    public void didClickInterstitial(String location) {
	    	Log.v("LOG", "didClickInterstitial"); 
	    	dismiss();
	    	//AKUNotifyChartBoostInterstitialDismissed();
	    }

	    
	    
	    //*********************************************************
	    //MORE APPS
	    
		// @Override
	    public void didDismissMoreApps() {
	    	Log.v("LOG", "MORE APPS : didDismissMoreApps");
	    	dismiss();
	    	//AKUNotifyChartBoostInterstitialDismissed();
	    }

	   // @Override
	    public void didCloseMoreApps() {
	    	Log.v("LOG", "MORE APPS : didCloseMoreApps"); 
	    	dismiss();
	    	//AKUNotifyChartBoostInterstitialDismissed();
	    }

	   // @Override
	    public void didClickMoreApps() {
	    	Log.v("LOG", "MORE APPS : didClickMoreApps"); 
	    	dismiss();
	    	//AKUNotifyChartBoostInterstitialDismissed();
	    };
	      		
		
	};
	
	
	
	
	//*****************************************************************************
	//*****************************************************************************
	

	public static void onCreate ( Activity activity ) {
		MoaiLog.i ( "MoaiChartBoost onCreate: Initializing Chartboost" );
		sActivity = activity;
	}

	public static void onDestroy () {
		MoaiLog.i ( "MoaiChartBoost onDestroy: Destroying Chartboost service" );
		cb.onDestroy(sActivity);
	}
	
//*****************************************************************************
//*****************************************************************************
	public static void init(final String appId, final String appSignature) {		
	
		sActivity.runOnUiThread(new Runnable() {
		    public void run() {		
			    	
		    	Chartboost.startWithAppId(sActivity, appId, appSignature);					
		    	Chartboost.onStart(sActivity);		 
		    	Chartboost.setDelegate(delegate);
		    	Chartboost.cacheInterstitial(CBLocation.LOCATION_DEFAULT);		    	
		    	Chartboost.cacheMoreApps(CBLocation.LOCATION_DEFAULT);		    
		    }
		});
		
	}

	
	//*************************************************************
	public static void showInterstitial(String location) {
				sActivity.runOnUiThread(new Runnable() {
				    public void run() {
				    	Chartboost.showInterstitial(CBLocation.LOCATION_DEFAULT);
				}
				});
		    
	}

	
	//*************************************************************
	public static boolean hasCachedInterstitial() {
		
		
		
		boolean hasAd = Chartboost.hasInterstitial(CBLocation.LOCATION_DEFAULT);	
		
		//*************************************************************
		// STATIC
		// VIDEO
		// STATIC
		// GAMES
		
		
		
		
		//**********************************************************
		//hasAd = false;
		ad_step = ad_step + 1;
		if (ad_step >= 3) {
			ad_step = 0;
			hasAd = false;
		};		
		Log.v("LOG", "SHOW MORE APPS: "+hasAd+" "+ad_step); 		
		
		//**********************************************************
			if (hasAd== false) {		
				sActivity.runOnUiThread(new Runnable() {
				    public void run() {				    	   
				    		//SHOW
				    		Chartboost.showMoreApps(CBLocation.LOCATION_DEFAULT);
				    
				    		
					    	//LOAD				    		
					    	Chartboost.cacheInterstitial(CBLocation.LOCATION_DEFAULT);	
							Chartboost.cacheMoreApps(CBLocation.LOCATION_DEFAULT);
					   
			
				    }});				
			};	
			
			
			
			
			
		//**********************************************************	
		//SHOW ADD
			if (hasAd == true) {	
				sActivity.runOnUiThread(new Runnable() {
				    public void run() {
				    	//SHOW
				    		Chartboost.showInterstitial(CBLocation.LOCATION_DEFAULT);
				    	//LOAD
					    	Chartboost.cacheInterstitial(CBLocation.LOCATION_DEFAULT);		    	
					    	Chartboost.cacheMoreApps(CBLocation.LOCATION_DEFAULT);
				    		
				}
				});
				
			};
			
			return hasAd;
	}

	
	
	
	
	//*************************************************************
	public static void loadInterstitial(String location) {
				sActivity.runOnUiThread(new Runnable() {
				    public void run() {
				    	Chartboost.cacheInterstitial(CBLocation.LOCATION_DEFAULT);		    	
				    	Chartboost.cacheMoreApps(CBLocation.LOCATION_DEFAULT);
				    }
				});
	}
}
