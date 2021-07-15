/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EasyAdsLibrary.h"
#include "RequestConsentInfoUpdate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConsentInfoUpdateDelegate, bool, IsSuccess, ConsentStatus, status);

/**
 * 
 */
UCLASS()
class EASYADS_API URequestConsentInfoUpdate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	URequestConsentInfoUpdate();
	~URequestConsentInfoUpdate();

	UPROPERTY(BlueprintAssignable)
	FConsentInfoUpdateDelegate OnConsentUpdate;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RequestConsentInfoUpdate", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds|GDPR")
	static URequestConsentInfoUpdate* RequestConsentInfoUpdate(const FString& publisherId);

	virtual void Activate() override;

	static void OnConsentUpdateCallback(const FString& publisherId, bool isSuccess, int status);

private:

	FString mPublisherId;
	static TMap<FString, URequestConsentInfoUpdate*> mRequuestConsentInfoMap;
};
