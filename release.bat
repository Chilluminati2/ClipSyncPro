@echo off
setlocal enabledelayedexpansion

:: ==============================================================================
:: ClipSync Pro - RESILIENT Release Script
:: This script anticipates and fixes bad behavior from Qt's qtenv2.bat script.
:: It MUST be run from inside a VS Developer Command Prompt.
:: ==============================================================================

:: --- Configuration ---
set QT_DIR=C:\Qt\6.10.0\msvc2022_64
set WEBSITE_DIR=C:\Users\Chilluminati\Downloads\ClipSync Pro Website\

:: --- Setup ---
echo(
echo --- Initializing Qt environment... ---

:: Save our starting directory, because the Qt script will change it.
set "START_DIR=%cd%"

:: Call the problematic Qt script
call "%QT_DIR%\bin\qtenv2.bat"

:: IMPORTANT: Force the directory back to where we started.
cd /d "%START_DIR%"

echo Qt environment has been configured. Returning to project directory.
echo(

:: --- Get Version ---
:getVersion
set "VERSION="
set /p "VERSION=Enter new version number (e.g., 2.0): "
if not defined VERSION (
    echo Version number cannot be empty. Please try again.
    goto getVersion
)

echo(
echo --- Starting Release Process for v%VERSION% ---
echo(

:: --- Define Filenames ---
set APP_ZIP_NAME=ClipSyncPro-v%VERSION%-Windows.zip
set SOURCE_ZIP_NAME=ClipSyncPro-v%VERSION%-Source.zip
set TEMP_BUILD_DIR=%~dp0build
set TEMP_RELEASE_DIR=%TEMP_BUILD_DIR%\Release

:: --- Clean and Build ---
echo [1/5] Cleaning previous build...
if exist "%TEMP_BUILD_DIR%" rd /s /q "%TEMP_BUILD_DIR%"

echo [2/5] Configuring Release build with CMake...
cmake -B "%TEMP_BUILD_DIR%" -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 ( echo CMake configuration failed. Aborting. & goto end )

echo [3/5] Compiling the application...
cmake --build "%TEMP_BUILD_DIR%" --config Release
if %errorlevel% neq 0 ( echo Compilation failed. Aborting. & goto end )

:: --- Create Packages ---
echo [4/5] Creating application and source packages...
cd /d "%TEMP_RELEASE_DIR%"
echo      - Deploying Qt DLLs...
windeployqt.exe ClipSyncPro.exe
echo      - Zipping application files...
tar -a -c -f "%~dp0%APP_ZIP_NAME%" .
cd /d "%~dp0"
echo      - Zipping source files...
tar -a -c -f "%~dp0%SOURCE_ZIP_NAME%" assets src CMakeLists.txt win32_resource.rc

:: --- Deploy to Website ---
echo [5/5] Deploying to website and updating index.html...
if not exist "%WEBSITE_DIR%downloads\" ( echo Website downloads folder not found. Aborting. & goto end )

echo      - Copying new packages...
copy /Y "%~dp0%APP_ZIP_NAME%" "%WEBSITE_DIR%downloads\"
copy /Y "%~dp0%SOURCE_ZIP_NAME%" "%WEBSITE_DIR%downloads\"

:: --- HTML Update ---
set "HTML_FILE=%WEBSITE_DIR%index.html"
set "TEMP_HTML_FILE=%WEBSITE_DIR%index.temp.html"
(
    echo ^<div class="version-block"^>
    echo   ^<h4^>Version %VERSION%^</h4^>
    echo   ^<a href="downloads/%APP_ZIP_NAME%" class="btn btn-primary"^>Download App v%VERSION% (.zip)^</a^>
    echo   ^<a href="downloads/%SOURCE_ZIP_NAME%" class="btn btn-tertiary"^>Download Source v%VERSION% (.zip)^</a^>
    echo ^</div^>
) > new_version.tmp
(
    for /f "delims=" %%i in ('findstr /n "^" "%HTML_FILE%"') do (
        set "line=%%i"
        set "line=!line:*:=!"
        if "%%i" equ "%%i:*" (
            echo(
        ) else (
            echo !line! | findstr /C:"<div class=\"version-block\">" > nul
            if !errorlevel! equ 0 (
                type new_version.tmp
                echo(
            )
            echo !line!
        )
    )
) > "%TEMP_HTML_FILE%"
del new_version.tmp
move /Y "%TEMP_HTML_FILE%" "%HTML_FILE%"
echo      - index.html has been updated!

echo(
echo --- Release v%VERSION% Complete! ---
echo(

:end
pause