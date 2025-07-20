# Using Start-Job to limit scope of VsDevShell.
Start-Job -ScriptBlock {
	$PSScriptRoot = "$using:PSScriptRoot"
	& "$PSScriptRoot/tools/Launch-VsDevShell.ps1" -Latest

	Push-Location -Path $PSScriptRoot

	Push-Location -Path $PSScriptRoot/tools
	git submodule update --init --recursive

	# Prepare Sharpmake
	if (Test-Path "./Sharpmake/Sharpmake.Application/bin") {
		Remove-Item "./Sharpmake/Sharpmake.Application/bin" -Force -Recurse
	}
	dotnet build "./Sharpmake/Sharpmake.sln" -c "Release" --nologo

	# Prepare Catch2
	# if (Test-Path "./Catch2_build") {
	# 	Remove-Item "./Catch2_build" -Force -Recurse
	# }
	# New-Item -Name "Catch2_build" -ItemType "Directory"
	# Push-Location -Path "./Catch2_build"
	# cmake "../Catch2/"
	# Pop-Location
	Pop-Location
} | Receive-Job -Wait -AutoRemoveJob