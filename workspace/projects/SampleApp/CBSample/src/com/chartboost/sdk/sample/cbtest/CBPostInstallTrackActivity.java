package com.chartboost.sdk.sample.cbtest;

import java.util.EnumMap;

import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.Libraries.CBLogging.Level;
import com.chartboost.sdk.Tracking.CBPostInstallTracker;
import com.chartboost.sdk.Tracking.CBPostInstallTracker.CBIAPType;
import com.chartboost.sdk.Tracking.CBPostInstallTracker.CBIAPPurchaseInfo;
import com.chartboost.sdk.sample.R;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.IabHelper;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.IabResult;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.Inventory;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.Purchase;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.SkuDetails;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class CBPostInstallTrackActivity extends Activity{

	private static final String TAG = "com.chartboost.sdk.sample.cbtest.inappbilling";
    private static final int INAPP_REQUEST_CODE = 10001;
    private static final String RELEASE_ITEM_SKU = "com.chartboost.click";
    
    /** SKU used for testing if you don't wanna publish your app*/
    //private static final String TEST_ITEM_SKU = "android.test.purchased";
    
	private Button clickButton;
	private Button buyButton;
    private Chartboost cb;
    private String ITEM_SKU;
    
	IabHelper mHelper;
	Inventory inventory;
	CBPostInstallTracker pit;
    
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.pit);
		
		// Configure Chartboost
		this.cb = Chartboost.sharedChartboost();
		String appId = "";
		String appSignature = "";
		this.cb.onCreate(this, appId, appSignature, null);
		this.cb.getPreferences().setLoggingLevel(Level.ALL);
		
		buyButton = (Button)findViewById(R.id.buyButton);
		clickButton = (Button)findViewById(R.id.clickButton);	
		clickButton.setEnabled(false);
		
		/** Replace this sku with TEST_ITEM_SKU above if you are gonna test it without publishing */
		ITEM_SKU = RELEASE_ITEM_SKU;
		
		/** Get you public key from your developer google play store account for the corresponding app and put it in
		 * the strings.xml file under the string "base64EncodedPublicKey" */
		String base64EncodedPublicKey = getResources().getString(R.string.base64EncodedPublicKey);

		/*Setting up Inapp billing purchase*/
		mHelper = new IabHelper(this, base64EncodedPublicKey);
		mHelper.enableDebugLogging(true);
		mHelper.startSetup(new 
		IabHelper.OnIabSetupFinishedListener() {
		public void onIabSetupFinished(IabResult result) 
		{
		if (!result.isSuccess()) {
		  Log.d(TAG, "In-app Billing setup failed: " + 
		result);
		} else {
		    Log.d(TAG, "In-app Billing is set up OK");
		}
		}
		});
	}
	
	public void buttonClicked (View view)
	{
		clickButton.setEnabled(false);
		buyButton.setEnabled(true);
	}
	
	public void buyClick(View view) {
		
	     mHelper.launchPurchaseFlow(this, ITEM_SKU, INAPP_REQUEST_CODE,  mPurchaseFinishedListener, "mypurchasetoken");
	}
	
	IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {

	@Override
	public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
		Log.d(TAG, "###### onIabPurchaseFinished"+purchase +"#####"+ ITEM_SKU);
		if (result.isFailure()) {
			 Runnable r = new Runnable() {				
			@Override
			public void run() {
			    mHelper.myconsume(CBPostInstallTrackActivity.this.getPackageName(), "inapp:"+getPackageName()+":android.test.purchased");
			}
		};
		r.run(); 
		Log.d(TAG,"###### onIabPurchaseFinished Error ");
		 return;
		 }      
		 else if (purchase.getSku().equals(ITEM_SKU)) {
			    mHelper.queryInventoryAsync(mReceivedInventoryListener);
			    buyButton.setEnabled(false);
		}
		
		}
	};
		
	IabHelper.QueryInventoryFinishedListener mReceivedInventoryListener 
		   = new IabHelper.QueryInventoryFinishedListener() {
		
			@Override
			public void onQueryInventoryFinished(IabResult result, Inventory inv) {
				Log.d(TAG,"###### onQueryInventoryFinished : " + inv);
			      if (result.isFailure()) {
					  // Handle failure
				      } 
			      else {
				    		  if(pit != null){
									 SkuDetails item = inv.getSkuDetails(ITEM_SKU);
									 Purchase purchase = inv.getPurchase(ITEM_SKU);
									 if(item !=null && purchase != null) {
										 String data = purchase.getOriginalJson();							 
										 String signature = purchase.getSignature();
										 if(item != null){
										   	    EnumMap<CBIAPPurchaseInfo, String> map = new EnumMap<CBIAPPurchaseInfo, String>(CBIAPPurchaseInfo.class);
												map.put(CBIAPPurchaseInfo.PRODUCT_ID, purchase.getSku());
												map.put(CBIAPPurchaseInfo.PRODUCT_TITLE,item.getTitle());
												map.put(CBIAPPurchaseInfo.PRODUCT_DESCRIPTION, item.getDescription());
												map.put(CBIAPPurchaseInfo.PRODUCT_PRICE, item.getPrice());
												map.put(CBIAPPurchaseInfo.PRODUCT_CURRENCY_CODE, item.getCurrencyCode());
												map.put(CBIAPPurchaseInfo.GOOGLE_PURCHASE_DATA, data);
												map.put(CBIAPPurchaseInfo.GOOGLE_PURCHASE_SIGNATURE, signature );		
												pit.trackInAppPurchaseEvent(map,CBIAPType.GOOGLE_PLAY);
												Log.d(TAG,"########## Sending it to Chartboost SDK###########");
										 }
									 }
								}
				    		  mHelper.consumeAsync(inv.getPurchase(ITEM_SKU), mConsumeFinishedListener);
				    }
			}
	};
		
	IabHelper.OnConsumeFinishedListener mConsumeFinishedListener =
		new IabHelper.OnConsumeFinishedListener() {
			 public void onConsumeFinished(Purchase purchase, 
			       IabResult result) {
				 Log.d(TAG,"###### onConsumeFinished");
				if (result.isSuccess()) {		    	 
					Log.d(TAG,"###### onConsumeFinished sucess");
				} 
				buyButton.setEnabled(true);
			}
	};

		
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "onActivityResult(" + requestCode + "," + resultCode + "," + data);
        if (mHelper == null) return;

        // Pass on the activity result to the helper for handling
        if (!mHelper.handleActivityResult(requestCode, resultCode, data)) {
            // not handled, so handle it ourselves (here's where you'd
            // perform any handling of activity results not related to in-app
            // billing...
            super.onActivityResult(requestCode, resultCode, data);
        }
        else {
            Log.d(TAG, "onActivityResult handled by IABUtil.");
        }
		
	};
    
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
	
	public void trackMiscRevenueGeneratingEventOfType(View view) {
		String toastStr = "Sending trackMiscRevenueGeneratingEventOfType to SDK ..";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		//pit.trackMiscRevenueGeneratingEvent(CBMiscRevenueGeneratingEventType.CBMiscRevenueGeneratingEventType1, 100, "USD", "HayDay");
	}
	
	public void trackCustomEventOfType(View view) {
		String toastStr = "Sending trackCustomEventOfType to SDK ..";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		//pit.trackCustomEventofType(CBCustomEventType.CBCustomEventType1, 2);
	}
	
	public void trackInGameScore(View view) {
		String toastStr = "Sending trackInGameScore to SDK ..";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		//pit.trackInGameScore(10);
	}
	
	public void trackPlayerCurrencyBalance(View view) {
		String toastStr = "Sending trackPlayerCurrencyBalance to SDK ..";
		Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
		//pit.trackPlayerCurrencyBalance(5, "USD");
	}

	/*Activity callback methods*/
	@Override
	protected void onStart() {
		super.onStart();
		this.cb.onStart(this);

	}
	
	@Override
	protected void onResume() {
		super.onResume();
		System.out.println("### onResume");
		pit= CBPostInstallTracker.sharedPostInstallTracker();
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
	public void onBackPressed() {
		if (this.cb.onBackPressed())
			return;
		else
			super.onBackPressed();
	}
	
	@Override
	public void onDestroy() {
		super.onDestroy();
		this.cb.onDestroy(this);
		if (mHelper != null) mHelper.dispose();
		mHelper = null;
	}
}
