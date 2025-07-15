:: Batch arguments
:: %~1: sharpmake.cs file to generate.

pushd "%~dp0"
if not exist "%~dp0Sharpmake\Sharpmake.Application" (
	git submodule init .\Sharpmake\

	if %errorlevel% NEQ 0 (
		echo.
		echo Error: Failed to get Sharpmake.
		pause
		exit /b %errorlevel%
	)
)
git submodule update .\Sharpmake\
popd

if not exist "%~dp0Sharpmake\Sharpmake.Application\bin\Release\net6.0\Sharpmake.Application.exe" (
	call "%~dp0compile_msbuild.bat" "%~dp0Sharpmake\Sharpmake.sln" "Release"
	if %errorlevel% NEQ 0 (
		echo.
		echo Error: Failed to build Sharpmake.
		pause
		exit /b %errorlevel%
	)
)

:: Sharpmake isn't happy with back-slashes, so we just replace them here.
set "path=%~1"
set "sanitizedPath=%path:\=/%"
"%~dp0Sharpmake\Sharpmake.Application\bin\Release\net6.0\Sharpmake.Application.exe" "/sources('%sanitizedPath%')"
