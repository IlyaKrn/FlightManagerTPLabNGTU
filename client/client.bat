@echo off
set service_name=client

if "%1" EQU "-cl" goto clean
if "%1" EQU "-b" goto build
if "%1" EQU "-t" goto test
goto end

:clean
echo [script] cleaning %service_name% ...
rd /s /q "build"
echo [script] cleaning %service_name% finished
goto end

:build
echo [script] building %service_name% exec ...
call cmake -G "MinGW Makefiles" -B ./build
cd build/
call mingw32-make
call mingw32-make install
cd ../
echo [script] building %service_name% exec finished
goto end

:test
echo [script] testing %service_name% exec ...
cd build/
call mingw32-make test
cd ../
echo [script] testing %service_name% exec finished
goto end
















:end
