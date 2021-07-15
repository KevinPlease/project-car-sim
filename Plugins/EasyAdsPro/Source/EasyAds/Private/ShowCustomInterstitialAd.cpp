/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#include "ShowCustomInterstitialAd.h"

TMap<FString, UShowCustomInterstitialAd*> UShowCustomInterstitialAd::mLoadCustomInterstitialMap;

#if PLATFORM_ANDROID
void AndroidShowCustomInterstial(const FString& adUnit);
#endif

#if PLATFORM_IOS
extern "C" void IOS_ShowCustomInterstitialAd(FString adUnit);
#endif

UShowCustomInterstitialAd::UShowCustomInterstitialAd()
{

}

UShowCustomInterstitialAd::~UShowCustomInterstitialAd()
{
	mLoadCustomInterstitialMap.Remove(mAdUnit);
}

UShowCustomInterstitialAd* UShowCustomInterstitialAd::ShowCustomInterstitialAd(const FString& adUnit)
{
	UShowCustomInterstitialAd* ret = NewObject<UShowCustomInterstitialAd>();
	ret->mAdUnit = adUnit;

	mLoadCustomInterstitialMap.Remove(adUnit);
	mLoadCustomInterstitialMap.Add(adUnit, ret);
	
	return ret;
}

void UShowCustomInterstitialAd::Activate()
{
#if PLATFORM_ANDROID
	AndroidShowCustomInterstial(mAdUnit);
#endif

#if PLATFORM_IOS
	IOS_ShowCustomInterstitialAd(mAdUnit);
#endif
}

void UShowCustomInterstitialAd::OnClickCallback(const FString& adUnit)
{
	if (!mLoadCustomInterstitialMap.Contains(adUnit))
	{
		return;
	}

	mLoadCustomInterstitialMap[adUnit]->OnClick.Broadcast();
}

void UShowCustomInterstitialAd::OnShowCallback(const FString& adUnit)
{
	if (!mLoadCustomInterstitialMap.Contains(adUnit))
	{
		return;
	}

	mLoadCustomInterstitialMap[adUnit]->OnShow.Broadcast();
}

void UShowCustomInterstitialAd::OnCloseCallback(const FString& adUnit)
{
	if (!mLoadCustomInterstitialMap.Contains(adUnit))
	{
		return;
	}

	mLoadCustomInterstitialMap[adUnit]->OnClose.Broadcast();
}