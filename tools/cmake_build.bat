@echo off
set PROJ_DIR=%~dp0..

if not exist "%PROJ_DIR%\build" (
    call %PROJ_DIR%\tools\cmake_config.bat
)

cmake --build %PROJ_DIR%\build --config Debug --target all -j 18 --

exit /b
