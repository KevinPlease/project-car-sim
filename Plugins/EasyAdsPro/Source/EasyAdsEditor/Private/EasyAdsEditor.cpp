// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EasyAdsEditor.h"
#include "AdmobSetting.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "PropertyEditorModule.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FEasyAdsEditorModule"

DEFINE_LOG_CATEGORY_STATIC(EasyAdsEditor, Log, All);

void FEasyAdsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings(TEXT("Project"), TEXT("EasyAds"), TEXT("Admob"),
			LOCTEXT("Admob", "Admob"),
			LOCTEXT("Admob", "Settings for Admob"),
			GetMutableDefault<UAdmobSetting>()
		);

	}
	
	const FString& EnginePath = FPaths::EngineDir();
	FString GameActivityTemplatePath = EnginePath / TEXT("Build/Android/Java/src/com/epicgames/ue4/GameActivity.java.template");
	
	FString Result;
	if (FFileHelper::LoadFileToString(Result, *GameActivityTemplatePath) )
	{
		Result = Result.Replace(TEXT("android.support.v4"), TEXT("androidx.core"));

		// check if we use engine plugin
		FString EnginePluginTemplatePath = FPaths::EnginePluginsDir() / TEXT("Marketplace/EasyAdsPro/Source/ThirdParty/Android/GameActivity.java.template");
		if (IFileManager::Get().FileExists(*EnginePluginTemplatePath))
		{
			FFileHelper::SaveStringToFile(Result, *EnginePluginTemplatePath);
		}

		// check if we use project plugin
		FString ProjectPluginTemplatePath = FPaths::ProjectPluginsDir() / TEXT("EasyAdsPro/Source/ThirdParty/Android/GameActivity.java.template");
		if (IFileManager::Get().FileExists(*ProjectPluginTemplatePath))
		{
			FFileHelper::SaveStringToFile(Result, *ProjectPluginTemplatePath);
		}
	}
}

void FEasyAdsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyAdsEditorModule, EasyAdsEditor)