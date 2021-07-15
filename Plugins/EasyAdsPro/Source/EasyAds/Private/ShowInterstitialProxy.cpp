/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/


#include "ShowInterstitialProxy.h"
#include "EasyAds.h"

UShowInterstitialProxy::UShowInterstitialProxy() :
	ShowDelegate(FInterstitialShowDelegate::CreateUObject(this, &ThisClass::OnShowCallback)),
	ClickDelegate(FInterstitialClickDelegate::CreateUObject(this, &ThisClass::OnClickCallback)),
	CloseDelegate(FInterstitialClosedDelegate::CreateUObject(this, &ThisClass::OnCloseCallback))
{

}

UShowInterstitialProxy* UShowInterstitialProxy::ShowInterstitial()
{
	
	UShowInterstitialProxy* Proxy = NewObject<UShowInterstitialProxy>();

		return Proxy;

}


void UShowInterstitialProxy::Activate()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();

	mediation.ClearAllInterstitialShowDelegate_Handle();
	mediation.ClearAllInterstitialClickDelegate_Handle();
	mediation.ClearAllInterstitialClosedDelegate_Handle();


		ShowDelegateHandle = mediation.AddInterstitialShowDelegate_Handle(ShowDelegate);
		ClickDelegateHandle = mediation.AddInterstitialClickDelegate_Handle(ClickDelegate);
		CloseDelegateHandle = mediation.AddInterstitialClosedDelegate_Handle(CloseDelegate);

		mediation.ShowInterstitial();
	
}


void UShowInterstitialProxy::OnShowCallback()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();

	OnShow.Broadcast();

	mediation.ClearInterstitialShowDelegate_Handle(ShowDelegateHandle);
}

void UShowInterstitialProxy::OnClickCallback()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();

	OnClick.Broadcast();

	mediation.ClearInterstitialClickDelegate_Handle(ClickDelegateHandle);
}

void UShowInterstitialProxy::OnCloseCallback()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();

	OnClose.Broadcast();

	mediation.ClearInterstitialClosedDelegate_Handle(CloseDelegateHandle);
}
