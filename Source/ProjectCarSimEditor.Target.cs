

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectCarSimEditorTarget : TargetRules
{
	public ProjectCarSimEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ProjectCarSim" } );
	}
}
