/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AdmobMediation.h"
#include "PlayVideoProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicEasyAdsDebugMessageDelegate, FString, debugMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayRewardedDelegate, FString, item, int32, amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicRewardedClosedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicInterstitialShowDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicInterstitialClickDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicInterstitialCloseDelegate);


/**
 * 
 */
UCLASS()
class EASYADS_API UPlayVideoProxy : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPlayVideoProxy();

	/**
	* Called when the Rewarded video ads complete
	*/
	UPROPERTY(BlueprintAssignable)
		FPlayRewardedDelegate OnSuccess;


	UPROPERTY(BlueprintAssignable)
		FDynamicRewardedClosedDelegate OnClosed;

	/**
	* play rewarded video ads
	* @param	AdType		the type of the ads
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayRewardedVideo", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
		static UPlayVideoProxy* PlayRewardedVideo();

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;


private:

	FPlayRewardCompleteDelegate Delegate;
	FDelegateHandle DelegateHandle;

	FPlayRewardClosedDelegate CloseDelegate;
	FDelegateHandle CloseDelegateHandle;


	void OnComplete(FString, int32);
	void OnClosedCallback();
	
};
