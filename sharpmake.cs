using Sharpmake;

[module: Include("tools/Util.sharpmake.cs")]

[Generate]
public class RoseCommon : Sharpmake.Project
{
	public static string MainNamespace = null;
	public static string MathNamespace = null;

	public RoseCommon()
	{
		Name = "rose-common";
		SourceRootPath = "[project.SharpmakeCsPath]/include";
		AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]/source");

		AddTargets(new Target(
			Platform.win32 | Platform.win64,
			Util.AllFlags<DevEnv>(),
			Util.AllFlags<Optimization>()
		));
	}

	[Configure]
	public virtual void ConfigureAll(Configuration conf, Target target)
	{
		conf.IncludePaths.Add("[project.SourceRootPath]");

		Util.SetDefaultBuildArguments(conf, target);

		if (MainNamespace != null)
		{
			conf.Defines.Add("ROSECOMMON_NAMESPACE=" + MainNamespace);
			conf.ExportDefines.Add("ROSECOMMON_NAMESPACE=" + MainNamespace);
		}

		if (MathNamespace != null)
		{
			conf.Defines.Add("ROSECOMMON_MATH_NAMESPACE=" + MathNamespace);
			conf.ExportDefines.Add("ROSECOMMON_MATH_NAMESPACE=" + MathNamespace);
		}

		conf.Output = Configuration.OutputType.Lib;
	}
}