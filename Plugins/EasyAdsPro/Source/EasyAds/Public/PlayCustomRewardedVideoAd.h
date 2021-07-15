/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "PlayCustomRewardedVideoAd.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCustomRewardedVideoEarnDelegate, FString, type, int32, amout);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomRewardedVideoCloseDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomRewardedVideoFailDelegate, FString, errmsg);


/**
 * 
 */
UCLASS()
class EASYADS_API UPlayCustomRewardedVideoAd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPlayCustomRewardedVideoAd();
	~UPlayCustomRewardedVideoAd();

	UPROPERTY(BlueprintAssignable)
	FCustomRewardedVideoEarnDelegate OnComplete;

	UPROPERTY(BlueprintAssignable)
	FCustomRewardedVideoFailDelegate OnFail;

	UPROPERTY(BlueprintAssignable)
	FCustomRewardedVideoCloseDelegate OnClose;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayCustomRewardedVideoAd", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
	static UPlayCustomRewardedVideoAd* PlayCustomRewardedVideoAd(const FString& adUnit);

	virtual void Activate() override;
	
	static void OnEarnCallback(const FString& adUnit, const FString& rewardedType, int32 amount);
	static void OnFailCallback(const FString& adUnit, const FString& errmsg);
	static void OnCloseCallback(const FString& adUnit);

private:

	FString mAdUnit;
	static TMap<FString, UPlayCustomRewardedVideoAd*> mPlayCustomRewardedVideoMap;
};
