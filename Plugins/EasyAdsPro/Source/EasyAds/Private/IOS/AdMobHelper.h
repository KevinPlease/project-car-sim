//
//  AdMobHelper.h
//  AdsUtil
//
//  Created by Xufei Wu on 2017/6/28.
//  Copyright © 2017年 Xufei Wu. All rights reserved.
//

#ifndef AdMobHelper_h
#define AdMobHelper_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <GoogleMobileAds/GoogleMobileAds.h>
#import <PersonalizedAdConsent/PersonalizedAdConsent.h>
@interface AdMobHelper : NSObject

+ (AdMobHelper*) GetDelegate;
- (void) InitSDK:(UIViewController*) viewController AppID:(NSString*)AppID  testDevice:(NSArray<NSString *> *)testDevice BannerUnit:(NSString*)BannerUnit InterstitalUnit:(NSString*)InterstitalUnit RewardedUnit:(NSString*)RewardedUnit callback:(void(*)(NSString* strType, int aomount)) callback rewardClose:(void(*)(void)) rewardClose interstitialShow:(void(*)(void)) interstitialShow  interstitialClick:(void(*)(void)) interstitialClick interstitialClose:(void(*)(void)) interstitialClose rcvDebugMessage: (void(*)(NSString* debugMessage)) rcvDebugMessage
    customInterstitialLoadResult:(void(*)(NSString* adUnit, bool isSuccess, NSString* errmsg)) customInterstitialLoadResult
    customRewardedVideoLoadResult:(void(*)(NSString* adUnit, bool isSuccess, NSString* errmsg)) customRewardedVideoLoadResult
    customInterstitialClick:(void(*)(NSString* adUnit)) customInterstitialClick
    customInterstitialShow:(void(*)(NSString* adUnit)) customInterstitialShow
    customInterstitialClose:(void(*)(NSString* adUnit)) customInterstitialClose
    customRewardedComplete:(void(*)(NSString* adUnit, NSString* type, int amount)) customRewardedComplete
    customRewardedClos:(void(*)(NSString* adUnit)) customRewardedClos
customRewardedFail:(void(*)(NSString* adUnit, NSString* errmsg)) customRewardedFail
userConfirmConsent:(void(*)(int status, bool preferAdsFree)) userConfirmConsent
consentInfoUpdate:(void(*)(NSString* publisherId, bool success, int status)) consentInfoUpdate;

-(void) ShowBanner:(UIViewController*) viewController isBottom:(BOOL)isBottom;
-(void) HideBanner;
-(void) IsBannerReady:(NSMutableDictionary*)result;
-(void) ShowInterstitialAds:(UIViewController*) viewController;
-(void) IsInterstitalReady:(NSMutableDictionary*)result;
-(void) Play:(UIViewController*) viewController;
-(void) IsPlayable:(NSMutableDictionary*)result;

-(void) LoadCustomInterstitial:(UIViewController*) viewController adUnit:(NSString*) adUnit;
-(void) IsCustomInterstitialReady:(NSMutableDictionary*) result;
-(void) ShowCustomInterstitialAd:(UIViewController*) viewController adUnit:(NSString*) adUnit;

-(void) LoadCustomRewardedVideo:(UIViewController*) viewController adUnit:(NSString*) adUnit;
-(void) IsCustomRewardReady:(NSMutableDictionary*) result;
-(void) PlayCustomRewardAd:(UIViewController*)viewController adUnit:(NSString*) adUnit;

-(void) RequestConsentInfoUpdate:(NSString*) publisherId;
-(int) ConsentStatusToInt:(PACConsentStatus) status;
-(PACConsentStatus) IntToConsentStatu:(int) status;
-(void)GetConsentStatus:(NSMutableDictionary*)result;
-(void)SetConsentStatus:(int) status;
-(void)IsLocationInEEA:(NSMutableDictionary*) result;
-(void)IsUseNonPersonalizedAds:(NSMutableDictionary*) result;
-(bool)UseNonPersonallziedAds;
-(void)SetTagForUnderAgeOfConsent:(bool) underAgeOfConsent;
-(void)RequestUserConfirmConsent:(UIViewController*)viewController privacyUrl: (NSString*)privacyUrl withAdsFreeOpt:(bool)withAdsFreeOpt;
-(void) AutoReloadReward;
-(void)ProcessGDPR:(GADRequest*) request;
-(void)IsSdkInitlized:(NSMutableDictionary*)result;

@end

#endif /* AdMobHelper_h */
