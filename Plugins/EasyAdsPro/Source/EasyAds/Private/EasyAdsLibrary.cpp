/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/


#include "EasyAdsLibrary.h"
#include "EasyAds.h"
#include "AdmobMediation.h"

#if PLATFORM_ANDROID
bool AndroidIsCustomInterstitialReady(const FString& adUnit);
bool AndroidIsCustomRewardedVideoReady(const FString& adUnit);
int AndroidGetConsentStatus();
bool AndroidSetConsentStatus(int status);
bool AndroidIsLocationInEEA();
bool AndroidSetTagUnderAgeOfConsent(bool isUnderAgeOfConsent);
bool AndroidIsUseNonPersonalizeAds();

void AndroidSetApplovinConsentStatus(int status);
void AndroidSetUnityConsentStatus(int status);
void AndroidSetVungleConsentStatus(int status);
void AndroidSetChartboostConsentStatus(int status);
void AndroidSetFacebookConsentStatus(int status);

int AndroidGetApplovinConsentStatus();
int AndroidGetUnityConsentStatus();
int AndroidGetVungleConsentStatus();
int AndroidGetChartboostConsentStatus();
int AndroidGetFacebookConsentStatus();
#endif

#if PLATFORM_IOS
extern "C" bool IOS_IsCustomInterstitialReady(FString adUnit);
extern "C" bool IOS_IsCustomRewardedVideoReady(FString adUnit);

extern "C" int IOS_GetConsentStatus();
extern "C" void IOS_SetConsentStatus(int status);
extern "C" bool IOS_IsLocationInEEA();
extern "C" bool IOS_IsUseNonPersonalizeAds();
extern "C" void IOS_SetTagForUnderAgeOfConsent(bool v);

extern "C" void IOS_SetUnityConsentStatus(int status);
extern "C" void IOS_SetVungleConsentStatus(int status);
extern "C" void IOS_SetChartboostConsentStatus(int status);
extern "C" void IOS_SetApplovinConsentStatus(int status);
extern "C" bool IOS_IsAdmobInitlized();

#endif


void UEasyAdsLibrary::ShowBanner(bool isOnBottom)
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	mediation.ShowBanner(isOnBottom);
}


void UEasyAdsLibrary::HideBanner()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	mediation.HideBanner();
}

bool UEasyAdsLibrary::IsBannerReady()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return false;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	return mediation.IsBannerReady();
}

bool UEasyAdsLibrary::IsInterstitialReady()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return false;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	return mediation.IsInterstitalReady();
}

bool UEasyAdsLibrary::IsCustomInterstitialReady(const FString& adUnit)
{
#if PLATFORM_ANDROID
	return AndroidIsCustomInterstitialReady(adUnit);
#endif

#if PLATFORM_IOS
	return IOS_IsCustomInterstitialReady(adUnit);
#endif

	return false;
}

bool UEasyAdsLibrary::IsCustomRewardedVideoAdsReady(const FString& adUnit)
{
#if PLATFORM_ANDROID
	return AndroidIsCustomRewardedVideoReady(adUnit);
#endif

#if PLATFORM_IOS
	return IOS_IsCustomRewardedVideoReady(adUnit);
#endif
	
	return false;
}

bool UEasyAdsLibrary::IsRewardedVideoReady()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return false;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	return mediation.IsRewardedVideoReady();
}

void UEasyAdsLibrary::LaunchMediationTestSuite()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	return mediation.LaunchTestSuite();
}


static ConsentStatus Int2ConsentStatus(int status)
{
	if (status == (int)ConsentStatus::UNKNOWN)
	{
		return ConsentStatus::UNKNOWN;
	}
	else if (status == (int)ConsentStatus::NON_PERSONALIZED)
	{
		return ConsentStatus::NON_PERSONALIZED;
	}
	else if (status == (int)ConsentStatus::PERSONALIZED)
	{
		return ConsentStatus::PERSONALIZED;
	}

	return ConsentStatus::INVALID;
}


bool UEasyAdsLibrary::IsAdmobInitlized()
{
#if PLATFORM_IOS
	return IOS_IsAdmobInitlized();
#endif
	
	return true;
}


bool UEasyAdsLibrary::SetConsendStatus(ConsentStatus status)
{
#if PLATFORM_ANDROID
	AndroidSetConsentStatus((int)status);
	AndroidSetApplovinConsentStatus((int)status);
	AndroidSetUnityConsentStatus((int)status);
	AndroidSetVungleConsentStatus((int)status);
	AndroidSetChartboostConsentStatus((int)status);
	AndroidSetFacebookConsentStatus((int)status);

	return true;
#endif

#if PLATFORM_IOS
	IOS_SetConsentStatus((int)status);
	IOS_SetUnityConsentStatus((int)status);
	IOS_SetVungleConsentStatus((int)status);
	IOS_SetChartboostConsentStatus((int)status);
	IOS_SetApplovinConsentStatus((int)status);
	return true;
#endif

	return false;
}


ConsentStatus UEasyAdsLibrary::GetUnityConsentStatus()
{
#if PLATFORM_ANDROID
	int status = AndroidGetUnityConsentStatus();
	return Int2ConsentStatus(status);
#endif

	return ConsentStatus::INVALID;
}


ConsentStatus UEasyAdsLibrary::GetApplovinConsentStatus()
{
#if PLATFORM_ANDROID
	int status = AndroidGetApplovinConsentStatus();
	return Int2ConsentStatus(status);
#endif

	return ConsentStatus::INVALID;
}


ConsentStatus UEasyAdsLibrary::GetVungleConsentStatus()
{
#if PLATFORM_ANDROID
	int status = AndroidGetVungleConsentStatus();
	return Int2ConsentStatus(status);
#endif

	return ConsentStatus::INVALID;
}


ConsentStatus UEasyAdsLibrary::GetChartboostConsentStatus()
{
#if PLATFORM_ANDROID
	int status = AndroidGetChartboostConsentStatus();
	return Int2ConsentStatus(status);
#endif

	return ConsentStatus::INVALID;
}


bool UEasyAdsLibrary::IsLocationInEEA()
{
#if PLATFORM_ANDROID
	return AndroidIsLocationInEEA();
#endif

#if PLATFORM_IOS
	return IOS_IsLocationInEEA();
#endif

	return false;
}


bool UEasyAdsLibrary::SetTagForUnderAgeOfConsent(bool isUnderAgeOfConsent)
{
#if PLATFORM_ANDROID
	return AndroidSetTagUnderAgeOfConsent(isUnderAgeOfConsent);
#endif


#if PLATFORM_IOS
	IOS_SetTagForUnderAgeOfConsent(isUnderAgeOfConsent);
	return true;
#endif

	return false;
}


bool UEasyAdsLibrary::IsUseNonPersonalizeAds()
{
#if PLATFORM_ANDROID
	return AndroidIsUseNonPersonalizeAds();
#endif

#if PLATFORM_IOS
	return IOS_IsUseNonPersonalizeAds();
#endif
	
	return false;
}