@echo off

pushd "%~dp0tools"
git submodule update --init --recursive

:: Prepare Sharpmake
rmdir /S /Q ".\Sharpmake\Sharpmake.Application\bin"
call ".\compile_msbuild.bat" ".\Sharpmake\Sharpmake.sln" "Release"

:: Prepare Catch2
rmdir /S /Q "Catch2_build"
mkdir "Catch2_build"
pushd "Catch2_build"
call "..\compile_cmake.bat" "..\Catch2\CMakeLists.txt"
popd

popd