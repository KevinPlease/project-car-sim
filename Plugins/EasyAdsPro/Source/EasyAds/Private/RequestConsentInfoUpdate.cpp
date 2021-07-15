/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/


#include "RequestConsentInfoUpdate.h"

TMap<FString, URequestConsentInfoUpdate*> URequestConsentInfoUpdate::mRequuestConsentInfoMap;

#if PLATFORM_ANDROID
void AndroidRequestConsentInfoUpdate(const FString& publisherId);
#endif

#if PLATFORM_IOS
extern "C" void IOS_RequestConsentInfoUpdate(const FString& publisherId);
#endif

URequestConsentInfoUpdate::URequestConsentInfoUpdate()
{

}

URequestConsentInfoUpdate::~URequestConsentInfoUpdate()
{
	mRequuestConsentInfoMap.Remove(mPublisherId);
}

URequestConsentInfoUpdate* URequestConsentInfoUpdate::RequestConsentInfoUpdate(const FString& publisherId)
{
	URequestConsentInfoUpdate* pRet = NewObject<URequestConsentInfoUpdate>();
	pRet->mPublisherId = publisherId;

	mRequuestConsentInfoMap.Remove(publisherId);
	mRequuestConsentInfoMap.Add(publisherId, pRet);

	return pRet;
}

void URequestConsentInfoUpdate::Activate()
{
#if PLATFORM_ANDROID
	AndroidRequestConsentInfoUpdate(mPublisherId);
#endif

#if PLATFORM_IOS
	IOS_RequestConsentInfoUpdate(mPublisherId);
#endif
}

void URequestConsentInfoUpdate::OnConsentUpdateCallback(const FString& publisherId, bool isSuccess, int status)
{
	if (!mRequuestConsentInfoMap.Contains(publisherId))
	{
		return;
	}
	
	ConsentStatus eStatus = ConsentStatus::INVALID;
	if (status == (int)ConsentStatus::NON_PERSONALIZED)
	{
		eStatus = ConsentStatus::NON_PERSONALIZED;
	}
	else if (status == (int)ConsentStatus::UNKNOWN)
	{
		eStatus = ConsentStatus::UNKNOWN;
	}
	else if (status == (int)ConsentStatus::PERSONALIZED)
	{
		eStatus = ConsentStatus::PERSONALIZED;
	}

	mRequuestConsentInfoMap[publisherId]->OnConsentUpdate.Broadcast(isSuccess, eStatus);
	mRequuestConsentInfoMap.Remove(publisherId);
}