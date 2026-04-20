& "./tools/Generate-Sharpmake.ps1" -TagName 1.3.0 -Params "/sources('./tests/sharpmake.cs')"

if ($LASTEXITCODE -ne 0) {
	Exit($LASTEXITCODE)
}

if (Test-Path "./output") {
	Remove-Item "./output" -Force -Recurse
}

& "./tools/Launch-VsDevShell.ps1" -Lates
# Launching VsDevShell loses the working directory, so set it back to the script location.
Push-Location -Path $PSScriptRoot
$slnlist = Get-ChildItem "./build/" -Filter "*.sln"
foreach ($sln in $slnlist) {
	msbuild $sln.FullName /verbosity:m /p:Configuration="Release" /maxcpucount
}

$exelist = Get-ChildItem "./build/output" -Filter "*.exe" -Recurse
foreach ($exe in $exelist) {
	& $exe.FullName
}