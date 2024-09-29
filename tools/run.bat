@echo off
setlocal

set PROJ_NAME=lv_mgr
set PROJ_DIR=%~dp0..

if not exist "%PROJ_DIR%\bin\" (
	goto :eof
)

:: 判断文件夹是否存在
if not exist "%PROJ_DIR%\bin\%PROJ_NAME%.exe" (
	call .\cmake_build.bat
)

cd %PROJ_DIR%\bin\
.\%PROJ_NAME%.exe

endlocal