@echo off
setlocal

set PROJ_NAME=lv_mgr
set PROJ_DIR=%~dp0..

if exist "%PROJ_DIR%\build" (
	call ./clean.bat
)

call ./cmake_config.bat
call ./cmake_build.bat

cd %PROJ_DIR%\bin\
.\%PROJ_NAME%.exe

endlocal