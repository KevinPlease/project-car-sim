/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AdmobMediation.h"
#include "PlayVideoProxy.h"
#include "ShowInterstitialProxy.generated.h"

/**
 * 
 */
UCLASS()
class EASYADS_API UShowInterstitialProxy : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UShowInterstitialProxy();

	UPROPERTY(BlueprintAssignable)
		FDynamicInterstitialShowDelegate OnShow;

	UPROPERTY(BlueprintAssignable)
		FDynamicInterstitialClickDelegate OnClick;

	UPROPERTY(BlueprintAssignable)
		FDynamicInterstitialCloseDelegate OnClose;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowInterstitial", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
		static UShowInterstitialProxy* ShowInterstitial();

	virtual void Activate() override;


private:

	FInterstitialShowDelegate ShowDelegate;
	FDelegateHandle ShowDelegateHandle;

	FInterstitialClickDelegate ClickDelegate;
	FDelegateHandle ClickDelegateHandle;

	FInterstitialClosedDelegate CloseDelegate;
	FDelegateHandle CloseDelegateHandle;

	void OnShowCallback();
	void OnClickCallback();
	void OnCloseCallback();
};
