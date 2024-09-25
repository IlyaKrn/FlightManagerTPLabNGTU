@echo off

cd database-service/
call gradlew clean
call gradlew bootJar
cd ../
echo ==============================
echo   database-service COMPILED
echo ==============================

cd identity-service/
call gradlew clean
call gradlew bootJar
cd ../
echo ==============================
echo   identity-service COMPILED
echo ==============================

@rem TODO: clean and rebuild plain-service executing file

@rem echo ==============================
@rem echo     plain-service COMPILED
@rem echo ==============================

@rem TODO: clean and rebuild gateway executing file

@rem echo ==============================
@rem echo        gateway COMPILED
@rem echo ==============================


if "%1" EQU "-c" goto end
if "%1" EQU "-d" goto docker
if "%1" EQU "-dl" goto docker-less

:docker
docker compose down
echo y|docker system prune -a --volumes
echo ==============================
echo    DOCKER COMPOSE CLEANED
echo    STARTING DOCKER COMPOSE
echo ==============================
docker compose up
goto end

:docker-less
for /f "tokens=*" %%a in (.env) do (
    set %%a
)
start java -jar ./database-service/build/libs/database-service-1.jar
start java -jar ./identity-service/build/libs/identity-service-1.jar
@rem TODO: run plain-service executing file
@rem TODO: run gateway executing file
goto end

:end

