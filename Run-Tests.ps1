$sharpmakecs = "$PSScriptRoot/tests/sharpmake.cs".Replace('\', '/')
& "$PSScriptRoot/tools/Sharpmake/Sharpmake.Application/bin/Release/net6.0/Sharpmake.Application.exe" "/sources('$sharpmakecs')"

Push-Location -Path "$PSScriptRoot/tests/generated"

if (Test-Path "./output") {
	Remove-Item "./output" -Force -Recurse
}

Start-Job -ScriptBlock {
	$PSScriptRoot = "$using:PSScriptRoot"
	& "$PSScriptRoot/tools/Launch-VsDevShell.ps1" -Lates
	$slnlist = Get-ChildItem "$PSScriptRoot/tests/generated/" -Filter "*.sln" -Recurse
	foreach ($sln in $slnlist) {
		msbuild -t:rebuild -restore $sln.FullName /nologo /verbosity:m /p:Configuration="Release" /maxcpucount
	}

} | Receive-Job -Wait -AutoRemoveJob

Push-Location -Path "./output"
$exelist = Get-ChildItem "./" -Filter "*.exe" -Recurse
foreach ($exe in $exelist) {
	& $exe.FullName
}
Pop-Location

Pop-Location