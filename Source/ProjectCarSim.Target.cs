

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectCarSimTarget : TargetRules
{
	public ProjectCarSimTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ProjectCarSim" } );
	}
}
