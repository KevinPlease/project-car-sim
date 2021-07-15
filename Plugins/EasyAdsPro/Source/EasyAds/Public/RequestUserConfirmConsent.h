/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EasyAdsLibrary.h"
#include "RequestUserConfirmConsent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUserConfirmConsentDelegate, ConsentStatus, status, bool, preferAdFree);

/**
 * 
 */
UCLASS()
class EASYADS_API URequestUserConfirmConsent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	URequestUserConfirmConsent();
	~URequestUserConfirmConsent();

	UPROPERTY(BlueprintAssignable)
	FUserConfirmConsentDelegate OnConfirmDelegate;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RequestUserConfirmConsent", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "EasyAds|GDPR")
	static URequestUserConfirmConsent* RequestUserConfirmConsent(const FString& privacyUrl, bool withAdFreeOption);

	virtual void Activate() override;
	static void OnUserConfirmConsent(int status, bool preferAdFree);
	
private:
	FString mPrivacyUrl;
	bool mWithAdFreeOption;
	static TSet<URequestUserConfirmConsent*> mRequestList;
};
