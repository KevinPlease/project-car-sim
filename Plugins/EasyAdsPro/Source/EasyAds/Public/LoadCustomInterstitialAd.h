/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LoadCustomInterstitialAd.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomInterstitialLoadFailDelegate, FString, errmsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomInterstitialLoadSuccessDelegate);


/**
 * 
 */
UCLASS()
class EASYADS_API ULoadCustomInterstitialAd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	ULoadCustomInterstitialAd();
	~ULoadCustomInterstitialAd();

	UPROPERTY(BlueprintAssignable)
	FCustomInterstitialLoadFailDelegate OnLoadFail;


	UPROPERTY(BlueprintAssignable)
	FCustomInterstitialLoadSuccessDelegate OnLoadSuccess;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadCustomInterstitialAd", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
	static ULoadCustomInterstitialAd* LoadCustomInterstitialAd(const FString& adUnit);

	virtual void Activate() override;

	static void OnLoadCompleteCallback(const FString& adUnit);
	static void OnLoadFailCallback(const FString& adUnit, const FString& errmsg);

private:
	FString mAdUnit;
	static TMap<FString, ULoadCustomInterstitialAd*> mLoadCustomInterstitialMap;
};
