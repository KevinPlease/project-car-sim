/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#include "PlayVideoProxy.h"
#include "EasyAds.h"

UPlayVideoProxy::UPlayVideoProxy() :
	Delegate(FPlayRewardCompleteDelegate::CreateUObject(this, &ThisClass::OnComplete)), CloseDelegate(FPlayRewardClosedDelegate::CreateUObject(this, &ThisClass::OnClosedCallback))
{
}


UPlayVideoProxy* UPlayVideoProxy::PlayRewardedVideo()
{
	UPlayVideoProxy* Proxy = NewObject<UPlayVideoProxy>();
	return Proxy;
}



void UPlayVideoProxy::OnComplete(FString item, int32 amout)
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();

	OnSuccess.Broadcast(item, amout);

	mediation.ClearPlayRewardCompleteDelegate_Handle(CloseDelegateHandle);
}

void UPlayVideoProxy::OnClosedCallback()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();

	OnClosed.Broadcast();

	mediation.ClearPlayRewardClosedDelegate_Handle(CloseDelegateHandle);
}

void UPlayVideoProxy::Activate()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	
	mediation.ClearAllPlayRewardCompleteDelegate_Handle();
	DelegateHandle = mediation.AddPlayRewardCompleteDelegate_Handle(Delegate);

	mediation.ClearAllPlayRewardClosedDelegate_Handle();
	CloseDelegateHandle = mediation.AddPlayRewardClosedDelegate_Handle(CloseDelegate);

	mediation.PlayRewardedVideo();
}
