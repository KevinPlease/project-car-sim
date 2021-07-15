/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/


#include "RequestUserConfirmConsent.h"

TSet<URequestUserConfirmConsent*> URequestUserConfirmConsent::mRequestList;

#if PLATFORM_ANDROID
void AndroidReqUserConfirmConsent(const FString& privacyUrl, bool withAdFreeOption);
#endif

#if PLATFORM_IOS
extern "C" void IOS_RequestUserConfirmConsent(const FString& privacyUrl, bool withAdFreeOption);
#endif

URequestUserConfirmConsent::URequestUserConfirmConsent()
{

}

URequestUserConfirmConsent::~URequestUserConfirmConsent()
{
	mRequestList.Remove(this);
}

URequestUserConfirmConsent* URequestUserConfirmConsent::RequestUserConfirmConsent(const FString& privacyUrl, bool withAdFreeOption)
{
	URequestUserConfirmConsent* pRet = NewObject<URequestUserConfirmConsent>();
	pRet->mPrivacyUrl = privacyUrl;
	pRet->mWithAdFreeOption = withAdFreeOption;
	
	mRequestList.Add(pRet);

	return pRet;
}

void URequestUserConfirmConsent::Activate()
{
#if PLATFORM_ANDROID
	AndroidReqUserConfirmConsent(mPrivacyUrl, mWithAdFreeOption);
#endif

#if PLATFORM_IOS
	IOS_RequestUserConfirmConsent(mPrivacyUrl, mWithAdFreeOption);
#endif
}

void URequestUserConfirmConsent::OnUserConfirmConsent(int status, bool preferAdFree)
{
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

	for (auto it = mRequestList.CreateIterator(); it; ++it)
	{
		URequestUserConfirmConsent* pObj = *it;
		pObj->OnConfirmDelegate.Broadcast(eStatus, preferAdFree);
	}
	mRequestList.Reset();
}