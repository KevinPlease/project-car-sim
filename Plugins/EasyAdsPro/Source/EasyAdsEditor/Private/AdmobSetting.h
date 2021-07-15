/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdmobSetting.generated.h"


UENUM(BlueprintType)
enum class Language :uint8
{
	aa = 0 UMETA(DisplayName = "aa"),
	ab = 1 UMETA(DisplayName = "ab"),
	ae = 2 UMETA(DisplayName = "ae"),
	af = 3 UMETA(DisplayName = "af"),
	ak = 4 UMETA(DisplayName = "ak"),
	am = 5 UMETA(DisplayName = "am"),
	an = 6 UMETA(DisplayName = "an"),
	ar = 7 UMETA(DisplayName = "ar"),
	as = 8 UMETA(DisplayName = "as"),
	av = 9 UMETA(DisplayName = "av"),
	ay = 10 UMETA(DisplayName = "ay"),
	az = 11 UMETA(DisplayName = "az"),
	ba = 12 UMETA(DisplayName = "ba"),
	be = 13 UMETA(DisplayName = "be"),
	bg = 14 UMETA(DisplayName = "bg"),
	bh = 15 UMETA(DisplayName = "bh"),
	bi = 16 UMETA(DisplayName = "bi"),
	bm = 17 UMETA(DisplayName = "bm"),
	bn = 18 UMETA(DisplayName = "bn"),
	bo = 19 UMETA(DisplayName = "bo"),
	br = 20 UMETA(DisplayName = "br"),
	bs = 21 UMETA(DisplayName = "bs"),
	ca = 22 UMETA(DisplayName = "ca"),
	ce = 23 UMETA(DisplayName = "ce"),
	ch = 24 UMETA(DisplayName = "ch"),
	co = 25 UMETA(DisplayName = "co"),
	cr = 26 UMETA(DisplayName = "cr"),
	cs = 27 UMETA(DisplayName = "cs"),
	cu = 28 UMETA(DisplayName = "cu"),
	cv = 29 UMETA(DisplayName = "cv"),
	cy = 30 UMETA(DisplayName = "cy"),
	da = 31 UMETA(DisplayName = "da"),
	de = 32 UMETA(DisplayName = "de"),
	dv = 33 UMETA(DisplayName = "dv"),
	dz = 34 UMETA(DisplayName = "dz"),
	ee = 35 UMETA(DisplayName = "ee"),
	el = 36 UMETA(DisplayName = "el"),
	en = 37 UMETA(DisplayName = "en"),
	eo = 38 UMETA(DisplayName = "eo"),
	es = 39 UMETA(DisplayName = "es"),
	et = 40 UMETA(DisplayName = "et"),
	eu = 41 UMETA(DisplayName = "eu"),
	fa = 42 UMETA(DisplayName = "fa"),
	ff = 43 UMETA(DisplayName = "ff"),
	fi = 44 UMETA(DisplayName = "fi"),
	fj = 45 UMETA(DisplayName = "fj"),
	fo = 46 UMETA(DisplayName = "fo"),
	fr = 47 UMETA(DisplayName = "fr"),
	fy = 48 UMETA(DisplayName = "fy"),
	ga = 49 UMETA(DisplayName = "ga"),
	gd = 50 UMETA(DisplayName = "gd"),
	gl = 51 UMETA(DisplayName = "gl"),
	gn = 52 UMETA(DisplayName = "gn"),
	gu = 53 UMETA(DisplayName = "gu"),
	gv = 54 UMETA(DisplayName = "gv"),
	ha = 55 UMETA(DisplayName = "ha"),
	he = 56 UMETA(DisplayName = "he"),
	hi = 57 UMETA(DisplayName = "hi"),
	ho = 58 UMETA(DisplayName = "ho"),
	hr = 59 UMETA(DisplayName = "hr"),
	ht = 60 UMETA(DisplayName = "ht"),
	hu = 61 UMETA(DisplayName = "hu"),
	hy = 62 UMETA(DisplayName = "hy"),
	hz = 63 UMETA(DisplayName = "hz"),
	ia = 64 UMETA(DisplayName = "ia"),
	id = 65 UMETA(DisplayName = "id"),
	ie = 66 UMETA(DisplayName = "ie"),
	ig = 67 UMETA(DisplayName = "ig"),
	ii = 68 UMETA(DisplayName = "ii"),
	ik = 69 UMETA(DisplayName = "ik"),
	io = 70 UMETA(DisplayName = "io"),
	is = 71 UMETA(DisplayName = "is"),
	it = 72 UMETA(DisplayName = "it"),
	iu = 73 UMETA(DisplayName = "iu"),
	ja = 74 UMETA(DisplayName = "ja"),
	jv = 75 UMETA(DisplayName = "jv"),
	ka = 76 UMETA(DisplayName = "ka"),
	kg = 77 UMETA(DisplayName = "kg"),
	ki = 78 UMETA(DisplayName = "ki"),
	kj = 79 UMETA(DisplayName = "kj"),
	kk = 80 UMETA(DisplayName = "kk"),
	kl = 81 UMETA(DisplayName = "kl"),
	km = 82 UMETA(DisplayName = "km"),
	kn = 83 UMETA(DisplayName = "kn"),
	ko = 84 UMETA(DisplayName = "ko"),
	kr = 85 UMETA(DisplayName = "kr"),
	ks = 86 UMETA(DisplayName = "ks"),
	ku = 87 UMETA(DisplayName = "ku"),
	kv = 88 UMETA(DisplayName = "kv"),
	kw = 89 UMETA(DisplayName = "kw"),
	ky = 90 UMETA(DisplayName = "ky"),
	la = 91 UMETA(DisplayName = "la"),
	lb = 92 UMETA(DisplayName = "lb"),
	lg = 93 UMETA(DisplayName = "lg"),
	li = 94 UMETA(DisplayName = "li"),
	ln = 95 UMETA(DisplayName = "ln"),
	lo = 96 UMETA(DisplayName = "lo"),
	lt = 97 UMETA(DisplayName = "lt"),
	lu = 98 UMETA(DisplayName = "lu"),
	lv = 99 UMETA(DisplayName = "lv"),
	mg = 100 UMETA(DisplayName = "mg"),
	mh = 101 UMETA(DisplayName = "mh"),
	mi = 102 UMETA(DisplayName = "mi"),
	mk = 103 UMETA(DisplayName = "mk"),
	ml = 104 UMETA(DisplayName = "ml"),
	mn = 105 UMETA(DisplayName = "mn"),
	mr = 106 UMETA(DisplayName = "mr"),
	ms = 107 UMETA(DisplayName = "ms"),
	mt = 108 UMETA(DisplayName = "mt"),
	my = 109 UMETA(DisplayName = "my"),
	na = 110 UMETA(DisplayName = "na"),
	nb = 111 UMETA(DisplayName = "nb"),
	nd = 112 UMETA(DisplayName = "nd"),
	ne = 113 UMETA(DisplayName = "ne"),
	ng = 114 UMETA(DisplayName = "ng"),
	nl = 115 UMETA(DisplayName = "nl"),
	nn = 116 UMETA(DisplayName = "nn"),
	no = 117 UMETA(DisplayName = "no"),
	nr = 118 UMETA(DisplayName = "nr"),
	nv = 119 UMETA(DisplayName = "nv"),
	ny = 120 UMETA(DisplayName = "ny"),
	oc = 121 UMETA(DisplayName = "oc"),
	oj = 122 UMETA(DisplayName = "oj"),
	om = 123 UMETA(DisplayName = "om"),
	os = 125 UMETA(DisplayName = "os"),
	pa = 126 UMETA(DisplayName = "pa"),
	pi = 127 UMETA(DisplayName = "pi"),
	pl = 128 UMETA(DisplayName = "pl"),
	ps = 129 UMETA(DisplayName = "ps"),
	pt = 130 UMETA(DisplayName = "pt"),
	qu = 131 UMETA(DisplayName = "qu"),
	rm = 132 UMETA(DisplayName = "rm"),
	rn = 133 UMETA(DisplayName = "rn"),
	ro = 134 UMETA(DisplayName = "ro"),
	ru = 135 UMETA(DisplayName = "ru"),
	rw = 136 UMETA(DisplayName = "rw"),
	sa = 137 UMETA(DisplayName = "sa"),
	sc = 138 UMETA(DisplayName = "sc"),
	sd = 139 UMETA(DisplayName = "sd"),
	se = 140 UMETA(DisplayName = "se"),
	sg = 141 UMETA(DisplayName = "sg"),
	si = 142 UMETA(DisplayName = "si"),
	sk = 143 UMETA(DisplayName = "sk"),
	sl = 144 UMETA(DisplayName = "sl"),
	sm = 145 UMETA(DisplayName = "sm"),
	sn = 146 UMETA(DisplayName = "sn"),
	so = 147 UMETA(DisplayName = "so"),
	sq = 148 UMETA(DisplayName = "sq"),
	sr = 149 UMETA(DisplayName = "sr"),
	ss = 150 UMETA(DisplayName = "ss"),
	st = 151 UMETA(DisplayName = "st"),
	su = 152 UMETA(DisplayName = "su"),
	sv = 153 UMETA(DisplayName = "sv"),
	sw = 154 UMETA(DisplayName = "sw"),
	ta = 155 UMETA(DisplayName = "ta"),
	te = 156 UMETA(DisplayName = "te"),
	tg = 157 UMETA(DisplayName = "tg"),
	th = 158 UMETA(DisplayName = "th"),
	ti = 159 UMETA(DisplayName = "ti"),
	tk = 160 UMETA(DisplayName = "tk"),
	tl = 161 UMETA(DisplayName = "tl"),
	tn = 162 UMETA(DisplayName = "tn"),
	to = 163 UMETA(DisplayName = "to"),
	tr = 164 UMETA(DisplayName = "tr"),
	ts = 165 UMETA(DisplayName = "ts"),
	tt = 166 UMETA(DisplayName = "tt"),
	tw = 167 UMETA(DisplayName = "tw"),
	ty = 168 UMETA(DisplayName = "ty"),
	ug = 169 UMETA(DisplayName = "ug"),
	uk = 170 UMETA(DisplayName = "uk"),
	ur = 171 UMETA(DisplayName = "ur"),
	uz = 172 UMETA(DisplayName = "uz"),
	ve = 173 UMETA(DisplayName = "ve"),
	vi = 174 UMETA(DisplayName = "vi"),
	vo = 175 UMETA(DisplayName = "vo"),
	wa = 176 UMETA(DisplayName = "wa"),
	wo = 177 UMETA(DisplayName = "wo"),
	xh = 178 UMETA(DisplayName = "xh"),
	yi = 179 UMETA(DisplayName = "yi"),
	yo = 180 UMETA(DisplayName = "yo"),
	za = 181 UMETA(DisplayName = "za"),
	zh = 182 UMETA(DisplayName = "zh"),
	zu = 183 UMETA(DisplayName = "zu"),

};


USTRUCT(BlueprintType)
struct FTrackingDescription
{
	GENERATED_BODY()

	UPROPERTY(Category = TrackingDescription, EditAnywhere)
	Language language;
	
	UPROPERTY(Category = TrackingDescription, EditAnywhere)
	FString localizationDesctiption;
};

/**
 * 
 */
UCLASS(transient, config = Engine)
class UAdmobSetting : public UObject
{
	GENERATED_BODY()
	
public:

	UAdmobSetting();

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android AppID"))
	FString AndroidAppId;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android Banner AdUnit"))
	FString AndroidBannerUnit;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android Interstitial AdUnit"))
	FString AndroidInterstitialUnit;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android RewardVideo AdUnit"))
	FString AndroidRewardedVideoAdUnit;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android TestDevice"))
	TArray<FString> AndroidTestDeviceList;

	UPROPERTY(Config)
	FString AndroidResultTestDevice;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Enable Mediation TestSute", ToolTip = "this require minSdkVersion 16, else will package fail"))
	bool EnableAndroidTestSuite;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Disable Unity"))
	bool DisableAndroidUnity;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Disable Vungle"))
	bool DisableAndroidVungle;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Disable Chartboost"))
	bool DisableAndroidChartboost;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Disable Facebook"))
	bool DisableAndroidFacebook;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Disable Applovin"))
	bool DisableAndroidApplovin;



	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS AppID"))
	FString IOSAppId;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS Banner AdUnit"))
	FString IOSBannerUnit;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS Interstitial AdUnit"))
	FString IOSInterstitialUnit;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS RewardVideo AdUnit"))
	FString IOSRewardedVideoAdUnit;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS TestDevice"))
	TArray<FString> IOSTestDeviceList;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "TrackingUseageDescription"))
	TArray<FTrackingDescription> UserTrackingDescriptionList;


#if WITH_EDITOR
	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
