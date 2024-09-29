@echo off

set PROJ_DIR=%~dp0..

rd/s/q %PROJ_DIR%\build

exit /b