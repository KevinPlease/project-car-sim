/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "AdmobMediation.h"
#include "PlayVideoProxy.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RcvEasyAdsDebugMessage.generated.h"

/**
 * 
 */
UCLASS()
class EASYADS_API URcvEasyAdsDebugMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


public:

	URcvEasyAdsDebugMessage();

	UPROPERTY(BlueprintAssignable)
		FDynamicEasyAdsDebugMessageDelegate OnDebugMessage;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RcvEasyAdsDebugMessage", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
	static URcvEasyAdsDebugMessage* RcvEasyAdsDebugMessage();

	virtual void Activate() override;
	
private:

	FEasyAdsDebugMessageDelegate RcvDebugMessageDelegate;
	FDelegateHandle RcvDebugMessageDelegateHandle;

	void OnRcvDebugMessageCallback(FString debugMessage);
};
