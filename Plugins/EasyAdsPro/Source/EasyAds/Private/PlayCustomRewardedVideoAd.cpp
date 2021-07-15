/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#include "PlayCustomRewardedVideoAd.h"

TMap<FString, UPlayCustomRewardedVideoAd*> UPlayCustomRewardedVideoAd::mPlayCustomRewardedVideoMap;

#if PLATFORM_ANDROID
void AndroidPlayCustomRewardedVideo(const FString& adUnit);
#endif

#if PLATFORM_IOS
extern "C" void IOS_PlayCustomRewardedVideoAd(FString adUnit);
#endif

UPlayCustomRewardedVideoAd::UPlayCustomRewardedVideoAd()
{

}

UPlayCustomRewardedVideoAd::~UPlayCustomRewardedVideoAd()
{
	mPlayCustomRewardedVideoMap.Remove(mAdUnit);
}

UPlayCustomRewardedVideoAd* UPlayCustomRewardedVideoAd::PlayCustomRewardedVideoAd(const FString& adUnit)
{
	UPlayCustomRewardedVideoAd* ret = NewObject<UPlayCustomRewardedVideoAd>();
	ret->mAdUnit = adUnit;

	mPlayCustomRewardedVideoMap.Remove(adUnit);
	mPlayCustomRewardedVideoMap.Add(adUnit, ret);

	return ret;
}

void UPlayCustomRewardedVideoAd::Activate()
{
#if PLATFORM_ANDROID
	AndroidPlayCustomRewardedVideo(mAdUnit);
#endif

#if PLATFORM_IOS
	IOS_PlayCustomRewardedVideoAd(mAdUnit);
#endif
}

void UPlayCustomRewardedVideoAd::OnEarnCallback(const FString& adUnit, const FString& rewardedType, int32 amount)
{
	if (!mPlayCustomRewardedVideoMap.Contains(adUnit))
	{
		return;
	}

	mPlayCustomRewardedVideoMap[adUnit]->OnComplete.Broadcast(rewardedType, amount);
}

void UPlayCustomRewardedVideoAd::OnFailCallback(const FString& adUnit, const FString& errmsg)
{
	if (!mPlayCustomRewardedVideoMap.Contains(adUnit))
	{
		return;
	}

	mPlayCustomRewardedVideoMap[adUnit]->OnFail.Broadcast(errmsg);
}

void UPlayCustomRewardedVideoAd::OnCloseCallback(const FString& adUnit)
{
	if (!mPlayCustomRewardedVideoMap.Contains(adUnit))
	{
		return;
	}

	mPlayCustomRewardedVideoMap[adUnit]->OnClose.Broadcast();
}