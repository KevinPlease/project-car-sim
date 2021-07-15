/*
* EasyAds Pro - unreal engine 4 ads plugin
*
* Copyright (C) 2019 feixuwu <feixuwu@outlook.com> All Rights Reserved.
*/

#include "AdmobSetting.h"
#include "Misc/ConfigCacheIni.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "PropertyEditorModule.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"


static FString GetLanguageName(Language l)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("Language"), true);
	if (!EnumPtr)
	{
		return TEXT("");
	}

	FString EnumName = EnumPtr->GetNameByValue((int64)l).ToString();

	FString Result;
	int32 ScopeIndex = EnumName.Find(TEXT("::"), ESearchCase::CaseSensitive);
	if (ScopeIndex != INDEX_NONE)
	{
		Result = EnumName.Mid(ScopeIndex + 2);
	}
	else
	{
		Result = EnumName;
	}

	return Result;
}

UAdmobSetting::UAdmobSetting() :EnableAndroidTestSuite(true), DisableAndroidUnity(false), DisableAndroidVungle(false), DisableAndroidChartboost(false), 
DisableAndroidFacebook(false), DisableAndroidApplovin(false)
{
	FTrackingDescription enDescription;
	enDescription.language = Language::en;
	enDescription.localizationDesctiption = TEXT("This identifier will be used to deliver personalized ads to you in this game.");
	UserTrackingDescriptionList.Add(enDescription);
}

#if WITH_EDITOR
void UAdmobSetting::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	AndroidResultTestDevice = "";
	for (size_t i = 0; i < AndroidTestDeviceList.Num(); i++)
	{
		if (AndroidResultTestDevice.Len() == 0)
		{
			AndroidResultTestDevice = AndroidTestDeviceList[i];
		}
		else
		{
			AndroidResultTestDevice += FString(",") + AndroidTestDeviceList[i];
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
	SaveConfig(CPF_Config, *GetDefaultConfigFilename());

	if (EnableAndroidTestSuite)
	{
		const TCHAR* AndroidSettings = TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings");

		FString configPath = FString::Printf(TEXT("%sDefaultEngine.ini"), *FPaths::SourceConfigDir());

		int curVersion = 0;
		if (GConfig->GetInt(AndroidSettings, TEXT("MinSDKVersion"), curVersion, configPath))
		{
			if (curVersion < 19)
			{
				GConfig->SetInt(AndroidSettings, TEXT("MinSDKVersion"), 19, configPath);
			}
		}
	}

	bool existEnginePlugin = false;
	bool existProjectPlugin = false;

	FString EnginePluginEnPath = FPaths::EnginePluginsDir() / TEXT("Marketplace/EasyAdsPro/Source/ThirdParty/TrackingLocalize/Resources/Localizations/en.lproj/InfoPlist.strings");
	FString ProjectPluginEnPath = FPaths::ProjectPluginsDir() / TEXT("EasyAdsPro/Source/ThirdParty/TrackingLocalize/Resources/Localizations/en.lproj/InfoPlist.strings");
	existEnginePlugin = IFileManager::Get().FileExists(*EnginePluginEnPath);
	existProjectPlugin = IFileManager::Get().FileExists(*ProjectPluginEnPath);


	TMap<Language, FString> languageMap;
	for (int32 i = 0; i < UserTrackingDescriptionList.Num(); i++)
	{
		FTrackingDescription tmp = UserTrackingDescriptionList[i];
		if (tmp.localizationDesctiption.Len() == 0 || languageMap.Find(tmp.language) != nullptr)
		{
			continue;
		}

		FString strLanguage = GetLanguageName(tmp.language);
		if (strLanguage.Len() == 0)
		{
			continue;
		}
		languageMap.Add(tmp.language, tmp.localizationDesctiption);

		if (existEnginePlugin)
		{
			FString EnginePluginTemplatePath = FPaths::EnginePluginsDir() / TEXT("Marketplace/EasyAdsPro/Source/ThirdParty/TrackingLocalize/Resources/Localizations") / (strLanguage + TEXT(".lproj")) / TEXT("InfoPlist.strings");

			FString strContent = "\"NSUserTrackingUsageDescription\" = \"" + tmp.localizationDesctiption + "\";";
			FFileHelper::SaveStringToFile(strContent, *EnginePluginTemplatePath);
		}

		// check if we use project plugin
		if (existProjectPlugin)
		{
			FString ProjectPluginTemplatePath = FPaths::ProjectPluginsDir() / TEXT("EasyAdsPro/Source/ThirdParty/TrackingLocalize/Resources/Localizations") / (strLanguage + TEXT(".lproj")) / TEXT("InfoPlist.strings");
			FString strContent = "\"NSUserTrackingUsageDescription\" = \"" + tmp.localizationDesctiption + "\";";
			FFileHelper::SaveStringToFile(strContent, *ProjectPluginTemplatePath);
		}
	}
}


#endif