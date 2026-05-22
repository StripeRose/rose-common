using Sharpmake;
using System;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Threading.Tasks;

[module: Include("Util.sharpmake.cs")]

// Todo: Can be run in parallel and must sync up so multiple threads don't try to get the same external dependency.
// Only one copy of any given repository state should exist on disk.
public static class ExternalProject
{
	// Reference: https://gitlab.kitware.com/cmake/cmake/-/commit/670e16af2d76d5a75ed03b895562ac5923fdda56

	private static string DependenciesPath => $"{Util.BuildPath}/dependencies";

	public static string Git(string Name, string Repository, string Tag)
	{
		if (string.IsNullOrEmpty(Name))
		{
			Console.WriteLine("Repository Name must not be null or empty.");
			return null;
		}

		if (string.IsNullOrEmpty(Repository))
		{
			Console.WriteLine("Git Repository must not be null or empty.");
			return null;
		}

		if (string.IsNullOrEmpty(Tag))
		{
			Console.WriteLine("Git Tag must not be null or empty.");
			return null;
		}

		string sourceDirectory = $"{DependenciesPath}/{Name}_{Tag}";

		if (Directory.Exists(sourceDirectory))
		{
			if (ExecuteGit(Name, sourceDirectory, "fetch") &&
				ExecuteGit(Name, sourceDirectory, $"-c advice.detachedHead=false checkout {Tag}") &&
				ExecuteGit(Name, sourceDirectory, "submodule update --recursive")
				)
				return sourceDirectory;
		}
		else
		{
			if (ExecuteGit(Name, DependenciesPath, $"clone \"{Repository}\" \"{sourceDirectory}\"") &&
				ExecuteGit(Name, sourceDirectory, $"checkout {Tag}") &&
				ExecuteGit(Name, sourceDirectory, "submodule update --init --recursive")
				)
				return sourceDirectory;
		}

		return null;
	}

	private static ProcessStartInfo GetGitProcessInfo(string aWorkingDirectory, string someGitArguments)
	{
		return new ProcessStartInfo
		{
			FileName = "git",
			UseShellExecute = false,
			WorkingDirectory = aWorkingDirectory,
			Arguments = someGitArguments
		};
	}

	private static bool ExecuteGit(string aName, string aWorkingDirectory, string someArguments)
	{
		Console.WriteLine($"[Git] {aName} {someArguments}");

		try
		{
			if (!Directory.Exists(aWorkingDirectory))
				Directory.CreateDirectory(aWorkingDirectory);

			ProcessStartInfo startInfo = GetGitProcessInfo(aWorkingDirectory, someArguments);
			using var process = new Process { StartInfo = startInfo };
			process.Start();
			process.WaitForExit();
			return process.ExitCode == 0;
		}
		catch (Exception ex)
		{
			throw new ApplicationException($"Failed to execute git command \"{someArguments}\"", ex);
		}
	}

	public static string NuGet(string Name, string Version)
	{
		string nupkgPath = $"{DependenciesPath}/{Name}_{Version}.nupkg";
		string sourceDirectory = $"{DependenciesPath}/{Name}_{Version}";

		if (Directory.Exists(sourceDirectory))
			return sourceDirectory;

		Directory.CreateDirectory(sourceDirectory);

		Console.WriteLine($"Downloading {Name} {Version}..");
		var task = Task.Run(async () =>
		{
			using (System.Net.Http.HttpClient client = new System.Net.Http.HttpClient())
			{
				try
				{
					string url = $"https://www.nuget.org/api/v2/package/{Name}/{Version}";
					byte[] fileBytes = await client.GetByteArrayAsync(url);
					await File.WriteAllBytesAsync(nupkgPath, fileBytes);
					return true;
				}
				catch (Exception ex)
				{
					Console.WriteLine("Error: " + ex.Message);
					return false;
				}
			}
		});

		task.Wait();

		if (!task.Result)
			return "";
		
		ZipFile.ExtractToDirectory(nupkgPath, sourceDirectory);

		return sourceDirectory;
	}
}