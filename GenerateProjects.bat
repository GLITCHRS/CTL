@echo off

echo vs2022
echo vs2019
echo gmake2
echo xcode4
echo codelite

set /p "platform=Please choose a platform: "

call premake5.exe %platform%
PAUSE