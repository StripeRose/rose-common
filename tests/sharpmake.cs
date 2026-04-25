using Sharpmake;

[module: Include("../sharpmake.cs")]
[module: Include("../tools/ExternalProject.sharpmake.cs")]

namespace RoseCommonTest
{
	[Generate]
	public class Catch2 : Project
	{
		public Catch2()
		{
			Name = "Catch2";

			string repositoryPath = ExternalProject.Git(
				"Catch2",
				"https://github.com/catchorg/Catch2.git",
				"v3.14.0"
			);

			SourceRootPath = $"{repositoryPath}/src";

			AddTargets(new Target(
				Util.GetExecutingPlatform(),
				Util.AllFlags<DevEnv>(),
				Optimization.Debug | Optimization.Release
			));
		}

		[Configure]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.IncludePaths.Add("[project.SourceRootPath]");

			// Use premade Catch2 config, instead of needing CMake to generate one.
			conf.IncludePaths.Add("[project.SharpmakeCsPath]/../tools/catch2_config");

			Util.SetDefaultBuildArguments(conf, target);
			conf.Options.Add(Sharpmake.Options.Vc.General.WarningLevel.Level0); // Don't care about any Catch2 issues.

			conf.ProjectFileName = "[project.Name] [target.Platform] [target.DevEnv]";
			conf.ProjectPath = Util.BuildPath;
		}
	}

	[Generate]
	public class TestsExecutable : Project
	{
		public TestsExecutable()
		{
			Name = "rose-common-tests";
			SourceRootPath = "[project.SharpmakeCsPath]";

			AddTargets(new Target(
				Util.GetExecutingPlatform(),
				Util.AllFlags<DevEnv>(),
				Optimization.Debug | Optimization.Release
			));
		}
		
		[Configure]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.IncludePaths.Add("[project.SourceRootPath]");
			
			conf.AddPrivateDependency<Catch2>(target);
			conf.AddPrivateDependency<RoseCommon>(target);

			Util.SetDefaultBuildArguments(conf, target);

			conf.Output = Sharpmake.Project.Configuration.OutputType.Exe;
		}
	}

	[Generate]
	public class TestsSolution : Solution
	{
		public TestsSolution()
		{
			Name = "rose-common-tests";

			AddTargets(new Target(
				Util.GetExecutingPlatform(),
				DevEnv.vs2022,
				Optimization.Debug | Optimization.Release
			));
		}

		[Configure]
		public void ConfigureAll(Solution.Configuration conf, Target target)
		{
			conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);

			conf.AddProject<TestsExecutable>(target);
			
			Util.SetDefaultBuildArguments(conf, target);
		}
	}

	public static class Main
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Arguments someArguments)
		{
			someArguments.Generate<TestsSolution>();
		}
	}
}