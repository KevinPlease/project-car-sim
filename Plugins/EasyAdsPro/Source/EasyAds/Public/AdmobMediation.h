/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEasyAdsDebugMessage, FString);
typedef FEasyAdsDebugMessage::FDelegate FEasyAdsDebugMessageDelegate;

DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayRewardComplete, FString, int32);
typedef FPlayRewardComplete::FDelegate FPlayRewardCompleteDelegate;

DECLARE_MULTICAST_DELEGATE(FInterstitialShow);
typedef FInterstitialShow::FDelegate FInterstitialShowDelegate;


DECLARE_MULTICAST_DELEGATE(FInterstitialClick);
typedef FInterstitialClick::FDelegate FInterstitialClickDelegate;


DECLARE_MULTICAST_DELEGATE(FInterstitialClosed);
typedef FInterstitialClosed::FDelegate FInterstitialClosedDelegate;


DECLARE_MULTICAST_DELEGATE(FPlayRewardClosed);
typedef FPlayRewardClosed::FDelegate FPlayRewardClosedDelegate;


#define DEFINE_ADS_DELEGATE_BASE(DelegateName) \
public: \
	F##DelegateName DelegateName##Delegates; \
public: \
	FDelegateHandle Add##DelegateName##Delegate_Handle(const F##DelegateName##Delegate& Delegate) \
	{ \
		DelegateName##Delegates.Add(Delegate); \
		return Delegate.GetHandle(); \
	} \
	void Clear##DelegateName##Delegate_Handle(FDelegateHandle& Handle) \
	{ \
		DelegateName##Delegates.Remove(Handle); \
		Handle.Reset(); \
	}\
	void ClearAll##DelegateName##Delegate_Handle() \
	{ \
		DelegateName##Delegates.Clear(); \
	}


#define DEFINE_ADS_DELEGATE(DelegateName) \
	DEFINE_ADS_DELEGATE_BASE(DelegateName) \
	void Trigger##DelegateName##Delegates() \
	{ \
		DelegateName##Delegates.Broadcast(); \
	}


#define DEFINE_ADS_DELEGATE_ONE_PARAM(DelegateName, Param1Type) \
	DEFINE_ADS_DELEGATE_BASE(DelegateName) \
	void Trigger##DelegateName##Delegates(Param1Type Param1) \
	{ \
		DelegateName##Delegates.Broadcast(Param1); \
	}

#define DEFINE_ADS_DELEGATE_TWO_PARAMS(DelegateName, Param1Type, Param2Type) \
	DEFINE_ADS_DELEGATE_BASE(DelegateName) \
	void Trigger##DelegateName##Delegates(Param1Type Param1, Param2Type Param2) \
	{ \
		DelegateName##Delegates.Broadcast(Param1, Param2); \
	}


/**
 * 
 */
class EASYADS_API AdmobMediation
{
public:
	AdmobMediation();
	~AdmobMediation();


	/**
	* show  banner
	* @param	isBottom  if the banner will show on the bottom
	*/
	void ShowBanner(bool isBottom);

	/**
	* hide  banner
	*/
	void HideBanner();

	
	/**
	* check if the banner is ready to show
	*/
	bool IsBannerReady();


	/**
	* show the interstitial ads
	*/
	void ShowInterstitial();

	
	/**
	* check if interstitial ads ready
	*/
	bool IsInterstitalReady();

	
	/**
	* show rewarded video ads
	*/
	void PlayRewardedVideo();

	/**
	* check if rewardedvideo ads ready
	*/
	bool IsRewardedVideoReady();

	
	/**
	* launch mediation test suite
	*/
	void LaunchTestSuite();


	/**
	* init function
	*/
	void init();


	DEFINE_ADS_DELEGATE(InterstitialShow);
	DEFINE_ADS_DELEGATE(InterstitialClick);
	DEFINE_ADS_DELEGATE(InterstitialClosed);
	DEFINE_ADS_DELEGATE(PlayRewardClosed);
	DEFINE_ADS_DELEGATE_TWO_PARAMS(PlayRewardComplete, FString, int32);
	DEFINE_ADS_DELEGATE_ONE_PARAM(EasyAdsDebugMessage, FString);
};
