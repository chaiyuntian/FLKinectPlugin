using System;
using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class FLKinectPlugin : ModuleRules
	{
		public FLKinectPlugin(TargetInfo Target)
		{

            string KinectPathEnvVar = "%KINECTSDK20_DIR%";
            string ExpandedKinectEnvVar = Environment.ExpandEnvironmentVariables(KinectPathEnvVar);

            //NOTE (OS): Safety check for comptuers that don't have the kinect plugin
            if (KinectPathEnvVar == ExpandedKinectEnvVar)
            {
                var err = "ERROR : Environment variable {0} does not exist in this Windows environment. Check if the Kinect for Windows 2.0 plugin is installed.";
                Console.WriteLine(err, KinectPathEnvVar);
                throw new Exception(err);
            }


            string ThirdPartyKinectIncludePath = Path.Combine(ExpandedKinectEnvVar, "inc");

            string PlatformSpec = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string ThirdPartyKinectLibPath = Path.Combine(ExpandedKinectEnvVar, "Lib", PlatformSpec);

            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyKinectLibPath, "Kinect20.lib"));

            PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Developer/FLKinectPlugin/Private",
                    ThirdPartyKinectIncludePath
					// ... add other private include paths required here ...
				}
				);

            
            

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Engine",
                    // ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}