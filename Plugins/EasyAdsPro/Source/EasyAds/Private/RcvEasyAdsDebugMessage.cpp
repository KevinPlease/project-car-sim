/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#include "RcvEasyAdsDebugMessage.h"
#include "EasyAds.h"

URcvEasyAdsDebugMessage::URcvEasyAdsDebugMessage():
	RcvDebugMessageDelegate(FEasyAdsDebugMessageDelegate::CreateUObject(this, &ThisClass::OnRcvDebugMessageCallback))
{

}

URcvEasyAdsDebugMessage* URcvEasyAdsDebugMessage::RcvEasyAdsDebugMessage()
{
	URcvEasyAdsDebugMessage* Proxy = NewObject<URcvEasyAdsDebugMessage>();

	return Proxy;
}

void URcvEasyAdsDebugMessage::Activate()
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	AdmobMediation& mediation = pModule->GetAdmobMediation();
	
	RcvDebugMessageDelegateHandle = mediation.AddEasyAdsDebugMessageDelegate_Handle(RcvDebugMessageDelegate);
}


void URcvEasyAdsDebugMessage::OnRcvDebugMessageCallback(FString debugMessage)
{
	FEasyAdsModule* pModule = FModuleManager::Get().LoadModulePtr<FEasyAdsModule>(TEXT("EasyAds"));
	if (pModule == nullptr) return;

	OnDebugMessage.Broadcast(debugMessage);
}