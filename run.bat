@echo off

docker compose down
echo y|docker system prune -a --volumes

echo ==============================
echo         DOCKER CLEANED
echo ==============================

cd identity-service/
call gradlew clean
call gradlew bootJar

echo ==============================
echo   identity-service COMPILED
echo ==============================

cd database-service/
call gradlew clean
call gradlew bootJar

echo ==============================
echo   database-service COMPILED
echo ==============================

@rem TODO: clean and rebuild plain-service executing file

@rem echo ==============================
@rem echo     plain-service COMPILED
@rem echo ==============================

@rem TODO: clean and rebuild gateway executing file

@rem echo ==============================
@rem echo        gateway COMPILED
@rem echo ==============================



echo ==============================
echo    STARTING DOCKER COMPOSE
echo ==============================

cd ../
docker compose up