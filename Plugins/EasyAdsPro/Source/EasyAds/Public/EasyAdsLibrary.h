/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasyAdsLibrary.generated.h"


UENUM(BlueprintType)
enum class ConsentStatus :uint8
{
	INVALID = 0 UMETA(DisplayName = "INVALID"),

	UNKNOWN = 1 UMETA(DisplayName = "UNKNOWN"),

	NON_PERSONALIZED = 2 UMETA(DisplayName = "NON_PERSONALIZED"),

	PERSONALIZED = 3 UMETA(DisplayName = "PERSONALIZED"),
};


/**
 * 
 */
UCLASS()
class EASYADS_API UEasyAdsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	/**
	* Show  banner
	* @param	isOnBottom		if the banner show on the bottom of the screen
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowBanner", Keywords = "EasyAds Show Banner"), Category = "EasyAds")
		static void ShowBanner(bool isOnBottom);

	/**
	* hide  banner
	* @param	adType			the  ads type
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HideBanner", Keywords = "EasyAds Hide Banner"), Category = "EasyAds")
		static void HideBanner();

	/**
	* show interstitial ads
	* @param	adType			the  ads type
	*/
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowInterstitial", Keywords = "AdCollection Show Interstitial Ads"), Category = "AdCollection")
	//static void ShowInterstitial();

	/**
	* check is the banner is load finish
	* @param	adType			the  ads type
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsBannerAdsReady", Keywords = "EasyAds Check Banner Ads Ready"), Category = "EasyAds")
		static bool IsBannerReady();

	/**
	* check is the interstitial is load finish
	* @param	adType			the  ads type
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsInterstitialAdsReady", Keywords = "EasyAds Check Interstital Ads Ready"), Category = "EasyAds")
		static bool IsInterstitialReady();

	/**
	* check is the rewardedvideo ads load finish
	* @param	adType			the  ads type
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsRewardedVideoAdsReady", Keywords = "EasyAds Check RewardedVideo Ads Ready"), Category = "EasyAds")
		static bool IsRewardedVideoReady();


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LaunchMediationTestSuite", Keywords = "EasyAds Launch Mediation TestSuite"), Category = "EasyAds")
	static void LaunchMediationTestSuite();
	

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsCustomInterstitialAdsReady", Keywords = "EasyAds Check Custom Interstital Ads Ready"), Category = "EasyAds")
	static bool IsCustomInterstitialReady(const FString& adUnit);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsCustomRewardedVideoAdsReady", Keywords = "EasyAds Check Custom RewardedVideo Ads Ready"), Category = "EasyAds")
	static bool IsCustomRewardedVideoAdsReady(const FString& adUnit);
	

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetConsendStatus", Keywords = "EasyAds SetConsendStatus"), Category = "EasyAds|GDPR")
	static bool SetConsendStatus(ConsentStatus status);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsLocationInEEA", Keywords = "EasyAds check location is in eea"), Category = "EasyAds|GDPR")
	static bool IsLocationInEEA();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "setTagForUnderAgeOfConsent", Keywords = "EasyAds setTagForUnderAgeOfConsent"), Category = "EasyAds|GDPR")
	static bool SetTagForUnderAgeOfConsent(bool isUnderAgeOfConsent);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsUseNonPersonalizeAds", Keywords = "EasyAds check if use nonpersonalized ads"), Category = "EasyAds|GDPR")
	static bool IsUseNonPersonalizeAds();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetUnityConsentStatus", Keywords = "EasyAds GetUnityConsentStatus"), Category = "EasyAds")
	static ConsentStatus GetUnityConsentStatus();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetApplovinConsentStatus", Keywords = "EasyAds GetApplovinConsentStatus"), Category = "EasyAds")
	static ConsentStatus GetApplovinConsentStatus();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetVungleConsentStatus", Keywords = "EasyAds GetVungleConsentStatus"), Category = "EasyAds")
	static ConsentStatus GetVungleConsentStatus();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetChartboostConsentStatus", Keywords = "EasyAds GetChartboostConsentStatus"), Category = "EasyAds")
	static ConsentStatus GetChartboostConsentStatus();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsAdmobInitlized", Keywords = "EasyAds IsAdmobInitlize"), Category = "EasyAds")
	static bool IsAdmobInitlized();
};
