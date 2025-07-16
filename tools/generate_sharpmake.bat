:: Batch arguments
:: %~1: sharpmake.cs file to generate.

:: Sharpmake isn't happy with back-slashes, so we just replace them here.
set "path=%~1"
set "sanitizedPath=%path:\=/%"

:: Todo: Replace with script that finds "Sharpmake.Application.exe", wherever in \bin\ it is.
"%~dp0Sharpmake\Sharpmake.Application\bin\Release\net6.0\Sharpmake.Application.exe" "/sources('%sanitizedPath%')"
