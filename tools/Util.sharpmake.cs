using System;
using System.Collections.Generic;
using System.IO;
using Sharpmake;

public static partial class Util
{
	public static bool IsObsolete(Enum value)
	{
		var enumType = value.GetType();
		var enumName = enumType.GetEnumName(value);
		var fieldInfo = enumType.GetField(enumName);
		return Attribute.IsDefined(fieldInfo, typeof(ObsoleteAttribute));
	}

	public static T AllFlags<T>() where T : struct, Enum
	{
		var validFlags = new List<string>();

		foreach (var value in Enum.GetValues<T>())
		{
			if (!IsObsolete(value))
				validFlags.Add(value.ToString());
		}

		string str = string.Join(", ", validFlags);

		if (Enum.TryParse<T>(str, out var e))
			return e;

		return default;
	}

	public static Platform GetExecutingPlatform() => Sharpmake.Util.GetExecutingPlatform();

	public static string RootPath => System.IO.Directory.GetCurrentDirectory();
	public static string BuildPath => $"{RootPath}/build";
	public static string OutputPath => $"{BuildPath}/output";

	public static void SetDefaultBuildArguments(Project.Configuration conf, Target target)
	{
		conf.IncludePaths.Add("[project.SourceRootPath]");
		
		conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.Latest);
		conf.Options.Add(Options.Vc.Compiler.Exceptions.Enable);
		conf.Options.Add(Options.Vc.Compiler.MultiProcessorCompilation.Enable);
		//conf.Options.Add(Options.Vc.Compiler.RTTI.Enable);
		conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
		conf.Options.Add(Options.Vc.General.WarningLevel.Level4);
		conf.Options.Add(Options.Vc.General.WindowsTargetPlatformVersion.Latest);

		conf.ProjectPath = "[project.SharpmakeCsPath]";
		conf.ProjectFileName = "[project.Name] [target.Platform] [target.DevEnv]";

		conf.IntermediatePath = $"{BuildPath}/intermediate/{conf.ProjectFileName}";
		conf.TargetPath = OutputPath;
		conf.TargetLibraryPath = $"{BuildPath}/lib";
		conf.TargetFileName = "[project.Name] [target.Optimization] [target.DevEnv]";

		conf.Output = Project.Configuration.OutputType.Lib;
	}

	public static void SetDefaultBuildArguments(Solution.Configuration conf, Target target)
	{
		conf.SolutionFileName = "[solution.Name] [target.DevEnv]";
		conf.SolutionPath = RootPath;
	}

	public static bool ResolveFilterPathForFile(string aFilePath, out string outFilterPath)
	{
		string commentStartString = "//";
		string filterIdentifierString = "Filter";
		string openFilterString = "\"";
		string closeFilterString = "\"";

		IEnumerable<string> fileLines = File.ReadLines(aFilePath);
		foreach (string line in fileLines)
		{
			if (string.IsNullOrWhiteSpace(line))
				continue;

			int commentStartIndex = line.IndexOf(commentStartString);
			if (commentStartIndex == -1) continue; // Skip lines without comments.

			string comment = line.Substring(commentStartIndex + commentStartString.Length);
			int filterIdentifier = comment.IndexOf(filterIdentifierString, System.StringComparison.CurrentCultureIgnoreCase);
			if (filterIdentifier == -1) break;

			int openFilterIndex = comment.IndexOf(openFilterString, filterIdentifier + filterIdentifierString.Length);
			if (openFilterIndex == -1) break;

			int closeFilterIndex = comment.IndexOf(closeFilterString, openFilterIndex + openFilterString.Length);
			if (closeFilterIndex == -1) break;

			int filterNameStart = openFilterIndex + openFilterString.Length;
			int filterNameLength = closeFilterIndex - filterNameStart;
			outFilterPath = comment.Substring(filterNameStart, filterNameLength).Replace("/", "\\");
			return true;
		}

		outFilterPath = null;
		return false;
	}
}