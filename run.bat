docker compose down
docker system prune -a --volumes

cd identity-service/
call gradlew clean
call gradlew bootJar

cd database-service/
call gradlew clean
call gradlew bootJar

cd ../
docker compose up