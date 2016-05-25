# Chartboost for Android

*Version 4.1.1 (2014-06-23)*

The Chartboost SDK is the cornerstone of the Chartboost network. It provides the functionality for showing intersitials, More-Apps pages, and tracking in-app purchase revenue. 


### Usage

Integrating Chartboost takes a few easy steps:

1. Make sure your app fits the minimum requirements:
     - Minimum API level 9 (Android OS 2.3)
     - Required permission: `android.permission.INTERNET`
     - Required permission: `android.permission.ACCESS_NETWORK_STATE`
     - Optional (recommended) permissions: `android.permission.WRITE_EXTERNAL_STORAGE`, `android.permission.ACCESS_WIFI_STATE`

2. Add the `chartboost.jar` file to your `libs` directory
     - If you don't have a `libs` directory, create one and add the .jar file to it
     - Optionally add `chartboost.jar.properties` and the `doc` directory to `libs` to get javadocs in your IDE

3. Add the Google Play Services library as a dependency of your project.
     - The GPS library has its own set of integration instructions, including additions to your Android Manifest and Proguard configuration
     - You can follow the setup instructions outlined by Google at the [Google Developer website](https://developer.android.com/google/play-services/setup.html)

4. Import the Chartboost SDK into any activity that uses Chartboost
    
    ```java
    import com.chartboost.sdk.*;
    ```
    
5. Create an instance variable in the activity that uses Chartboost
 
    ```java
    private Chartboost cb;
    ```

6. Add the following code to your `onCreate()` method:
    
    ```java
    // Configure Chartboost
    this.cb = Chartboost.sharedChartboost();
    String appId = "YOUR_APP_ID";
    String appSignature = "YOUR_APP_SIGNATURE";
    this.cb.onCreate(this, appId, appSignature, null);
    ```

7. Add the following code to your activity's `onStart()`, `onStop()`, `onDestroy()`, and `onBackPressed()` methods:

    ```java
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
        this.cb.onDestroy(this);
        super.onDestroy();
    }
    
    @Override
    public void onBackPressed() {
        // If an interstitial is on screen, close it. Otherwise continue as normal.
        if (this.cb.onBackPressed())
            return;
        else
            super.onBackPressed();
    }
    ```

8. Back in step (6) we called `onCreate()` with `null` as the final parameter.  This parameter, if supplied, is a delegate object that allows one to fine-tune the behavior of Chartboost. Simply supply an object that implements `ChartboostDelegate`. As an alternative, extend from `ChartboostDefaultDelegate` if you do not want to bother overriding all of the delegate methods.
 
9. As an alternative to steps (5) through (8), you can simply have your activities that use Chartboost extend from `ChartboostActivity` or `ChartboostNativeActivity`.  The only implementation necessary is returning the app's Chartboost ID and signature in two abstract methods that you will required to fill in.  These two base classes also implement `ChartboostDelegate` and use themselves as the Chartboost delegate, so feel free to override any delegate methods that you need to use.
 
10. If you plan on using Proguard, add the following to your *proguard.cfg* file (also make sure you follow Proguard instructions for the Google Play Services library):

    ```
    -keep class com.chartboost.** { *; }
    ```


# Post Install Tracking: 
 Post Install Tracking product is basically used to track events once a game is installed and the user starts playing the game. It's basically provides the developers some fine grain information about the game event the  user is playing. Chartboost SDK for this release supports just `In-App Purchasing` more events API's will be added soon.
        
* **In-app Purchasing:**
      In-App Purchase lets you sell a variety of items directly within your free or paid app, including premium content, virtual goods, and subscriptions. Chartboost SDK provides an API to track these purchase by sending the information to the SDK. Chartboost Android SDK will support `GooglePlayStore`, `Amazon` In-app purchasing. If you are using Chartboost Store In-App purchase are tracked automatically by the SDK.

      ```
      trackInAppPurchaseEvent( EnumMap<CBIAPPurchaseInfo, String> map,  CBIAPType iapType)
      ```

*  **Example**

* `Google`
```javascript
EnumMap<CBIAPPurchaseInfo, String> map = new EnumMap<CBIAPPurchaseInfo, String>(CBIAPPurchaseInfo.class);
                        map.put(CBIAPPurchaseInfo.PRODUCT_ID,"xxx-id");
            map.put(CBIAPPurchaseInfo.PRODUCT_TITLE,"xxx-title");
            map.put(CBIAPPurchaseInfo.PRODUCT_DESCRIPTION, "xxx-description");
            map.put(CBIAPPurchaseInfo.PRODUCT_PRICE, "$0.99");
            map.put(CBIAPPurchaseInfo.PRODUCT_CURRENCY_CODE,"USD");
            map.put(CBIAPPurchaseInfo.GOOGLE_PURCHASE_DATA, "xxx-data");
            map.put(CBIAPPurchaseInfo.GOOGLE_PURCHASE_SIGNATURE, "xxx-signature");
            trackInAppPurchaseEvent(map, CBIAPType.GOOGLE_PLAY);
```


* `Amazon`
```javascript
EnumMap<CBIAPPurchaseInfo, String> map = new EnumMap<CBIAPPurchaseInfo, String>(CBIAPPurchaseInfo.class);
            map.put(CBIAPPurchaseInfo.PRODUCT_ID,"xxx-id");
            map.put(CBIAPPurchaseInfo.PRODUCT_TITLE,"xxx-title");
            map.put(CBIAPPurchaseInfo.PRODUCT_DESCRIPTION, "xxx-description");
            map.put(CBIAPPurchaseInfo.PRODUCT_PRICE, "$0.99");
            map.put(CBIAPPurchaseInfo.PRODUCT_CURRENCY_CODE,"USD");
            map.put(CBIAPPurchaseInfo.AMAZON_USER_ID, "xxx-userId");
            map.put(CBIAPPurchaseInfo.AMAZON_PURCHASE_TOKEN, "xxx-token");
            trackInAppPurchaseEvent(map,CBIAPType.AMAZON);
```
### Dive deeper

Please check out our example code: https://github.com/ChartBoost/client-examples

If you encounter any issues, do not hesitate to contact our happy support team at [support@chartboost.com](mailto:support@chartboost.com)

