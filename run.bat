docker compose down
echo y|docker system prune -a --volumes

cd identity-service/
call gradlew clean
call gradlew bootJar

cd database-service/
call gradlew clean
call gradlew bootJar

@rem TODO: clean and rebuild plain-service executing file

@rem TODO: clean and rebuild gateway executing file

cd ../
docker compose up