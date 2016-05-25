package com.ziplinegames.moai;

import android.app.Activity;
import android.util.Log;

import com.chartboost.sdk.*;
//import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
//import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

class MoaiChartBoost {

	private static int     ad_step = 0; 
	private static  Activity sActivity = null;
	private static  MoaiChartBoost instance = null;
	private static  Chartboost cb;
	
	
	
/*
	private static ChartboostDelegate chartBoostDelegate = new ChartboostDelegate() {

	    public boolean shouldDisplayInterstitial(String location) {
	        return true;
	    }

	    @Override
	    public boolean shouldRequestInterstitial(String location) {
	        return true;
	    }

	    //@Override
	    //public void didCacheInterstitial(String location) {
	    	//MoaiLog.i ( "MoaiChartboost didCacheInterstitial: didCacheInterstitial" );
	   // }

	    @Override
	    public void didDismissInterstitial(String location) {
	        cb.cacheInterstitial(location);
	    }

	    @Override
	    public void didCloseInterstitial(String location) {
	        // Know that the user has closed the interstitial
	    }

	    @Override
	    public void didClickInterstitial(String location) {
	        // Know that the user has clicked the interstitial
	    }

	    //@Override
	    //public void didShowInterstitial(String location) {
	        //MoaiLog.i ( "MoaiChartboost didShowInterstitial: didShowInterstitial" );
	    //}

	   // @Override
	   // public boolean shouldDisplayLoadingViewForMoreApps() {
	   //     return true;
	    //}

	    //@Override
	   // public boolean shouldRequestMoreApps() {
	    //    return true;
	    //}

	   // @Override
	   // public boolean shouldDisplayMoreApps() {
	   //     return true;
	   // }

	   // @Override
	   // public void didCacheMoreApps() {
	        // Know that the More-Apps page is cached and ready to display
	   // }

	   // @Override
	   // public void didDismissMoreApps() {
	        // Know that the More-Apps page has been dismissed
	   // }

	   // @Override
	   // public void didCloseMoreApps() {
	        // Know that the More-Apps page has been closed
	   // }

	   // @Override
	   // public void didClickMoreApps() {
	        // Know that the More-Apps page has been clicked

	   // }

	   // @Override
	   // public void didShowMoreApps() {
	        // Know that the More-Apps page has been presented on the screen
	   // }

	  //  @Override
	  //  public boolean shouldRequestInterstitialsInFirstSession() {
	  //      return true;
	 //   }

		//@Override
		//public void didFailToLoadInterstitial(String arg0,
		//		CBImpressionError arg1) {
			// TODO Auto-generated method stub
			
		//}

		//@Override
		//public void didFailToLoadMoreApps(CBImpressionError arg0) {
		//	// TODO Auto-generated method stub
			
		//}

		//@Override
		//public void didFailToRecordClick(String arg0, CBClickError arg1) {
			// TODO Auto-generated method stub
			
		//}

		
		//@Override
		//public boolean shouldPauseClickForConfirmation(CBAgeGateConfirmation arg0) {
			// TODO Auto-generated method stub
		//	return false;
		//}
		
		
	};
	
	
	
	*/
	
	
	
	
	
	
	
	
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
