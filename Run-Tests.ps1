$sharpmakecs = "$PSScriptRoot/tests/sharpmake.cs".Replace('\', '/')
& "$PSScriptRoot/tools/Generate-Sharpmake.ps1" -TagName 1.3.0 -Params "/sources('$sharpmakecs')"

if ($LASTEXITCODE -ne 0) {
	Exit($LASTEXITCODE)
}

Push-Location -Path "$PSScriptRoot/build"

if (Test-Path "./output") {
	Remove-Item "./output" -Force -Recurse
}

Start-Job -ScriptBlock {
	$PSScriptRoot = "$using:PSScriptRoot"
	& "$PSScriptRoot/tools/Launch-VsDevShell.ps1" -Lates
	$slnlist = Get-ChildItem "$PSScriptRoot/build/" -Filter "*.sln" -Recurse
	foreach ($sln in $slnlist) {
		msbuild -restore $sln.FullName /nologo /verbosity:m /p:Configuration="Release" /maxcpucount
	}

} | Receive-Job -Wait -AutoRemoveJob

Push-Location -Path "./output"
$exelist = Get-ChildItem "./" -Filter "*.exe" -Recurse
foreach ($exe in $exelist) {
	& $exe.FullName
}
Pop-Location
Pop-Location