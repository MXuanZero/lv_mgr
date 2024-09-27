@echo off

set PROJ_DIR=%~dp0..\

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=gcc -DCMAKE_CXX_COMPILER:FILEPATH=g++ --no-warn-unused-cli -SE:/WorkSpace/C/lv_mgr -Be:/WorkSpace/C/lv_mgr/build -G "MinGW Makefiles"

exit /b