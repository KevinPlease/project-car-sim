//
//  AdMobHelper.m
//  AdsUtil
//
//  Created by Xufei Wu on 2017/6/28.
//  Copyright © 2017年 Xufei Wu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AdSupport/AdSupport.h>
#import "AdMobHelper.h"
#import <GoogleMobileAds/GoogleMobileAds.h>


static AdMobHelper* AdMobHelperSingleton = NULL;
static BOOL isAdMobInsterstitalReady = FALSE;
static BOOL isAdMobBannerReady = FALSE;
static GADBannerView *bannerViewSingleton = NULL;
static GADInterstitial* instertitialViewSingleton = NULL;
static GADRewardedAd* rewardedVideoSingleton = NULL;
static NSString* adMobReawrdedVideoUnit = NULL;
static NSString* adMobInterstitialUnit = NULL;
static const int INVALID=0;
static const int UNKNOW = 1;
static const int NON_PERSONALIZED = 2;
static const int PERSONALIZED = 3;

static int admobRefreshTimer = 35000;
static void(*admobRcvDebugMessageCb)(NSString* debugMessage) = NULL;

static void(*admobCustomInterstitialLoadCb)(NSString* adUnit, bool isSuccess, NSString* errmsg) = NULL;
static void(*admobCustomRewardedLoadCb)(NSString* adUnit, bool isSuccess, NSString* errmsg) = NULL;

static void(*admobCustomInterstitialClickCb)(NSString* adUnit) = NULL;
static void(*admobCustomInterstitialShowCb)(NSString* adUnit) = NULL;
static void(*admobCustomInterstitialCloseCb)(NSString* adUnit) = NULL;
static void(*admobCustomRewardCompleteCb)(NSString* adUnit, NSString* type, int amount);
static void(*admobCustomRewardCloseCb)(NSString* adUnit) = NULL;
static void(*admobCustomRewardFailCb)(NSString* adUnit, NSString* errmsg) = NULL;
static void(*admobUserConfirmConsent)(int status, bool preferAdsFree);
static void(*admobConsentInfoUpdate)(NSString* publisherId, bool success, int status);

static NSMutableDictionary *admobCustomInterstitialDic = NULL;
static NSMutableDictionary *admobCustomRewardedVideoDic = NULL;

static NSMutableDictionary *admobCustomInterstitialDelegate = NULL;
static NSMutableDictionary *admobCustomRewardedDelegate = NULL;
static bool s_isInitlized = false;

@interface AutoRewardedVideoDelegate : NSObject<GADRewardedAdDelegate>
    @property void (*completeCallback)(NSString* strType, int amount);
    @property void (*closeCallback)(void);
@end

@implementation AutoRewardedVideoDelegate
- (void)rewardedAd:(nonnull GADRewardedAd *)rewardedAd
    userDidEarnReward:(nonnull GADAdReward *)reward
{
    self.completeCallback(reward.type, [reward.amount intValue]);
    NSString *s = [NSString stringWithFormat : @"Admob RewardedVideo reward: %@ %@", reward.type, reward.amount];
    if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
}


- (void)rewardedAd:(nonnull GADRewardedAd *)rewardedAd
    didFailToPresentWithError:(nonnull NSError *)error
{
    NSString *s = [NSString stringWithFormat : @"Admob RewardedVideo Fail Present: %@", error];
    if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
}

- (void)rewardedAdDidPresent:(nonnull GADRewardedAd *)rewardedAd
{
}


- (void)rewardedAdDidDismiss:(nonnull GADRewardedAd *)rewardedAd
{
    self.closeCallback();
	[AdMobHelperSingleton AutoReloadReward];
    if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"admob RewardedVideo closed");
}

@end

static AutoRewardedVideoDelegate* s_rewardedVideoCb = NULL;

@interface IntersitialDelegate : NSObject<GADInterstitialDelegate>
    @property void (*interstitialShow)(void);
    @property void (*interstitialClick)(void);
    @property void (*interstitialClose)(void);
@end

static IntersitialDelegate* admobInterstitalDelegate = NULL;

@implementation IntersitialDelegate

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
    isAdMobInsterstitalReady = true;
	NSLog(@"AdMob Interstital Cache Success!!!");
	if(admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"AdMob Interstital Cache Success!!!");
}

- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"Admob Interstitial Cache Fail:%@", error);

	[self reloadInterstitial];
	NSString *s = [NSString stringWithFormat : @"Admob Interstitial Cache Fail : %@", error];
	if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
}

- (void)interstitialWillPresentScreen:(GADInterstitial *)ad
{
    _interstitialShow();
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
	[self reloadInterstitial];
    _interstitialClose();
}

-(void)reloadInterstitial {
	[NSTimer scheduledTimerWithTimeInterval : admobRefreshTimer / 1000.0 repeats : false block : ^ (NSTimer *_timer) {
		instertitialViewSingleton = [[GADInterstitial alloc]
			initWithAdUnitID:adMobInterstitialUnit];

		instertitialViewSingleton.delegate = admobInterstitalDelegate;

		GADRequest *request = [GADRequest request];
        [AdMobHelperSingleton ProcessGDPR:request];
		[instertitialViewSingleton loadRequest : request];
	}];
}

@end


@interface CustomIntersitialDelegate : NSObject<GADInterstitialDelegate>
    @property(retain) NSString* adUnit;
@end

@implementation CustomIntersitialDelegate
    - (void)interstitialDidReceiveAd:(GADInterstitial *)ad
    {
        if(admobCustomInterstitialLoadCb != NULL){
            admobCustomInterstitialLoadCb(_adUnit, true, @"");
        }
        if(admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"AdMob Custom Interstital Cache Success!!!");
    }

    - (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
    {
        NSString *s = [NSString stringWithFormat : @"Admob Custom Interstitial Cache Fail : %@", error];
        if(admobCustomInterstitialLoadCb != NULL){
            admobCustomInterstitialLoadCb(_adUnit, false, s);
        }
        
        if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
    }

    - (void)interstitialWillPresentScreen:(GADInterstitial *)ad
    {
        admobCustomInterstitialShowCb(_adUnit);
    }

    - (void)interstitialDidDismissScreen:(GADInterstitial *)ad
    {
        admobCustomInterstitialCloseCb(_adUnit);
    }
@end

@interface CustomRewardedVideoDelegate : NSObject<GADRewardedAdDelegate>
    @property(retain) NSString* adUnit;
@end

@implementation CustomRewardedVideoDelegate
    - (void)rewardedAd:(nonnull GADRewardedAd *)rewardedAd
    userDidEarnReward:(nonnull GADAdReward *)reward
{
    admobCustomRewardCompleteCb(_adUnit, reward.type, [reward.amount intValue]);
    NSString *s = [NSString stringWithFormat : @"Admob Custom RewardedVideo reward: %@ %@", reward.type, reward.amount];
    if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
}


- (void)rewardedAd:(nonnull GADRewardedAd *)rewardedAd
    didFailToPresentWithError:(nonnull NSError *)error
{
    NSString *s = [NSString stringWithFormat : @"Admob Custom RewardedVideo Fail Present: %@", error];
    admobCustomRewardFailCb(_adUnit, s);
    if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
}

- (void)rewardedAdDidPresent:(nonnull GADRewardedAd *)rewardedAd
{
}


- (void)rewardedAdDidDismiss:(nonnull GADRewardedAd *)rewardedAd
{
    admobCustomRewardCloseCb(_adUnit);
    if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"admob Custom RewardedVideo closed");
}

@end


@interface BannerDelegate : NSObject<GADBannerViewDelegate>

@end

static BannerDelegate* admobBannerDelegate = NULL;

@implementation BannerDelegate

- (void)adViewDidReceiveAd:(GADBannerView *)bannerView
{
    isAdMobBannerReady = TRUE;
    NSLog(@"AdMob Banner Cache success!!!");

	if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"AdMob Banner Cache success!!!");
}

- (void)adView:(GADBannerView *)bannerView didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"Admob Banner Cache Fail:%@", error);
	[self reloadBanner];
	NSString *s = [NSString stringWithFormat : @"Admob Banner Cache Fail : %@", error];
	if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
}

-(void)reloadBanner {
	[NSTimer scheduledTimerWithTimeInterval : admobRefreshTimer / 1000.0 repeats : false block : ^ (NSTimer *_timer) {
		GADRequest *request = [GADRequest request];
        [AdMobHelperSingleton ProcessGDPR:request];
        [bannerViewSingleton loadRequest : request];
	}];
}


@end


@implementation AdMobHelper

+ (AdMobHelper*) GetDelegate
{
    if(AdMobHelperSingleton == NULL)
    {
        AdMobHelperSingleton = [AdMobHelper new];
    }
    
    return AdMobHelperSingleton;
}

-(void)IsSdkInitlized:(NSMutableDictionary*)result;
{
	NSNumber *boolNumber = [NSNumber numberWithBool : s_isInitlized];
	[result setValue : boolNumber forKey : @"RetValue"];
}

- (void) InitSDK:(UIViewController*) viewController AppID:(NSString*) AppID  testDevice : (NSArray<NSString *> *)testDevice BannerUnit:(NSString*)BannerUnit InterstitalUnit:(NSString*)InterstitalUnit RewardedUnit:(NSString*)RewardedUnit callback:(void(*)(NSString* strType, int amount)) callback rewardClose:(void(*)(void)) rewardClose interstitialShow:(void(*)(void)) interstitialShow  interstitialClick:(void(*)(void)) interstitialClick interstitialClose:(void(*)(void)) interstitialClose rcvDebugMessage : (void(*)(NSString* debugMessage)) rcvDebugMessage
    customInterstitialLoadResult:(void(*)(NSString* adUnit, bool isSuccess, NSString* errmsg))  customInterstitialLoadResult
        customRewardedVideoLoadResult:(void(*)(NSString* adUnit, bool isSuccess, NSString* errmsg)) customRewardedVideoLoadResult
        customInterstitialClick:(void(*)(NSString* adUnit)) customInterstitialClick
        customInterstitialShow:(void(*)(NSString* adUnit)) customInterstitialShow
        customInterstitialClose:(void(*)(NSString* adUnit)) customInterstitialClose
        customRewardedComplete:(void(*)(NSString* adUnit, NSString* type, int amount)) customRewardedComplete
        customRewardedClos:(void(*)(NSString* adUnit)) customRewardedClos
    customRewardedFail:(void(*)(NSString* adUnit, NSString* errmsg)) customRewardedFail
    userConfirmConsent:(void(*)(int status, bool preferAdsFree)) userConfirmConsent
    consentInfoUpdate:(void(*)(NSString* publisherId, bool success, int status)) consentInfoUpdate
{
    admobCustomInterstitialLoadCb =customInterstitialLoadResult;
    admobCustomRewardedLoadCb = customRewardedVideoLoadResult;
    admobCustomInterstitialClickCb = customInterstitialClick;
    admobCustomInterstitialShowCb = customInterstitialShow;
    admobCustomInterstitialCloseCb = customInterstitialClose;
    admobCustomRewardCompleteCb = customRewardedComplete;
    admobCustomRewardCloseCb = customRewardedClos;
    admobCustomRewardFailCb = customRewardedFail;
    admobUserConfirmConsent = userConfirmConsent;
    admobConsentInfoUpdate = consentInfoUpdate;
    
    admobCustomInterstitialDic = [[NSMutableDictionary alloc] init];
    admobCustomRewardedVideoDic = [[NSMutableDictionary alloc] init];
    
    admobCustomInterstitialDelegate = [[NSMutableDictionary alloc] init];
    admobCustomRewardedDelegate = [[NSMutableDictionary alloc] init];
	PACConsentInformation.sharedInstance.debugIdentifiers = testDevice;
	// Geography appears as in EEA for debug devices.
	PACConsentInformation.sharedInstance.debugGeography = PACDebugGeographyEEA;

    [[GADMobileAds sharedInstance] startWithCompletionHandler:^(GADInitializationStatus *_Nonnull status) {
		NSLog(@"MobileAds Status begin---");
        NSLog(@"Admob Advertising ID: %@",
      ASIdentifierManager.sharedManager.advertisingIdentifier.UUIDString);
		s_isInitlized = true;
	  	admobRcvDebugMessageCb = rcvDebugMessage;

        for (NSString* key in status.adapterStatusesByClassName)
        {
            NSLog(@"MobileAds Status ad network:%@ status:%ld", key, status.adapterStatusesByClassName[key].state);
        }

        NSLog(@"MobileAds Status end--- ");
        if(testDevice)
        {
            GADMobileAds.sharedInstance.requestConfiguration.testDeviceIdentifiers = testDevice;
        }

        if (BannerUnit != NULL && BannerUnit.length > 1)
        {
            bannerViewSingleton = [[GADBannerView alloc]
                initWithAdSize:kGADAdSizeSmartBannerPortrait];
            bannerViewSingleton.hidden = TRUE;

            bannerViewSingleton.adUnitID = BannerUnit;
            bannerViewSingleton.rootViewController = viewController;
            admobBannerDelegate = [BannerDelegate new];
            bannerViewSingleton.delegate = admobBannerDelegate;

            GADRequest *request = [GADRequest request];
            [bannerViewSingleton loadRequest : request];
        }
        
        if (InterstitalUnit != NULL && InterstitalUnit.length > 1)
        {
            adMobInterstitialUnit = InterstitalUnit;

            admobInterstitalDelegate = [IntersitialDelegate new];
            admobInterstitalDelegate.interstitialShow = interstitialShow;
            admobInterstitalDelegate.interstitialClick = interstitialClick;
            admobInterstitalDelegate.interstitialClose = interstitialClose;

            instertitialViewSingleton = [[GADInterstitial alloc]
                initWithAdUnitID:InterstitalUnit];

            instertitialViewSingleton.delegate = admobInterstitalDelegate;

            GADRequest *request = [GADRequest request];
            [instertitialViewSingleton loadRequest : request];
        }

        if (RewardedUnit != NULL && RewardedUnit.length > 1)
        {
            adMobReawrdedVideoUnit = RewardedUnit;
            rewardedVideoSingleton = [[GADRewardedAd alloc]
                                      initWithAdUnitID:adMobReawrdedVideoUnit];
            s_rewardedVideoCb = [AutoRewardedVideoDelegate new];
            s_rewardedVideoCb.closeCallback = rewardClose;
            s_rewardedVideoCb.completeCallback = callback;

			[self AutoReloadReward];
        }
        
        NSLog(@"AdMob Init:%@ %@ %@ %@\n", AppID, BannerUnit, InterstitalUnit, RewardedUnit);
    }];
}

-(void) AutoReloadReward
{
    GADRequest *request = [GADRequest request];
	rewardedVideoSingleton = [[GADRewardedAd alloc]
		initWithAdUnitID:adMobReawrdedVideoUnit];
    [rewardedVideoSingleton loadRequest:request completionHandler:^(GADRequestError * _Nullable error) {
        if (error) {
            // Handle ad failed to load case.
            NSLog(@"Admob rewarded load fail:%@", error);
            //[self reloadRewardVideo];
            [NSTimer scheduledTimerWithTimeInterval : admobRefreshTimer / 1000.0 repeats : false block : ^ (NSTimer *_timer) {
                [self AutoReloadReward];
            }];
            NSString *s = [NSString stringWithFormat : @"Admob rewarded load fail : %@", error];
            if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
        } else {
            // Ad successfully loaded.
            NSLog(@"Admob rewarded load success!!");
            if(admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"Admob rewarded load success!!");
        }
    }];
}


-(int) ConsentStatusToInt:(PACConsentStatus) status
{
    int ret = INVALID;
    if(status == PACConsentStatusUnknown){
        ret = UNKNOW;
    } else if(status == PACConsentStatusNonPersonalized){
        ret = NON_PERSONALIZED;
    } else if(status == PACConsentStatusPersonalized){
        ret = PERSONALIZED;
    }
    return ret;
}

-(PACConsentStatus) IntToConsentStatu:(int) status;
{
    PACConsentStatus ret = PACConsentStatusUnknown;
    if(status == NON_PERSONALIZED){
        ret = PACConsentStatusNonPersonalized;
    } else if(status == PERSONALIZED){
        ret = PACConsentStatusPersonalized;
    }
    
    return ret;
}

-(void) RequestConsentInfoUpdate:(NSString*) publisherId
{
    [PACConsentInformation.sharedInstance
    requestConsentInfoUpdateForPublisherIdentifiers:@[ publisherId]
      completionHandler:^(NSError *_Nullable error) {
        if (error) {
            NSLog(@"AdMob RequestConsentInfoUpdate fail:%@", error);
            if(admobConsentInfoUpdate != NULL){
                admobConsentInfoUpdate(publisherId, false, UNKNOW);
            }
        } else {
            NSLog(@"AdMob RequestConsentInfoUpdate success:%ld", PACConsentInformation.sharedInstance.consentStatus);
            if(admobConsentInfoUpdate != NULL){
                admobConsentInfoUpdate(publisherId, true, [self ConsentStatusToInt:PACConsentInformation.sharedInstance.consentStatus]);
            }
        }
      }];
}

-(void)RequestUserConfirmConsent:(UIViewController*) viewController privacyUrl: (NSString*)privacyUrl withAdsFreeOpt:(bool)withAdsFreeOpt
{
    NSURL *privacyURL = [NSURL URLWithString: privacyUrl];
    PACConsentForm *form = [[PACConsentForm alloc] initWithApplicationPrivacyPolicyURL:privacyURL];
    form.shouldOfferPersonalizedAds = YES;
    form.shouldOfferNonPersonalizedAds = YES;
    form.shouldOfferAdFree = withAdsFreeOpt;
    
    [form loadWithCompletionHandler:^(NSError *_Nullable error) {
        if (error != NULL) {
            NSLog(@"AdMob Load complete. Error: %@", error);
            return;
        }
        
        NSLog(@"AdMob Load complete success");
        [form presentFromViewController:viewController
         dismissCompletion:^(NSError *_Nullable completeError, BOOL userPrefersAdFree) {
            if (completeError) {
                NSLog(@"AdMob presentFromViewController dismissCompletion Error: %@", completeError);
            } else if (userPrefersAdFree) {
                if(admobUserConfirmConsent != NULL){
                    admobUserConfirmConsent(UNKNOW, true);
                }
            } else {
             
                PACConsentStatus status = PACConsentInformation.sharedInstance.consentStatus;
                if(admobUserConfirmConsent != NULL){
                    admobUserConfirmConsent([self ConsentStatusToInt:status], false);
                }
            }
        }];
    }];
}

-(void)GetConsentStatus:(NSMutableDictionary*)result;
{
    NSNumber *statusNumber = [NSNumber numberWithInt:[self ConsentStatusToInt:PACConsentInformation.sharedInstance.consentStatus] ];
    [result setValue:statusNumber forKey:@"RetValue"];
}

-(void)SetConsentStatus:(int) status
{
    PACConsentStatus consentStatus = [self IntToConsentStatu:status];
    PACConsentInformation.sharedInstance.consentStatus = consentStatus;
}

-(void)IsLocationInEEA:(NSMutableDictionary*) result
{    
    NSNumber *boolNumber = [NSNumber numberWithBool:PACConsentInformation.sharedInstance.requestLocationInEEAOrUnknown];
    [result setValue:boolNumber forKey:@"RetValue"];
    
}

-(void)IsUseNonPersonalizedAds:(NSMutableDictionary*) result
{
    bool bUseNonPersonalizedAds = [self UseNonPersonallziedAds];
    NSNumber *boolNumber = [NSNumber numberWithBool:bUseNonPersonalizedAds];
    [result setValue:boolNumber forKey:@"RetValue"];
}

-(bool)UseNonPersonallziedAds
{
    // if not in eea, use personalized ads
    if(PACConsentInformation.sharedInstance.requestLocationInEEAOrUnknown == NO){
        return false;
    }
    
    // if age under consent, use non personalized ads
    if(PACConsentInformation.sharedInstance.isTaggedForUnderAgeOfConsent == YES){
        return true;
    }
    
    if(PACConsentInformation.sharedInstance.consentStatus == PACConsentStatusNonPersonalized){
        return true;
    }
    
    return false;
}

-(void)ProcessGDPR:(GADRequest*) request
{
    bool useNonPersonalizeAds = [self UseNonPersonallziedAds];
    if(useNonPersonalizeAds){
        GADExtras *extras = [[GADExtras alloc] init];
        extras.additionalParameters = @{@"npa": @"1"};
        [request registerAdNetworkExtras:extras];
    }
}

-(void)SetTagForUnderAgeOfConsent:(bool) underAgeOfConsent
{
    if(underAgeOfConsent){
        PACConsentInformation.sharedInstance.tagForUnderAgeOfConsent = YES;
    } else {
        PACConsentInformation.sharedInstance.tagForUnderAgeOfConsent = NO;
    }
}

-(void) ShowBanner:(UIViewController*)viewController isBottom:(BOOL)isBottom
{
    if(isAdMobBannerReady)
    {
        [bannerViewSingleton.rootViewController.view willRemoveSubview:bannerViewSingleton];
        bannerViewSingleton.rootViewController = viewController;
        [viewController.view addSubview:bannerViewSingleton];
        
        CGRect bannerFrame = CGRectZero;
        bannerFrame.size = bannerViewSingleton.bounds.size;
        
        if(isBottom)
        {
            bannerFrame.origin.y = viewController.view.bounds.size.height - bannerFrame.size.height;
        }
        bannerFrame.origin.x = (viewController.view.bounds.size.width - bannerFrame.size.width)/2;
        
        bannerViewSingleton.frame = bannerFrame;
        bannerViewSingleton.hidden = FALSE;
        isAdMobBannerReady = FALSE;

		GADRequest *request = [GADRequest request];
        [self ProcessGDPR:request];
        [bannerViewSingleton loadRequest: request];
    }
}

-(void) LoadCustomInterstitial:(UIViewController*) viewController adUnit:(NSString*) adUnit
{
    if([admobCustomInterstitialDic objectForKey:adUnit])
    {
        [admobCustomInterstitialDic removeObjectForKey:adUnit];
        [admobCustomInterstitialDelegate removeObjectForKey:adUnit];
    }
    
    GADInterstitial *newInterstitial = [[GADInterstitial alloc] initWithAdUnitID:adUnit];
    [admobCustomInterstitialDic setObject:newInterstitial forKey:adUnit];
    CustomIntersitialDelegate* cb = [CustomIntersitialDelegate new];
    cb.adUnit = adUnit;
    
    newInterstitial.delegate = cb;
    [admobCustomInterstitialDelegate setObject:cb forKey:adUnit];
    
    GADRequest *request = [GADRequest request];
    [self ProcessGDPR:request];
    [newInterstitial loadRequest : request];
}

-(void) IsCustomInterstitialReady:(NSMutableDictionary*) result
{
    if(![result objectForKey:@"AdUnit"])
    {
        NSNumber *boolNumber = [NSNumber numberWithBool:false];
        [result setValue:boolNumber forKey:@"RetValue"];
        return;
    }
    
    NSString* adUnit = [result objectForKey:@"AdUnit"];
    
    if(![admobCustomInterstitialDic objectForKey:adUnit])
    {
        NSNumber *boolNumber = [NSNumber numberWithBool:false];
        [result setValue:boolNumber forKey:@"RetValue"];
        return;
    }
    
    GADInterstitial* customInterstitial = [admobCustomInterstitialDic objectForKey:adUnit];
    NSNumber *boolNumber = [NSNumber numberWithBool:customInterstitial.isReady];
    [result setValue:boolNumber forKey:@"RetValue"];
}

-(void) ShowCustomInterstitialAd:(UIViewController*) viewController adUnit:(NSString*) adUnit
{
    if(![admobCustomInterstitialDic objectForKey:adUnit])
    {
        return;
    }
    
    GADInterstitial* customInterstitial = [admobCustomInterstitialDic objectForKey:adUnit];
    [customInterstitial presentFromRootViewController:viewController];
}

-(void) LoadCustomRewardedVideo:(UIViewController*) viewController adUnit:(NSString*) adUnit
{
    if([admobCustomRewardedVideoDic objectForKey:adUnit])
    {
        [admobCustomRewardedVideoDic removeObjectForKey:adUnit];
    }
    
    GADRewardedAd* newRewardedAd = [[GADRewardedAd alloc] initWithAdUnitID:adUnit];
    [admobCustomRewardedVideoDic setObject:newRewardedAd forKey:adUnit];
    
    GADRequest *request = [GADRequest request];
    [self ProcessGDPR:request];
    [newRewardedAd loadRequest:request completionHandler:^(GADRequestError * _Nullable error) {
        if(error)
        {
            NSString *s = [NSString stringWithFormat : @"Admob Custom RewardedVideo Load Fail : %@", error];
            admobCustomRewardedLoadCb(adUnit, false, s);
            if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(s);
        }
        else
        {
            admobCustomRewardedLoadCb(adUnit, true, @"");
            if (admobRcvDebugMessageCb != NULL) admobRcvDebugMessageCb(@"Admob Custom RewardedVideo Load Success");
        }
    }];
}

-(void) IsCustomRewardReady:(NSMutableDictionary*) result
{
    if(![result objectForKey:@"AdUnit"])
    {
        NSNumber *boolNumber = [NSNumber numberWithBool:false];
        [result setValue:boolNumber forKey:@"RetValue"];
        return;
    }
    
    NSString* adUnit = [result objectForKey:@"AdUnit"];
    
    if(![admobCustomRewardedVideoDic objectForKey:adUnit])
    {
        NSNumber *boolNumber = [NSNumber numberWithBool:false];
        [result setValue:boolNumber forKey:@"RetValue"];
        return;
    }
    
    GADRewardedAd* customRewardedVideo = [admobCustomRewardedVideoDic objectForKey:adUnit];
    NSNumber *boolNumber = [NSNumber numberWithBool:customRewardedVideo.isReady];
    [result setValue:boolNumber forKey:@"RetValue"];
}

-(void) PlayCustomRewardAd:(UIViewController*)viewController adUnit:(NSString*) adUnit
{
    if(![admobCustomRewardedVideoDic objectForKey:adUnit])
    {
        return;
    }
    
    GADRewardedAd* customRewardedVideo = [admobCustomRewardedVideoDic objectForKey:adUnit];
    if(!customRewardedVideo.isReady)
    {
        return;
    }
    
    [admobCustomRewardedDelegate removeObjectForKey:adUnit];
    CustomRewardedVideoDelegate* cb = [CustomRewardedVideoDelegate new];
    cb.adUnit = adUnit;
    [admobCustomRewardedDelegate setObject:cb forKey:adUnit];
    
    [customRewardedVideo presentFromRootViewController:viewController delegate:cb];
}

-(void) HideBanner
{
    if(bannerViewSingleton != NULL)
    {
        bannerViewSingleton.hidden = TRUE;
    }
}

-(void) IsBannerReady:(NSMutableDictionary*)result
{
    NSNumber *boolNumber = [NSNumber numberWithBool:isAdMobBannerReady];
    [result setValue:boolNumber forKey:@"RetValue"];
}

-(void) ShowInterstitialAds:(UIViewController*) viewController
{
    if (isAdMobInsterstitalReady)
    {
        [instertitialViewSingleton presentFromRootViewController:viewController];
        isAdMobInsterstitalReady = FALSE;
    }
}

-(void) IsInterstitalReady:(NSMutableDictionary*)result
{
    NSNumber *boolNumber = [NSNumber numberWithBool:isAdMobInsterstitalReady];
    [result setValue:boolNumber forKey:@"RetValue"];
}

-(void) Play:(UIViewController*) viewController
{
    if(rewardedVideoSingleton.isReady)
    {
        [rewardedVideoSingleton presentFromRootViewController:viewController delegate:s_rewardedVideoCb];
    }
}

-(void) IsPlayable:(NSMutableDictionary*)result
{
    NSNumber *boolNumber = [NSNumber numberWithBool:rewardedVideoSingleton.isReady];
    [result setValue:boolNumber forKey:@"RetValue"];
}

@end


