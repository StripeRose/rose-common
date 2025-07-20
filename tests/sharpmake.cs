using System.IO;
using Sharpmake;

public static class Settings
{
	public static bool UseAmalgamatedCatch2 = true;

	public static Platform GetDefaultPlatform()
	{
		switch (Util.GetExecutingPlatform())
		{
			case Platform.win32:
				return Platform.win32;
			case Platform.win64:
				return Platform.win64;
			case Platform.mac:
				return Platform.mac;
			case Platform.linux:
				return Platform.linux;
			default:
				throw new System.NotSupportedException("Unknown platform.");
		}
	}

	public static DevEnv GetDefaultDevEnvs()
	{
		switch (Util.GetExecutingPlatform())
		{
			case Platform.win32:
			case Platform.win64:
				return DevEnv.vs2022;
			case Platform.mac:
				return DevEnv.xcode;
			case Platform.linux:
				return DevEnv.make;
			default:
				throw new System.NotSupportedException("Unknown platform.");
		}
	}
}

public class BasicProject : Project
{
	public BasicProject()
	{
		AddTargets(new Target(
			Settings.GetDefaultPlatform(),
			Settings.GetDefaultDevEnvs(),
			Optimization.Debug | Optimization.Release
		));
	}

	[Configure]
	public virtual void ConfigureAll(Configuration conf, Target target)
	{
		conf.Name = "[project.Name]_[target.Optimization]_[target.Platform]";

		conf.ProjectFileName = "[project.Name]_[target.DevEnv]_[target.Platform]";
		conf.ProjectPath = "[project.SharpmakeCsPath]/generated";

		conf.IntermediatePath = Path.Combine(conf.IntermediatePath, "[project.Name]");
		conf.TargetFileName = @"[conf.Name]";

		conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);

		conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.Latest);
		conf.Options.Add(Sharpmake.Options.Vc.Compiler.MultiProcessorCompilation.Enable);

		conf.Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Enable);

	}
}

[Generate]
public class Catch2 : BasicProject
{
	public Catch2()
	{
		Name = "Catch2";
		SourceRootPath = "[project.SharpmakeCsPath]/../tools/Catch2/src";
		AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]/../tools/Catch2_build/generated-includes/");
	}

	public override void ConfigureAll(Configuration conf, Target target)
	{
		base.ConfigureAll(conf, target);
		conf.Output = Sharpmake.Project.Configuration.OutputType.Lib;
		conf.Options.Add(Sharpmake.Options.Vc.General.WarningLevel.Level0);

		conf.IncludePaths.Add("[project.SourceRootPath]");
		conf.IncludePaths.Add("[project.SharpmakeCsPath]/../tools/Catch2_build/generated-includes/");
	}
}

[Generate]
public class RoseCommon : BasicProject
{
	public RoseCommon()
	{
		Name = "RoseCommon";
		SourceRootPath = "[project.SharpmakeCsPath]/../include/";
		AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]/../source");
	}

	public override void ConfigureAll(Configuration conf, Target target)
	{
		base.ConfigureAll(conf, target);
		conf.Output = Sharpmake.Project.Configuration.OutputType.Lib;

		conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
		conf.Options.Add(Sharpmake.Options.Vc.General.WarningLevel.Level4);

		conf.IncludePaths.Add("[project.SourceRootPath]");
	}
}

[Generate]
public class TestsExecutable : BasicProject
{
	public TestsExecutable()
	{
		Name = "Tests";
		SourceRootPath = "[project.SharpmakeCsPath]/";
		AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]/tests");
		if (Settings.UseAmalgamatedCatch2)
			AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]/../tools/Catch2/extras");
	}

	public override void ConfigureAll(Configuration conf, Target target)
	{
		base.ConfigureAll(conf, target);

		if (Settings.UseAmalgamatedCatch2)
			conf.IncludePaths.Add("[project.SharpmakeCsPath]/../tools/Catch2/extras");
		else
			conf.AddPrivateDependency<Catch2>(target);
		conf.AddPrivateDependency<RoseCommon>(target);
	}
}

[Generate]
public class TestsSolution : Solution
{
	public TestsSolution()
	{
		Name = "rosecommon_tests";

		AddTargets(new Target(
			Settings.GetDefaultPlatform(),
			Settings.GetDefaultDevEnvs(),
			Optimization.Debug | Optimization.Release
		));
	}

	[Configure]
	public void ConfigureAll(Solution.Configuration conf, Target target)
	{
		conf.SolutionFileName = "[solution.Name]_[target.DevEnv]_[target.Platform]";
		conf.SolutionPath = "[solution.SharpmakeCsPath]/generated";
		conf.AddProject<TestsExecutable>(target);
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