@echo off

call "%~dp0tools\generate_sharpmake.bat" "%~dp0tests\sharpmake.cs"

pushd "%~dp0tests\generated"

rmdir /S /Q "output"

for %%f in (*.sln) do (
	call "%~dp0tools\compile_msbuild.bat" %~dp0tests\generated\%%f "Release"
	if %errorlevel% NEQ 0 (
		exit /b %errorlevel%
	)
)
pushd "output"
call :run_exes
popd
popd
exit /b 0

::::::::::::::::::::::::::::::::::
:: Run all exes in the current and sub-directories
::::::::::::::::::::::::::::::::::
:run_exes
echo.
echo Executing all tests..
echo.
:process_current_directory
for %%f in (*.exe) do (
	echo %%f
	%%f
)
for /D %%d in (*) do (
	pushd %%d
	call :process_current_directory
	popd
)
exit /b
