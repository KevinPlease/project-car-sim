/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#include "AdmobMediation.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Async/TaskGraphInterfaces.h"
#include "EasyAds.h"
#include "LoadCustomInterstitialAd.h"
#include "ShowCustomInterstitialAd.h"
#include "LoadCustomRewardedVideoAd.h"
#include "PlayCustomRewardedVideoAd.h"
#include "RequestConsentInfoUpdate.h"
#include "RequestUserConfirmConsent.h"

DEFINE_LOG_CATEGORY_STATIC(EasyAds, Log, All);

AdmobMediation::AdmobMediation()
{
}

void AdmobMediation::init()
{

}

AdmobMediation::~AdmobMediation()
{
}


void AdmobMediation::ShowBanner(bool isBottom)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID ShowBannerMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_ShowBanner", "(Z)V", bIsOptional);
		if (ShowBannerMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_ShowBanner not found"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ShowBannerMethod, isBottom);
	}
}

void AndroidLoadCustomRewardedVideo(const FString& adUnit)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID LoadCustomRewardedVideoMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_LoadCustomRewardedVideo", "(Ljava/lang/String;)V", bIsOptional);
		if (LoadCustomRewardedVideoMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_LoadCustomRewardedVideo not found"));
			return;
		}
		auto adUnitJava = FJavaHelper::ToJavaString(Env, adUnit);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadCustomRewardedVideoMethod, *adUnitJava);
	}
}

void AndroidLoadCustomInterstial(const FString& adUnit)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID LoadCustomInterstitialMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_LoadCustomInterstitial", "(Ljava/lang/String;)V", bIsOptional);
		if (LoadCustomInterstitialMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_LoadCustomInterstitial not found"));
			return;
		}
		auto adUnitJava = FJavaHelper::ToJavaString(Env, adUnit);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadCustomInterstitialMethod, *adUnitJava);
	}
}

bool AndroidIsCustomInterstitialReady(const FString& adUnit)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID CustomInterstitialLoadCheckMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_CustomInterstitialReady", "(Ljava/lang/String;)Z", bIsOptional);
		if (CustomInterstitialLoadCheckMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_CustomInterstitialReady not found"));
			return false;
		}
		auto adUnitJava = FJavaHelper::ToJavaString(Env, adUnit);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, CustomInterstitialLoadCheckMethod, *adUnitJava);
	}

	return false;
}

bool AndroidIsCustomRewardedVideoReady(const FString& adUnit)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID CustomRewardedVideoLoadCheckMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_CustomRewardedVideoReady", "(Ljava/lang/String;)Z", bIsOptional);
		if (CustomRewardedVideoLoadCheckMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_CustomRewardedVideoReady not found"));
			return false;
		}
		auto adUnitJava = FJavaHelper::ToJavaString(Env, adUnit);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, CustomRewardedVideoLoadCheckMethod, *adUnitJava);
	}

	return false;
}


void AndroidReqUserConfirmConsent(const FString& privacyUrl, bool withAdFreeOption)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID ReqUserConfirmConsentMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Admob_RequestUserConfirmConsent", "(Ljava/lang/String;Z)V", bIsOptional);
		if (ReqUserConfirmConsentMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_Admob_RequestUserConfirmConsent not found"));
			return;
		}
		auto javePrivacyUrl = FJavaHelper::ToJavaString(Env, privacyUrl);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ReqUserConfirmConsentMethod, *javePrivacyUrl, withAdFreeOption);
	}
}


int AndroidGetConsentStatusImp(const FString& func)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		jmethodID GetConsentStatusMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, TCHAR_TO_UTF8(*func), "()I", bIsOptional);
		if (GetConsentStatusMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("%s not found"), *func);
			return 0;
		}

		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, GetConsentStatusMethod);
	}

	return 0;
}

int AndroidGetApplovinConsentStatus()
{
	return AndroidGetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_GetApplovinConsentStatus") );
}


int AndroidGetUnityConsentStatus()
{
	return AndroidGetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_GetUnityConsentStatus"));
}

int AndroidGetVungleConsentStatus()
{
	return AndroidGetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_GetVungleConsentStatus"));
}

int AndroidGetChartboostConsentStatus()
{
	return AndroidGetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_GetChartboostConsentStatus"));
}


int AndroidGetFacebookConsentStatus()
{
	return AndroidGetConsentStatusImp(TEXT("AndroidThunkJava_Admob_GetFacebookConsentStatus"));
}


void AndroidSetConsentStatusImp(const FString& func, int status)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		jmethodID SetConsentStatusMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, TCHAR_TO_UTF8(*func), "(I)V", bIsOptional);
		if (SetConsentStatusMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("%s not found"), *func);
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, SetConsentStatusMethod, (jint)status);
	}
}

void AndroidSetApplovinConsentStatus(int status)
{
	AndroidSetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_SetApplovinConsentStatus"), status);
}


void AndroidSetUnityConsentStatus(int status)
{
	AndroidSetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_SetUnityConsentStatus"), status);
}

void AndroidSetVungleConsentStatus(int status)
{
	AndroidSetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_SetVungleConsentStatus"), status);
}


void AndroidSetChartboostConsentStatus(int status)
{
	AndroidSetConsentStatusImp(TEXT("AndroidThunkJava_AdMob_SetChartboostConsentStatus"), status);
}

void AndroidSetFacebookConsentStatus(int status)
{
	AndroidSetConsentStatusImp(TEXT("AndroidThunkJava_Admob_SetFacebookConsentStatus"), status);
}

int AndroidGetConsentStatus()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID GetConsentStatusMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_GetConsentStatus", "()I", bIsOptional);
		if (GetConsentStatusMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_GetConsentStatus not found"));
			return 0;
		}
		
		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, GetConsentStatusMethod);
	}

	return 0;
}

bool AndroidSetConsentStatus(int status)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID SetConsentStatusMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_SetConsentStatus", "(I)Z", bIsOptional);
		if (SetConsentStatusMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_SetConsentStatus not found"));
			return false;
		}

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, SetConsentStatusMethod, (jint)status);
	}

	return false;
}

bool AndroidIsLocationInEEA()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID IsLocationEEAMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_IsLocationInEEA", "()Z", bIsOptional);
		if (IsLocationEEAMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_IsLocationInEEA not found"));
			return false;
		}

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, IsLocationEEAMethod);
	}

	return false;
}

bool AndroidSetTagUnderAgeOfConsent(bool isUnderAgeOfConsent)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID SetTagAgeOfConsentMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_SetTagUnderAgeOfConsent", "(Z)Z", bIsOptional);
		if (SetTagAgeOfConsentMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_SetTagUnderAgeOfConsent not found"));
			return false;
		}

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, SetTagAgeOfConsentMethod, isUnderAgeOfConsent);
	}

	return false;
}


bool AndroidIsUseNonPersonalizeAds()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID IsUsePersonalizedAdsMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_IsUseNonPersonalizedAds", "()Z", bIsOptional);
		if (IsUsePersonalizedAdsMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_IsUseNonPersonalizedAds not found"));
			return false;
		}

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, IsUsePersonalizedAdsMethod);
	}

	return false;
}

void AndroidRequestConsentInfoUpdate(const FString& publisherId)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID RequestConsentMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_RequestConsentInfoUpdate", "(Ljava/lang/String;)V", bIsOptional);
		if (RequestConsentMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_RequestConsentInfoUpdate not found"));
			return;
		}
		auto strPublisherId = FJavaHelper::ToJavaString(Env, publisherId);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, RequestConsentMethod, *strPublisherId);
	}
}


void AndroidPlayCustomRewardedVideo(const FString& adUnit)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID PlayCustomRewardedVideoMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_PlayCustomRewardedVideoAd", "(Ljava/lang/String;)V", bIsOptional);
		if (PlayCustomRewardedVideoMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_PlayCustomRewardedVideoAd not found"));
			return;
		}
		auto adUnitJava = FJavaHelper::ToJavaString(Env, adUnit);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, PlayCustomRewardedVideoMethod, *adUnitJava);
	}
}

void AndroidShowCustomInterstial(const FString& adUnit)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID ShowCustomInterstitialMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_ShowCustomInterstitialAd", "(Ljava/lang/String;)V", bIsOptional);
		if (ShowCustomInterstitialMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_ShowCustomInterstitialAd not found"));
			return;
		}
		auto adUnitJava = FJavaHelper::ToJavaString(Env, adUnit);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ShowCustomInterstitialMethod, *adUnitJava);
	}
}

void AdmobMediation::HideBanner()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID HideBannerMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_HideBanner", "()V", bIsOptional);

		if (HideBannerMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_HideBanner not found"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HideBannerMethod);
	}
}

bool AdmobMediation::IsBannerReady()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID JniMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_BannerReady", "()Z", bIsOptional);
		if (JniMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_BannerReady not found"));
			return false;
		}

		// Convert scope array into java fields
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, JniMethod);
	}

	return false;
}

void AdmobMediation::LaunchTestSuite()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID LaunchTestSuiteMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_LaunchTestSuite", "()V", bIsOptional);
		//CHECK_JNI_METHOD(ShowInterstitialMethod);
		if (LaunchTestSuiteMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_LaunchTestSuite not found, please first enable testuite, which require minSdkVersion 16"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LaunchTestSuiteMethod);
	}
}


void AdmobMediation::ShowInterstitial()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID ShowInterstitialMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_ShowInterstitialAd", "()V", bIsOptional);
		//CHECK_JNI_METHOD(ShowInterstitialMethod);
		if (ShowInterstitialMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_ShowInterstitialAd not found"));
			return;
		}

		// Convert scope array into java fields
		//jstring AdUnitIDArg = Env->NewStringUTF(TCHAR_TO_UTF8(*adUnit));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, ShowInterstitialMethod);
	}
}


bool AdmobMediation::IsInterstitalReady()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID JniMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_InterstitialReady", "()Z", bIsOptional);
		if (JniMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_InterstitialReady not found"));
			return false;
		}

		// Convert scope array into java fields
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, JniMethod);
	}

	return false;
}


void AdmobMediation::PlayRewardedVideo()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID PlayRewardVideoMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_PlayRewardedVideo", "()V", bIsOptional);
		//CHECK_JNI_METHOD(PlayRewardVideoMethod);

		if (PlayRewardVideoMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_PlayRewardedVideo not found"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, PlayRewardVideoMethod);
	}
}


bool AdmobMediation::IsRewardedVideoReady()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID JniMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AdMob_RewardedVideoReady", "()Z", bIsOptional);
		if (JniMethod == nullptr)
		{
			UE_LOG(EasyAds, Error, TEXT("AndroidThunkJava_AdMob_RewardedVideoReady not found"));
			return false;
		}

		// Convert scope array into java fields
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, JniMethod);
	}

	return false;
}

__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeInterstitialClick(JNIEnv* jenv, jobject thiz)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeInterstitialClick"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeInterstitialClick, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeInterstitialClick\n"));
				FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
				if (pModule == nullptr)
				{
					return;
				}

				AdmobMediation& mediation = pModule->GetAdmobMediation();
				mediation.TriggerInterstitialClickDelegates();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeInterstitialClick),
				nullptr,
				ENamedThreads::GameThread
				);
}

__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeInterstitialShow(JNIEnv* jenv, jobject thiz)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeInterstitialShow"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeInterstitialShow, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeInterstitialShow\n"));
				FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
				if (pModule == nullptr)
				{
					return;
				}

				AdmobMediation& mediation = pModule->GetAdmobMediation();
				mediation.TriggerInterstitialShowDelegates();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeInterstitialShow),
				nullptr,
				ENamedThreads::GameThread
				);
}

__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeInterstitialClose(JNIEnv* jenv, jobject thiz)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeInterstitialClose"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeInterstitialClose, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeInterstitialClose\n"));
				FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
				if (pModule == nullptr)
				{
					return;
				}

				AdmobMediation& mediation = pModule->GetAdmobMediation();
				mediation.TriggerInterstitialClosedDelegates();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeInterstitialClose),
				nullptr,
				ENamedThreads::GameThread
				);
}

__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativePlayRewardedClose(JNIEnv* jenv, jobject thiz)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativePlayRewardedClose"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativePlayRewardedClose, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativePlayRewardedClose\n"));
				FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
				if (pModule == nullptr)
				{
					return;
				}

				AdmobMediation& mediation = pModule->GetAdmobMediation();
				mediation.TriggerPlayRewardClosedDelegates();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativePlayRewardedClose),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativePlayRewardedComplete(JNIEnv* jenv, jobject thiz, jstring type, jint amount)
{
	FString strHoldType = FJavaHelper::FStringFromParam(jenv, type);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.nativePlayRewardedComplete"), STAT_FSimpleDelegateGraphTask_nativePlayRewardedComplete, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				//FModuleManager
				FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
				if (pModule == nullptr) return;


				AdmobMediation& mediation = pModule->GetAdmobMediation();
				
				mediation.TriggerPlayRewardCompleteDelegates(strHoldType, (int32)amount);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_nativePlayRewardedComplete),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeDebugMessage(JNIEnv* jenv, jobject thiz, jstring debugMessage)
{
#if !UE_BUILD_SHIPPING
	FString strDebugMessage = FJavaHelper::FStringFromParam(jenv, debugMessage);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.nativeDebugMessage"), STAT_FSimpleDelegateGraphTask_nativeDebugMessage, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				//FModuleManager
				FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
				if (pModule == nullptr) return;


				AdmobMediation& mediation = pModule->GetAdmobMediation();

				mediation.TriggerEasyAdsDebugMessageDelegates(strDebugMessage);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_nativeDebugMessage),
				nullptr,
				ENamedThreads::GameThread
				);
#endif
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomInterstitialLoadSuccess(JNIEnv* jenv, jobject thiz, jstring adUnit)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomInterstitialLoadSuccess"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialLoadSuccess, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomInterstitialLoadSuccess\n"));
				ULoadCustomInterstitialAd::OnLoadCompleteCallback(strAdUnit);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialLoadSuccess),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomInterstitialLoadFail(JNIEnv* jenv, jobject thiz, jstring adUnit, jstring errmsg)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);
	FString strErrorMsg = FJavaHelper::FStringFromParam(jenv, errmsg);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomInterstitialLoadFail"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialLoadFail, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomInterstitialLoadFail\n"));
				ULoadCustomInterstitialAd::OnLoadFailCallback(strAdUnit, strErrorMsg);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialLoadFail),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomInterstitialClick(JNIEnv* jenv, jobject thiz, jstring adUnit)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomInterstitialClick"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialClick, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomInterstitialClick\n"));
				UShowCustomInterstitialAd::OnClickCallback(strAdUnit);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialClick),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomInterstitialShow(JNIEnv* jenv, jobject thiz, jstring adUnit)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomInterstitialShow"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialShow, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomInterstitialShow\n"));
				UShowCustomInterstitialAd::OnShowCallback(strAdUnit);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialShow),
				nullptr,
				ENamedThreads::GameThread
				);
}

__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomInterstitialClose(JNIEnv* jenv, jobject thiz, jstring adUnit)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomInterstitialClose"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialClose, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomInterstitialClose\n"));
				UShowCustomInterstitialAd::OnCloseCallback(strAdUnit);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomInterstitialClose),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadSuccess(JNIEnv* jenv, jobject thiz, jstring adUnit)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadSuccess"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadSuccess, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomRewardedVideoLoadSuccess\n"));
				ULoadCustomRewardedVideoAd::OnLoadCompleteCallback(strAdUnit);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadSuccess),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadFail(JNIEnv* jenv, jobject thiz, jstring adUnit, jstring errmsg)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	const char* pErrorMsg = jenv->GetStringUTFChars(errmsg, 0);
	FString strErrorMsg = FString(UTF8_TO_TCHAR(pErrorMsg));
	jenv->ReleaseStringUTFChars(errmsg, pErrorMsg);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadFail"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadFail, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomRewardedVideoLoadFail\n"));
				ULoadCustomRewardedVideoAd::OnLoadFailCallback(strAdUnit, strErrorMsg);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomRewardedVideoLoadFail),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoClose(JNIEnv* jenv, jobject thiz, jstring adUnit)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoClose"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoClose, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomPlayRewardedVideoClose\n"));
				UPlayCustomRewardedVideoAd::OnCloseCallback(strAdUnit);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoClose),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoFail(JNIEnv* jenv, jobject thiz, jstring adUnit, jstring errmsg)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);

	const char* pErrorMsg = jenv->GetStringUTFChars(errmsg, 0);
	FString strErrorMsg = FString(UTF8_TO_TCHAR(pErrorMsg));
	jenv->ReleaseStringUTFChars(errmsg, pErrorMsg);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoFail"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoFail, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomPlayRewardedVideoFail\n"));
				UPlayCustomRewardedVideoAd::OnFailCallback(strAdUnit, strErrorMsg);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoFail),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoComplete(JNIEnv* jenv, jobject thiz, jstring adUnit, jstring type, jint amount)
{
	FString strAdUnit = FJavaHelper::FStringFromParam(jenv, adUnit);
	FString strType = FJavaHelper::FStringFromParam(jenv, type);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoComplete"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoComplete, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeCustomPlayRewardedVideoComplete\n"));
				UPlayCustomRewardedVideoAd::OnEarnCallback(strAdUnit, strType, (int32)amount);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeCustomPlayRewardedVideoComplete),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeOnConsentInfoUpdated(JNIEnv* jenv, jobject thiz, jstring publisherId, jboolean isSuccess, jint status)
{
	FString strPublisherId = FJavaHelper::FStringFromParam(jenv, publisherId);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeOnConsentInfoUpdated"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeOnConsentInfoUpdated, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeOnConsentInfoUpdated\n"));
				URequestConsentInfoUpdate::OnConsentUpdateCallback(strPublisherId, (bool)isSuccess, status);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeOnConsentInfoUpdated),
				nullptr,
				ENamedThreads::GameThread
				);
}


__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_AdMob_nativeOnUserConfirmConsent(JNIEnv* jenv, jobject thiz, jint status, jboolean preferAdFree)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_ads_util_AdMob_nativeOnUserConfirmConsent"), STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeOnUserConfirmConsent, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				FPlatformMisc::LowLevelOutputDebugStringf(TEXT("nativeOnUserConfirmConsent\n"));
				URequestUserConfirmConsent::OnUserConfirmConsent(status, preferAdFree);
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_ads_util_AdMob_nativeOnUserConfirmConsent),
				nullptr,
				ENamedThreads::GameThread
				);
}

