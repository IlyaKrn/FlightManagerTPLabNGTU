FROM ubuntu

RUN apt update -y && apt install -y openjdk-17-jdk openjdk-17-jre dos2unix

ADD ../ /app

RUN cd /app &&\
    dos2unix gradlew &&\
    ./gradlew bootJar

CMD ["java", "-jar", "/app/build/libs/app.jar"]
EXPOSE ${DATABASE_SERVICE_PORT}