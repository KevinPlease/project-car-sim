/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LoadCustomRewardedVideoAd.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomRewardedVideoLoadFailDelegate, FString, errmsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomRewardedVideoLoadSuccessDelegate);

/**
 * 
 */
UCLASS()
class EASYADS_API ULoadCustomRewardedVideoAd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	ULoadCustomRewardedVideoAd();
	~ULoadCustomRewardedVideoAd();

	UPROPERTY(BlueprintAssignable)
	FCustomRewardedVideoLoadFailDelegate OnLoadFail;


	UPROPERTY(BlueprintAssignable)
	FCustomRewardedVideoLoadSuccessDelegate OnLoadSuccess;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadCustomRewardedVideoAd", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
	static ULoadCustomRewardedVideoAd* LoadCustomRewardedVideoAd(const FString& adUnit);

	virtual void Activate() override;

	static void OnLoadCompleteCallback(const FString& adUnit);
	static void OnLoadFailCallback(const FString& adUnit, const FString& errmsg);

private:

	FString mAdUnit;
	static TMap<FString, ULoadCustomRewardedVideoAd*> mLoadCustomRewardedVideoMap;
};
