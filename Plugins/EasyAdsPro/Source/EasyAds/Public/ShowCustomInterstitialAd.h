/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ShowCustomInterstitialAd.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomInterstitialClickDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomInterstitialShowDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomInterstitialCloseDelegate);

/**
 * 
 */
UCLASS()
class EASYADS_API UShowCustomInterstitialAd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UShowCustomInterstitialAd();
	~UShowCustomInterstitialAd();

	UPROPERTY(BlueprintAssignable)
	FCustomInterstitialClickDelegate OnClick;

	UPROPERTY(BlueprintAssignable)
	FCustomInterstitialShowDelegate OnShow;

	UPROPERTY(BlueprintAssignable)
	FCustomInterstitialCloseDelegate OnClose;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowCustomInterstitialAd", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds")
	static UShowCustomInterstitialAd* ShowCustomInterstitialAd(const FString& adUnit);

	virtual void Activate() override;

	static void OnClickCallback(const FString& adUnit);
	static void OnShowCallback(const FString& adUnit);
	static void OnCloseCallback(const FString& adUnit);
	
private:

	FString mAdUnit;
	static TMap<FString, UShowCustomInterstitialAd*> mLoadCustomInterstitialMap;
};
