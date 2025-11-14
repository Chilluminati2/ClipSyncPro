@echo off

:: This script's only job is to launch the main release script
:: inside the correct Visual Studio Developer Command Prompt environment.

echo =============================================================
echo               ClipSync Pro Release Launcher
echo =============================================================
echo.
echo This will now open the Developer Command Prompt and
echo automatically run the main release script (release.bat).
echo.
echo Please follow the instructions in the new window that opens.
echo.
pause

:: Find the path to the Developer Command Prompt shortcut helper
set "VS_DEV_CMD_PATH=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vcvarsall.bat"

:: Launch a new Developer Command Prompt window.
:: The /k flag tells it to run the command that follows AND keep the window open.
:: We tell it to run our main "release.bat" script.
cmd.exe /k ""%VS_DEV_CMD_PATH%"" x64 && release.bat
