@echo off


if "%1" EQU "-help" goto help

echo ==============================
echo   database-service COMPILING
echo ==============================
cd database-service/
call gradlew clean
call gradlew bootJar
cd ../

echo ==============================
echo   identity-service COMPILING
echo ==============================
cd identity-service/
call gradlew clean
call gradlew bootJar
cd ../

echo ==============================
echo     plain-service COMPILING
echo ==============================
cd plane-service/
echo y|rmdir build
mkdir build
call cmake -G "MinGW Makefiles" -B ./build
cd build/
call make
cd ../
cd ../


@rem echo ==============================
@rem echo        gateway COMPILING
@rem echo ==============================
@rem TODO: clean and rebuild gateway executing file


if "%1" EQU "-c" goto end
if "%1" EQU "-d" goto docker
if "%1" EQU "-dl" goto docker-less

:docker
echo ==============================
echo    DOCKER COMPOSE CLEANING
echo        AND RESTARTING
echo ==============================
docker compose down
echo y|docker system prune -a --volumes
docker compose up
goto end

:docker-less
echo ==============================
echo       RUNNING SERVICES
echo        WITHOUT DOCKER
echo ==============================
for /f "tokens=*" %%a in (.env) do (
    set %%a
)
for /f "tokens=*" %%a in (docker-less.env) do (
    set %%a
)
start java -jar ./database-service/build/libs/database-service-1.jar
start java -jar ./identity-service/build/libs/identity-service-1.jar
start plane-service/build/main.exe
@rem TODO: run gateway executing file
goto end

:help
echo run types:
echo [-c]   compile without run (must be installed: Java Development Kit (JDK) 8 or later + Java Runtime Environment (JRE) 8 or later)
echo [-d]   compile and run with docker (must be installed: Java Development Kit (JDK) 8 or later + Java Runtime Environment (JRE) 8 or later + docker)
echo [-dl]  compile and run without docker (must be installed: Java Development Kit (JDK) 8 or later + Java Runtime Environment (JRE) 8 or later)
goto end

:end

