using Sharpmake;

[module: Include("tools/Util.sharpmake.cs")]

[Generate]
public class RoseCommon : Sharpmake.Project
{
	public RoseCommon()
	{
		Name = "rose-common";
		SourceRootPath = "[project.SharpmakeCsPath]/include";
		AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]/source");

		AddTargets(new Target(
			Util.GetExecutingPlatform(),
			Util.AllFlags<DevEnv>(),
			Util.AllFlags<Optimization>()
		));
	}

	[Configure]
	public virtual void ConfigureAll(Configuration conf, Target target)
	{
		conf.IncludePaths.Add("[project.SourceRootPath]");

		Util.SetDefaultBuildArguments(conf, target);

		conf.Output = Configuration.OutputType.Lib;
	}
}