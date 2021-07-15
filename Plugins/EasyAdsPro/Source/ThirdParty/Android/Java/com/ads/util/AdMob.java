/*
* EasyAdsPro - unreal engine 4 ads plugin
*
* Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

package com.ads.util;

//import android.os.Bundle;
import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import androidx.annotation.NonNull;
import com.google.ads.consent.*;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;
import java.text.Normalizer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;
import java.util.logging.Logger;
import java.util.Random;

import java.util.Timer;
import java.util.TimerTask;

import com.google.ads.mediation.admob.AdMobAdapter;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.RequestConfiguration;
import com.google.android.gms.ads.initialization.AdapterStatus;
import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.reward.RewardedVideoAd;
import com.google.android.gms.ads.reward.RewardedVideoAdListener;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.android.gms.ads.rewarded.RewardedAdCallback;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;

//import static com.google.android.gms.internal.zzs.TAG;
import java.util.Set;

public class AdMob {
    public  static  final String TAG = "EasyAds:AdMob";
    public static final int ANDROID_BUILD_VERSION = android.os.Build.VERSION.SDK_INT;
    private PopupWindow adPopupWindow;
    private AdView adView;
    private boolean adInit = false;
    private LinearLayout adLayout;
    private int adGravity = Gravity.TOP;
    private Activity _activity;

    private LinearLayout activityLayout;
    private boolean mInitlizedAdunit = false;

    /** true when the application has requested that an ad be displayed */
    private boolean adWantsToBeShown = false;

    /** true when an ad is available to be displayed */
    private boolean adIsAvailable = false;

    /** true when an ad request is in flight */
    private boolean adIsRequested = false;

    private InterstitialAd mInterstitialAd;
    private  boolean mInterstitialLoaded = false;

    private RewardedVideoAd mRewardAd;
    private boolean mRewardedVideoLoaded = false;

    private  String mAppId;
    private  String mBannerUnit;
    private  String mInterstitialUnit;
    private  String mRewardedUnit;

	private String mSharedAppId = "ca-app-pub-7921597124175429~5864144593";
	private String mSharedBannerUnit = "ca-app-pub-7921597124175429/7340877793";
	private String mSharedInterstitialUnit = "ca-app-pub-7921597124175429/1970924970";
	private String mSharedRewardedUnit = "ca-app-pub-7921597124175429/8153189945";

    private  boolean mIsForUnity;
    public static final String mUnityAdsObjectName = "EZAds";

    private Timer mCountdownTimer;
    private int mReloadTimer = 5000;
    private Random mRand = new Random(System.currentTimeMillis() );

    private boolean mIsConsentUpdated = false;
    private ConsentStatus mConsentStatus = ConsentStatus.UNKNOWN;
    private ConsentForm mConsentForm;

    public static final int INVALID = 0;
    public static final int UNKNOWN = 1;
    public static final int NON_PERSONALIZED = 2;
    public static final int PERSONALIZED = 3;


    class CustomInterstitial{
        public String strAdUnit;
        public InterstitialAd interstitialAd;
    };

    class CustomRewardedVideo{
        public String strAdUnit;
        public RewardedAd rewardedVideoAd;
    };

    private ConcurrentHashMap<String, CustomInterstitial> mCustomInterstitial = new ConcurrentHashMap<>();
    private ConcurrentHashMap<String, CustomRewardedVideo> mCustomRewardedVideo = new ConcurrentHashMap<>();

    public AdMob(Activity activity, LinearLayout mainLayout, boolean isForUnity)
    {
        _activity = activity;
        activityLayout = mainLayout;
        mIsForUnity = isForUnity;

        Log.d(TAG, "Admob:Init");
    }

    public boolean IsBannerReady()
    {
        return adIsAvailable;
    }

    public  boolean IsInterstitialReady()
    {
        return mInterstitialLoaded;
    }

    public  boolean IsRewardedVideoReady()
    {
        return mRewardedVideoLoaded;
    }

    public void InitAdMob(String AppId, String adBannerUnit, String interstitialUnit, String rewardUnit, final List<String> testDeviceIds)
    {
        mAppId = AppId;
        mBannerUnit = adBannerUnit;
        mInterstitialUnit = interstitialUnit;
        mRewardedUnit = rewardUnit;
		

        MobileAds.initialize(_activity, new OnInitializationCompleteListener() {
            @Override
            public void onInitializationComplete(InitializationStatus initializationStatus) {
                int readyAdNetwotk = 0;
                Map<String, AdapterStatus> statusMap = initializationStatus.getAdapterStatusMap();
                for (Map.Entry<String, AdapterStatus> entry : statusMap.entrySet()) {
                    Log.d(TAG, "Init Mediation Status:" + entry.getKey() + " satus:" + entry.getValue().getInitializationState() );
                    if(entry.getValue().getInitializationState() == AdapterStatus.State.READY){
                        readyAdNetwotk++;
                    }
                }
                MobileAds.setRequestConfiguration(
                        new RequestConfiguration.Builder().setTestDeviceIds(testDeviceIds)
                                .build());

                if( (readyAdNetwotk > 0) && (readyAdNetwotk == statusMap.size() ) && !mInitlizedAdunit){
                    mInitlizedAdunit = true;
                    Log.d(TAG, "Init Mediation Status all mediation adapter init success!!!");
                    initAllAdunits();
                }

                if(mCountdownTimer == null){
                    mCountdownTimer = new Timer();
                    mCountdownTimer.scheduleAtFixedRate(new TimerTask() {
                        @Override
                        public void run() {
                            if(mInitlizedAdunit){
                                mCountdownTimer.cancel();
                                return;
                            }

                            _activity.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    if(!mInitlizedAdunit){
                                        mInitlizedAdunit = true;
                                        Log.d(TAG, "Init Mediation Status: TimeOut Start init add ad units!!!");
                                        initAllAdunits();
                                    }
                                }
                            });
                        }
                    }, 10000, 5000);
                }
            }
        });
    }

    public void requestConsentInfoUpdate(String PublisherId){
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ConsentInformation consentInformation = ConsentInformation.getInstance(_activity);
                String[] publisherIds = {PublisherId};
                consentInformation.requestConsentInfoUpdate(publisherIds, new ConsentInfoUpdateListener() {
                    @Override
                    public void onConsentInfoUpdated(ConsentStatus consentStatus) {
                        // User's consent status successfully updated.
                        Log.d(TAG, "onConsentInfoUpdated:" + consentStatus);
                        mIsConsentUpdated = true;
                        mConsentStatus = consentStatus;
                        int status = 0;
                        if(mConsentStatus == ConsentStatus.UNKNOWN){
                            status = 1;
                        } else if(mConsentStatus == ConsentStatus.NON_PERSONALIZED){
                            status = 2;
                        } else if(mConsentStatus == ConsentStatus.PERSONALIZED){
                            status = 3;
                        }
                        nativeOnConsentInfoUpdated(PublisherId,true, status);
                    }

                    @Override
                    public void onFailedToUpdateConsentInfo(String errorDescription) {
                        // User's consent status failed to update.
                        Log.d(TAG, "onFailedToUpdateConsentInfo:" + errorDescription);
                        nativeOnConsentInfoUpdated(PublisherId,false, 0);
                    }
                });
            }
        });
    }

    public void requestUserConfirmConsent(final String strPrivacyUrl, boolean withAdFree){
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                URL privacyUrl = null;
                try {
                    privacyUrl = new URL(strPrivacyUrl);
                } catch (MalformedURLException e) {
                    e.printStackTrace();
                    Log.d(TAG, "create privacy url fail:" + strPrivacyUrl);
                    return;
                }
                ConsentForm.Builder builder = new ConsentForm.Builder(_activity, privacyUrl)
                .withListener(new ConsentFormListener() {
                    @Override
                    public void onConsentFormLoaded() {
                        Log.d(TAG, "onConsentFormLoaded");
                        mConsentForm.show();
                    }

                    @Override
                    public void onConsentFormOpened() {
                        Log.d(TAG, "onConsentFormOpened");
                    }

                    @Override
                    public void onConsentFormClosed(
                            ConsentStatus consentStatus, Boolean userPrefersAdFree) {
                        Log.d(TAG, "onConsentFormClosed result:" + consentStatus);
                        nativeOnUserConfirmConsent(ConvertConsentStatusToInt(consentStatus), userPrefersAdFree);
                    }

                    @Override
                    public void onConsentFormError(String errorDescription) {
                        Log.d(TAG, "onConsentFormError:" + errorDescription);
                    }
                })
                .withPersonalizedAdsOption()
                .withNonPersonalizedAdsOption();

                if(withAdFree){
                    mConsentForm = builder.withAdFreeOption().build();
                } else {
                    mConsentForm = builder.build();
                }
                mConsentForm.load();
            }
        });
    }

    private int ConvertConsentStatusToInt(ConsentStatus status){
        if(status == ConsentStatus.UNKNOWN){
            return UNKNOWN;
        } else if(status == ConsentStatus.NON_PERSONALIZED){
            return NON_PERSONALIZED;
        } else if(status == ConsentStatus.PERSONALIZED){
            return PERSONALIZED;
        }
        return INVALID;
    }

    public int getConsentStatus(){
        FutureTask<Integer> futureResult = new FutureTask<Integer>(new Callable<Integer>() {
            @Override
            public Integer call() throws Exception {
                if(!mIsConsentUpdated){
                    return INVALID;
                }

                return ConvertConsentStatusToInt(mConsentStatus);
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            int ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return PERSONALIZED;
        }
        catch (ExecutionException e){
            return PERSONALIZED;
        }
    }

    public boolean setConsentStatus(int status){
        FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
            @Override
            public Boolean call() throws Exception {
                if(!mIsConsentUpdated) {
                    return false;
                }
                //mConsentStatus = status;
                if(status == INVALID){
                    return false;
                } else if(status == UNKNOWN){
                    mConsentStatus = ConsentStatus.UNKNOWN;
                } else if(status == NON_PERSONALIZED){
                    mConsentStatus = ConsentStatus.NON_PERSONALIZED;
                } else if(status == PERSONALIZED){
                    mConsentStatus = ConsentStatus.PERSONALIZED;
                } else {
                    return false;
                }
                ConsentInformation.getInstance(_activity).setConsentStatus(mConsentStatus);
                Log.d(TAG, "Set Consent status:" + mConsentStatus);
                return true;
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            boolean ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return false;
        }
        catch (ExecutionException e){
            return false;
        }
    }

    public boolean isLocationInEEA(){
        FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
            @Override
            public Boolean call() throws Exception {
                return ConsentInformation.getInstance(_activity).isRequestLocationInEeaOrUnknown();
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            boolean ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return false;
        }
        catch (ExecutionException e){
            return false;
        }
    }

    public boolean useNonPersonalizedAds(){
        FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
            @Override
            public Boolean call() throws Exception {
                if(mIsConsentUpdated && isLocationInEEA() ){

                    if(ConsentInformation.getInstance(_activity).isTaggedForUnderAgeOfConsent() ){
                        return true;
                    }

                    if(mConsentStatus == ConsentStatus.NON_PERSONALIZED){
                        return true;
                    }
                }
                return false;
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            boolean ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return false;
        }
        catch (ExecutionException e){
            return false;
        }
    }

    public boolean setTagForUnderAgeOfConsent(boolean underAgeOfConsent){
        FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
            @Override
            public Boolean call() throws Exception {
                if(!mIsConsentUpdated){
                    return false;
                }
                ConsentInformation.getInstance(_activity).setTagForUnderAgeOfConsent(underAgeOfConsent);
                return true;
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            boolean ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return false;
        }
        catch (ExecutionException e){
            return false;
        }
    }

    public void initAllAdunits(){
        if(mBannerUnit != null && mBannerUnit.length() > 1)
        {
            InitBanner();
        }

        if(mInterstitialUnit != null && mInterstitialUnit.length() > 1)
        {
            InitInterstitialAd();
        }

        if(mRewardedUnit != null && mRewardedUnit.length() > 1)
        {
            InitRewardAds();
        }
    }



    private void reloadRewardedVideo(){
		if(mRewardAd.isLoaded() ){
            mRewardedVideoLoaded = true;
            return;
        }
		
        mRewardedVideoLoaded = false;
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                _activity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Bundle extras = new Bundle();
                        if(useNonPersonalizedAds() ) {
                            extras.putString("npa", "1");
                        }
                        mRewardAd.loadAd(mRewardedUnit, new AdRequest.Builder()
                                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                                .build() );
                    }
                });
            }
        }, mReloadTimer);
    }

    public  void InitRewardAds()
    {
        final String strBackUnit = mRewardedUnit;
        mRewardAd = MobileAds.getRewardedVideoAdInstance(_activity);

        Log.d(TAG, "AdMob:play rewardedvideo In UI");

        Bundle extras = new Bundle();
        if(useNonPersonalizedAds() ) {
            extras.putString("npa", "1");
        }

        mRewardAd.loadAd(strBackUnit, new AdRequest.Builder()
                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                .build() );

        mRewardAd.setRewardedVideoAdListener(new RewardedVideoAdListener() {
            @Override
            public void onRewardedVideoAdLoaded() {
                Log.d(TAG, "AdMob:ReeardedVideo Loaded Success");
                mRewardedVideoLoaded = true;
                nativeDebugMessage("AdMob:ReeardedVideo Loaded Success");
            }

            @Override
            public void onRewardedVideoAdOpened() {

            }

            @Override
            public void onRewardedVideoStarted() {

            }

            @Override
            public void onRewardedVideoAdClosed() {
                Log.d(TAG, "AdMob:Request Load when closed");
                reloadRewardedVideo();

                if(mIsForUnity)
                {
                    //UnityPlayer.UnitySendMessage(mUnityAdsObjectName, "OnRewardedVideoClosed", "Admob");
                }
                else
                {
                    nativePlayRewardedClose();
                }
            }

            @Override
            public void onRewarded(RewardItem rewardItem) {
                Log.d(TAG, "AdMob:ReeardedVideo Rewarded");

                if(mIsForUnity)
                {
                    //UnityPlayer.UnitySendMessage(mUnityAdsObjectName, "OnRewardedVideoFinish", "Admob," + rewardItem.getType() + "," + rewardItem.getAmount() );
                }
                else
                {
                    nativePlayRewardedComplete(rewardItem.getType(), rewardItem.getAmount() );
                }
            }

            @Override
            public void onRewardedVideoAdLeftApplication() {

            }

            @Override
            public  void onRewardedVideoCompleted(){}

            @Override
            public void onRewardedVideoAdFailedToLoad(int i) {

                Log.d(TAG, "AdMob:ReeardedVideo Fail Loads:" + i);
                nativeDebugMessage("AdMob:ReeardedVideo Fail Loads:" + i);

                reloadRewardedVideo();
            }});
    }

    public void LoadCustomRewardedVideoImp(final String adUnit){
        if(mCustomRewardedVideo.containsKey(adUnit) ){
            mCustomRewardedVideo.remove(adUnit);
        }

        CustomRewardedVideo newRewardedVideo = new CustomRewardedVideo();
        newRewardedVideo.strAdUnit = adUnit;
        newRewardedVideo.rewardedVideoAd = new RewardedAd(_activity, adUnit);
        mCustomRewardedVideo.put(adUnit, newRewardedVideo);

        Bundle extras = new Bundle();
        if(useNonPersonalizedAds() ) {
            extras.putString("npa", "1");
        }

        newRewardedVideo.rewardedVideoAd.loadAd(new AdRequest.Builder()
                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                .build(), new RewardedAdLoadCallback(){
            @Override
            public void onRewardedAdLoaded() {
                nativeCustomRewardedVideoLoadSuccess(adUnit);
                nativeDebugMessage("Custom load RewardedVideo Success:"+adUnit);
            }

            @Override
            public void onRewardedAdFailedToLoad(int errorCode) {
                nativeCustomRewardedVideoLoadFail(adUnit, "Custom Rewardvideo load fail:" + adUnit + " error code:" + errorCode);
                nativeDebugMessage("Custom Rewardvideo load fail:" + adUnit + " error code:" + errorCode);
            }
        });
    }

    public void LoadCustomRewardedVideo(final String adUnit){
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                LoadCustomRewardedVideoImp(adUnit);
            }
        });
    }

    public boolean IsCustomRewardedVideoLoaded(final String adUnit){

        FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
            @Override
            public Boolean call() throws Exception {
                if(!mCustomRewardedVideo.containsKey(adUnit)){
                    return false;
                }
                return mCustomRewardedVideo.get(adUnit).rewardedVideoAd.isLoaded();
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            boolean ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return false;
        }
        catch (ExecutionException e){
            return false;
        }
    }

    public void PlayCustomRewardedVideo(final String adUnit){
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(!mCustomRewardedVideo.containsKey(adUnit) ){
                    return;
                }

                mCustomRewardedVideo.get(adUnit).rewardedVideoAd.show(_activity, new RewardedAdCallback(){
                    public void onRewardedAdOpened() {
                        // Ad opened.
                    }

                    public void onRewardedAdClosed() {
                        // Ad closed.
                        nativeCustomPlayRewardedVideoClose(adUnit);
                        nativeDebugMessage("Custom RewardedVideo Closed:" + adUnit);
                    }

                    public void onUserEarnedReward(@NonNull com.google.android.gms.ads.rewarded.RewardItem var1){
                        nativeCustomPlayRewardedVideoComplete(adUnit, var1.getType(), var1.getAmount() );
                        nativeDebugMessage("Custom RewardedVideo Get Rewarded:" + adUnit + " type:" + var1.getType() + " amount:" + var1.getAmount() );
                    }

                    public void onRewardedAdFailedToShow(int errorCode) {
                        nativeCustomPlayRewardedVideoFail(adUnit, "Custom RewardedVideo Play Fail:" + errorCode);
                        nativeDebugMessage("Custom RewardedVideo Play Fail:" + adUnit + " error code:" + errorCode);
                    }
                });
            }
        });
    }

    public void playRewardAds()
    {
        if(mRewardAd == null)
        {
            return;
        }

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(mRewardAd.isLoaded())
                {
                    Log.d(TAG, "AdMob:play rewardedvideo");
                    mRewardAd.show();
                }
            }
        });
    }

    public  void OnPause()
    {
        if(mRewardAd != null)
        {
            mRewardAd.pause(_activity);
        }
    }

    public  void OnResume()
    {
        if(mRewardAd != null)
        {
            mRewardAd.resume(_activity);
        }
    }

    public  void OnDestroy()
    {
        if(mRewardAd != null)
        {
            mRewardAd.destroy(_activity);
        }
    }

    private void updateAdVisibility(boolean loadIfNeeded)
    {
        if (!adInit || (adPopupWindow == null))
        {
            return;
        }

        // request an ad if we don't have one available or requested, but would like one
        if (adWantsToBeShown && !adIsAvailable && !adIsRequested && loadIfNeeded)
        {
            Bundle extras = new Bundle();
            if(useNonPersonalizedAds() ) {
                extras.putString("npa", "1");
            }

            AdRequest adRequest = new AdRequest.Builder()
                    .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                    .build();		// add test devices here
            adView.loadAd(adRequest);

            adIsRequested = true;
        }

        if (adIsAvailable && adWantsToBeShown)
        {
            if (adPopupWindow.isShowing())
            {
                return;
            }

            adPopupWindow.showAtLocation(activityLayout, adGravity, 0, 0);
            // don't call update on 7.0 to work around this issue: https://code.google.com/p/android/issues/detail?id=221001
            if (ANDROID_BUILD_VERSION != 24)
            {
                adPopupWindow.update();
            }
        }
        else
        {
            if (!adPopupWindow.isShowing())
            {
                return;
            }

            adPopupWindow.dismiss();
            adPopupWindow.update();
        }
    }

    public void HideAdBanner()
    {
        Log.d(TAG, "In AndroidThunkJava_HideAdBanner");

        if (!adInit)
        {
            return;
        }

        _activity.runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                adWantsToBeShown = false;
                updateAdVisibility(true);
            }
        });
    }

    private void reloadInterstitial(){
		if(mInterstitialAd.isLoaded()){
            mInterstitialLoaded = true;
            return;
        }
		
        mInterstitialLoaded = false;
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                _activity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Bundle extras = new Bundle();
                        if(useNonPersonalizedAds() ) {
                            extras.putString("npa", "1");
                        }

                        mInterstitialAd.loadAd(new AdRequest.Builder()
                                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                                .build());
                    }
                });
            }
        }, mReloadTimer);
    }

    public void InitInterstitialAd()
    {
        mInterstitialAd = new InterstitialAd(_activity);
        mInterstitialAd.setAdUnitId(mInterstitialUnit);

        Bundle extras = new Bundle();
        if(useNonPersonalizedAds() ) {
            extras.putString("npa", "1");
        }

        mInterstitialAd.loadAd(new AdRequest.Builder()
                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                .build());

        mInterstitialAd.setAdListener(new AdListener() {
            @Override
            public void onAdClosed() {
                if(mIsForUnity)
                {
                    //UnityPlayer.UnitySendMessage(mUnityAdsObjectName, "OnInterstitialClose", "Admob");
                }
                else
                {
                    nativeInterstitialClose();
                }
                // Load the next interstitial.
                reloadInterstitial();
            }

            @Override
            public void onAdFailedToLoad(int var1) {
                Log.d(TAG, "AdMob:Interstitial Ads Loaded Fail:" + var1);
                nativeDebugMessage("AdMob:Interstitial Ads Loaded Fail:" + var1);
                reloadInterstitial();
            }

            @Override
            public void onAdOpened() {
                if(mIsForUnity)
                {
                    //UnityPlayer.UnitySendMessage(mUnityAdsObjectName, "OnInterstitialShow", "Admob");
                }
                else
                {
                    nativeInterstitialShow();
                }
            }

            @Override
            public void onAdClicked(){
                if(mIsForUnity)
                {
                    //UnityPlayer.UnitySendMessage(mUnityAdsObjectName, "OnInterstitialClicked", "Admob");
                }
                else
                {
                    nativeInterstitialClick();
                }
            }

            @Override
            public void onAdLoaded()
            {
                Log.d(TAG, "AdMob:Interstitial Ads Loaded Success");
                mInterstitialLoaded = true;
                nativeDebugMessage("AdMob:Interstitial Ads Loaded Success");
            }
        });
    }


    private void LoadCustomInterstitialImp(final String adUnit){
        if(mCustomInterstitial.containsKey(adUnit) ){
            mCustomInterstitial.get(adUnit).interstitialAd.setAdListener(null);
            mCustomInterstitial.remove(adUnit);
        }

        CustomInterstitial newInterstitial = new CustomInterstitial();
        newInterstitial.strAdUnit = adUnit;
        newInterstitial.interstitialAd = new InterstitialAd(_activity);
        newInterstitial.interstitialAd.setAdUnitId(adUnit);

        mCustomInterstitial.put(adUnit, newInterstitial);
        newInterstitial.interstitialAd.setAdListener(new AdListener(){
            @Override
            public void onAdClosed() {
                nativeCustomInterstitialClose(adUnit);
            }

            @Override
            public void onAdFailedToLoad(int var1){
                nativeCustomInterstitialLoadFail(adUnit, "custom interstitial load fail:" + adUnit+" error:" + var1);
                nativeDebugMessage("custom interstitial load fail:" + adUnit);
            }

            @Override
            public void onAdOpened() {
                nativeCustomInterstitialShow(adUnit);
            }

            @Override
            public void onAdClicked() {
                nativeCustomInterstitialClick(adUnit);
            }

            @Override
            public void onAdLoaded(){
                nativeCustomInterstitialLoadSuccess(adUnit);
                nativeDebugMessage("CustomInterstitial Ads Loaded Success:" + adUnit);
            }
        });
        Bundle extras = new Bundle();
        if(useNonPersonalizedAds() ) {
            extras.putString("npa", "1");
        }

        newInterstitial.interstitialAd.loadAd(new AdRequest.Builder()
                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                .build());
    }

    public void LoadCustomInterstitial(final String adUnit){
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                LoadCustomInterstitialImp(adUnit);
            }
        });
    }

    public boolean IsCustomInterstitialLoaded(final String adUnit){
        FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
            @Override
            public Boolean call() throws Exception {
                if(!mCustomInterstitial.containsKey(adUnit) ){
                    return false;
                }
                return mCustomInterstitial.get(adUnit).interstitialAd.isLoaded();
            }
        });

        _activity.runOnUiThread(futureResult);

        try{
            boolean ret = futureResult.get();
            return ret;
        }catch (InterruptedException e){
            return false;
        }
        catch (ExecutionException e){
            return false;
        }
    }

    public void ShowCustomInterstitialAd(final String adUnit){
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(!IsCustomInterstitialLoaded(adUnit) ){
                    nativeDebugMessage("Show Custom Interstitial Fail, ad not load:" + adUnit);
                    return;
                }
                mCustomInterstitial.get(adUnit).interstitialAd.show();
            }
        });
    }

    public  void ShowInterstitialAd()
    {
        Log.d(TAG, "Admob:ShowInterstitialAd AdUnit");

        if(mInterstitialAd != null) {
            _activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mInterstitialAd.isLoaded()) {
                        mInterstitialAd.show();
                        mInterstitialLoaded = false;
                    }
                }
            });
        }
    }

    private void reloadBanner(){
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                _activity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Bundle extras = new Bundle();
                        if(useNonPersonalizedAds() ) {
                            extras.putString("npa", "1");
                        }
                        AdRequest adRequest = new AdRequest.Builder()
                                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                                .build();		// add test devices here
                        adView.loadAd(adRequest);
                    }
                });
            }
        }, mReloadTimer);
    }

    public void InitBanner()
    {
        adView = new AdView(_activity);
        adView.setAdUnitId(mBannerUnit);
        adView.setAdSize(AdSize.BANNER);

        adInit = true;

        final DisplayMetrics dm = _activity.getResources().getDisplayMetrics();
        final float scale = dm.density;
        adPopupWindow = new PopupWindow(_activity);
        adPopupWindow.setWidth((int)(320*scale));
        adPopupWindow.setHeight((int)(50*scale));
        adPopupWindow.setWindowLayoutMode(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        adPopupWindow.setClippingEnabled(false);

        adLayout = new LinearLayout(_activity);

        final int padding = (int)(-5*scale);
        adLayout.setPadding(padding,padding,padding,padding);

        ViewGroup.MarginLayoutParams params = new ViewGroup.MarginLayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);;

        params.setMargins(0,0,0,0);

        adLayout.setOrientation(LinearLayout.VERTICAL);
        adLayout.addView(adView, params);
        adPopupWindow.setContentView(adLayout);

        Bundle extras = new Bundle();
        if(useNonPersonalizedAds() ) {
            extras.putString("npa", "1");
        }
        AdRequest adRequest = new AdRequest.Builder()
                .addNetworkExtrasBundle(AdMobAdapter.class, extras)
                .build();		// add test devices here
        adView.loadAd(adRequest);

        // set up our ad callbacks
        adView.setAdListener(new AdListener()
        {
            @Override
            public void onAdLoaded()
            {
                adIsAvailable = true;
                adIsRequested = false;
                Log.d(TAG, "AdMob:" + "AdMob Banner Loaded");
                updateAdVisibility(true);
                nativeDebugMessage("AdMob:AdMob Banner Loaded");
            }

            @Override
            public void onAdFailedToLoad(int errorCode)
            {
                adIsAvailable = false;
                adIsRequested = false;

                Log.d(TAG, "AdMob:" + "AdMob Banner Load Fail:" + errorCode);
                // don't immediately request a new ad on failure, wait until the next show
                updateAdVisibility(false);

                nativeDebugMessage("AdMob:AdMob Banner Load Fail:" + errorCode);

                reloadBanner();
            }
        });

        //adWantsToBeShown = true;
        updateAdVisibility(true);
    }

    public  void ShowBanner(boolean bShowOnBottonOfScreen)
    {
        adGravity = bShowOnBottonOfScreen ? Gravity.BOTTOM : Gravity.TOP;

        if (adInit)
        {
            // already created, make it visible
            _activity.runOnUiThread(new Runnable()
            {
                @Override
                public void run()
                {
                    if ((adPopupWindow == null) || adPopupWindow.isShowing())
                    {
                        return;
                    }

                    adWantsToBeShown = true;
                    updateAdVisibility(true);
                }
            });

            return;
        }
    }

    public native void nativeInterstitialClick();
    public native void nativeInterstitialShow();
    public native void nativeInterstitialClose();

    public native void nativePlayRewardedComplete(String strType, int amount);
    public native void nativePlayRewardedClose();
    public native void nativeDebugMessage(String debugMessage);

    public native void nativeCustomInterstitialLoadSuccess(String adUnit);
    public native void nativeCustomInterstitialLoadFail(String adUnit, String errmsg);

    public native void nativeCustomRewardedVideoLoadSuccess(String adUnit);
    public native void nativeCustomRewardedVideoLoadFail(String adUnit, String errmsg);

    public native void nativeCustomInterstitialClick(String adUnit);
    public native void nativeCustomInterstitialShow(String adUnit);
    public native void nativeCustomInterstitialClose(String adUnit);

    public native void nativeCustomPlayRewardedVideoComplete(String adUnit, String strType, int amount);
    public native void nativeCustomPlayRewardedVideoClose(String adUnit);
    public native void nativeCustomPlayRewardedVideoFail(String adUnit, String errmsg);

    public native void nativeOnConsentInfoUpdated(String publisherId, boolean success, int status);
    public native void nativeOnUserConfirmConsent(int status, boolean preferAdsFree);
}
