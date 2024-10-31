FROM gcc:latest

RUN apt update -y && apt install -y make cmake

ADD ../ /app

RUN mkdir /app/build &&\
    cmake -G "Unix Makefiles" -S /app -B /app/build &&\
    make -C /app/build

CMD ["/app/build/main"]
EXPOSE ${PLANE_SERVICE_PORT}