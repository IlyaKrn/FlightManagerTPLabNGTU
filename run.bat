@echo off

if "%1" EQU "-d" goto docker
if "%1" EQU "-dl" goto docker-less



:docker
docker compose down

cd database-service
call ./service -bd
cd ../

cd identity-service
call ./service -bd
cd ../

cd gateway
call ./service -bd
cd ../

cd plane-service
call ./service -bd
cd ../

docker compose up
goto end

:docker-less
for /f "tokens=*" %%a in (docker-less.env) do (
    set %%a
)
cd database-service
call ./service -bdl
cd ../

cd identity-service
call ./service -bdl
cd ../

cd gateway
call ./service -bdl
cd ../

cd plane-service
call ./service -bdl
cd ../

start java -jar ./database-service/build/libs/database-service.jar
start java -jar ./identity-service/build/libs/identity-service.jar
start java -jar ./gateway/build/libs/gateway.jar
start plane-service/build/main.exe
goto end

:end

