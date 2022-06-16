@echo off
pushd %~dp0\..\
call Tools\BuildSystem\bin\premake5.exe --file=Tools\BuildSystem\premake5.lua vs2022
popd
PAUSE