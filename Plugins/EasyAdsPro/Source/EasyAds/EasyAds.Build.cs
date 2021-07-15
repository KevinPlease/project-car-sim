// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using Tools.DotNETCommon;
using System.IO;

public class EasyAds : ModuleRules
{
	public EasyAds(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Public/EasyAds.h";

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);


        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            //PrivateIncludePaths.Add("Private/Windows");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("Launch");
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "EasyAds_UPL.xml"));
        }
        else if(Target.Platform == UnrealTargetPlatform.IOS)
        {
            // to enable ios 14 support, uncomment this line
            PublicDefinitions.Add("WITH_IOS14_SUPPORT=1");
            ProjectDescriptor projectDescriptor = null;
            if(Target.ProjectFile != null)
            {
                projectDescriptor = ProjectDescriptor.FromFile(Target.ProjectFile);
            }
            
            System.Console.WriteLine("Engine Directory:" + EngineDirectory);
            List<PluginInfo> pluginList = new List<PluginInfo>();
            pluginList.AddRange(global::UnrealBuildTool.Plugins.ReadEnginePlugins(new DirectoryReference(EngineDirectory) ) );

            if (Target.ProjectFile != null)
            {
                System.Console.WriteLine("Project Directory:" + Target.ProjectFile.Directory);
                pluginList.AddRange(global::UnrealBuildTool.Plugins.ReadEnginePlugins(Target.ProjectFile.Directory));
            }
            
            List<string> fbrelationPluginList = new List<string>();
            fbrelationPluginList.AddRange(new string[]{"",
                "EasyFirebasePro",
                "OnlineSubsystemFacebook"
            });
            
            bool exsitEasyFirebase = false;
            bool existOnlineFacebook = false;
            foreach (PluginInfo plugin in pluginList)
            {
                if(!fbrelationPluginList.Contains(plugin.Name) )
                {
                    continue;
                }

                if(global::UnrealBuildTool.Plugins.IsPluginEnabledForTarget(plugin, projectDescriptor, Target.Platform, Target.Configuration, Target.Type) )
                {
                    if(plugin.Name.Contains("EasyFirebasePro") )
                    {
                        exsitEasyFirebase = true;
                    }

                    if (plugin.Name.Contains("OnlineSubsystemFacebook"))
                    {
                        existOnlineFacebook = true;
                    }

                    System.Console.WriteLine("Find Enabled Plugin:" + plugin.Name);
                }
            }

            // admob
            PublicAdditionalFrameworks.Add(
            new Framework(
            "GoogleMobileAds",														// Framework name
            "../ThirdParty/IOSFrameworks/GoogleMobileAds.embeddedframework.zip")
            );

            if (!exsitEasyFirebase)
            {
                PublicAdditionalFrameworks.Add(
                new Framework(
                "GoogleAppMeasurement",                                                      // Framework name
                "../ThirdParty/IOSFrameworks/GoogleAppMeasurement.embeddedframework.zip")
                );

                PublicAdditionalFrameworks.Add(
                new Framework(
                "GoogleUtilities",                                                      // Framework name
                "../ThirdParty/IOSFrameworks/GoogleUtilities.embeddedframework.zip")
                );

                PublicAdditionalFrameworks.Add(
                new Framework(
                "nanopb",                                                       // Framework name
                "../ThirdParty/IOSFrameworks/nanopb.embeddedframework.zip")
                );

                /*PublicAdditionalFrameworks.Add(
                new Framework(
                "PromisesObjC",                                                       // Framework name
                "../ThirdParty/IOSFrameworks/PromisesObjC.embeddedframework.zip")
                );*/

                PublicAdditionalFrameworks.Add(
                new Framework(
                "UserMessagingPlatform",                                                       // Framework name
                "../ThirdParty/IOSFrameworks/UserMessagingPlatform.embeddedframework.zip")
                );
            }

            // GDPR
            PublicAdditionalFrameworks.Add(
                new Framework(
                "PersonalizedAdConsent",                                                       // Framework name
                "../ThirdParty/IOSFrameworks/PersonalizedAdConsent.embeddedframework.zip",
                "PersonalizedAdConsent.framework/PersonalizedAdConsent.bundle")
                );

            // unity
            PublicAdditionalFrameworks.Add(
            new Framework(
            "UnityAds",														// Framework name
            "../ThirdParty/IOSFrameworks/UnityAds.embeddedframework.zip")
            );

            PublicAdditionalFrameworks.Add(
            new Framework(
            "UnityAdapter",														// Framework name
            "../ThirdParty/IOSFrameworks/UnityAdapter.embeddedframework.zip")
            );


            // chartboost
            /*PublicAdditionalFrameworks.Add(
            new Framework(
            "CHAMoatMobileAppKit",														// Framework name
            "../ThirdParty/Frameworks/CHAMoatMobileAppKit.embeddedframework.zip")
            );*/

            PublicAdditionalFrameworks.Add(
            new Framework(
            "Chartboost",														// Framework name
            "../ThirdParty/IOSFrameworks/Chartboost.embeddedframework.zip")
            );

            PublicAdditionalFrameworks.Add(
            new Framework(
            "ChartboostAdapter",														// Framework name
            "../ThirdParty/IOSFrameworks/ChartboostAdapter.embeddedframework.zip")
            );

            // vungle
            PublicAdditionalFrameworks.Add(
            new Framework(
            "VungleAdapter",														// Framework name
            "../ThirdParty/IOSFrameworks/VungleAdapter.embeddedframework.zip")
            );

            PublicAdditionalFrameworks.Add(
            new Framework(
            "VungleSDK",														// Framework name
            "../ThirdParty/IOSFrameworks/VungleSDK.embeddedframework.zip")
            );

            // facebook
            if (!exsitEasyFirebase)
            {
                if(!existOnlineFacebook)
                {
                    PublicAdditionalFrameworks.Add(
                    new Framework(
                    "FacebookAdapter",														// Framework name
                    "../ThirdParty/IOSFrameworks/FacebookAdapter.embeddedframework.zip")
                    );


                    PublicAdditionalFrameworks.Add(
                    new Framework(
                    "FBAudienceNetwork",                                                        // Framework name
                    "../ThirdParty/IOSFrameworks/FBAudienceNetwork.embeddedframework.zip")
                    );


                    PublicAdditionalFrameworks.Add(
                    new Framework(
                    "FBSDKCoreKit",                                                     // Framework name
                    "../ThirdParty/IOSFrameworks/FBSDKCoreKit.embeddedframework.zip")
                    );
                }
                

                PublicAdditionalFrameworks.Add(
                new Framework(
                "FBLPromises",                                                      // Framework name
                "../ThirdParty/IOSFrameworks/FBLPromises.embeddedframework.zip")
                );
            }

            // applovin
            PublicAdditionalFrameworks.Add(
            new Framework(
            "AppLovinSDK",														// Framework name
            "../ThirdParty/IOSFrameworks/AppLovinSDK.embeddedframework.zip")
            );

            PublicAdditionalFrameworks.Add(
            new Framework(
            "AppLovinAdapter",														// Framework name
            "../ThirdParty/IOSFrameworks/AppLovinAdapter.embeddedframework.zip")
            );

            // test suite
            PublicAdditionalFrameworks.Add(
            new Framework(
            "GoogleMobileAdsMediationTestSuite",														// Framework name
            "../ThirdParty/IOSFrameworks/GoogleMobileAdsMediationTestSuite.embeddedframework.zip", 
            "GoogleMobileAdsMediationTestSuite.framework/Resources/GoogleMobileAdsMediationTestSuite.bundle")
            );

            // MaterialComponents
            PublicAdditionalFrameworks.Add(
            new Framework(
            "MaterialComponents",														// Framework name
            "../ThirdParty/IOSFrameworks/MaterialComponents.embeddedframework.zip",
            "MaterialComponents.framework/MaterialTabs.bundle")
            );

            PublicAdditionalFrameworks.Add(
            new Framework(
            "MaterialComponents",														// Framework name
            "../ThirdParty/IOSFrameworks/MaterialComponents.embeddedframework.zip",
            "MaterialComponents.framework/MaterialIcons_ic_check_circle.bundle")
            );

            PublicAdditionalFrameworks.Add(
            new Framework(
            "MaterialComponents",														// Framework name
            "../ThirdParty/IOSFrameworks/MaterialComponents.embeddedframework.zip",
            "MaterialComponents.framework/MaterialDialogs.bundle")
            );

            // MDFInternationalization
            PublicAdditionalFrameworks.Add(
            new Framework(
            "MDFInternationalization",														// Framework name
            "../ThirdParty/IOSFrameworks/MDFInternationalization.embeddedframework.zip")
            );

            // MDFTextAccessibility
            PublicAdditionalFrameworks.Add(
            new Framework(
            "MDFTextAccessibility",														// Framework name
            "../ThirdParty/IOSFrameworks/MDFTextAccessibility.embeddedframework.zip")
            );


            PublicFrameworks.AddRange(
            new string[]
            {
            "EventKit",
            "CFNetwork",
            "GLKit",
            "MobileCoreServices",
            "SystemConfiguration",
            "MediaPlayer",
            "AdSupport",
            "CoreLocation",
            "MessageUI",
            "Security",
            "CoreTelephony",
            "AppTrackingTransparency",
            "Security",
            "StoreKit",
            "Foundation",
            "CoreGraphics",
            "WebKit",
            "AVFoundation",
            "UIKit",
            "Accelerate"
            }
            );


            {
                string PluginPathForFramework = Utils.MakePathRelativeTo(ModuleDirectory, "./");
                BundleResource source = new BundleResource(PluginPathForFramework + "/../ThirdParty/PersonalizedAdConsent.bundle", "");
                AdditionalBundleResources.Add(source);
            }

            {
                string PluginPathForFramework = Utils.MakePathRelativeTo(ModuleDirectory, "./");
                BundleResource source = new BundleResource(PluginPathForFramework + "/../ThirdParty/GoogleMobileAdsMediationTestSuite.bundle", "");
                AdditionalBundleResources.Add(source);
            }

            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "EasyAds_IOS_UPL.xml"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            //PrivateIncludePaths.Add("Private/Mac");
        }
        else
        {
            PrecompileForTargets = PrecompileTargetsType.None;
        }
    }
}
