FROM gcc:latest

RUN apt update -y
RUN apt install make -y
RUN apt install cmake -y

ADD ./src /app/src
COPY ./CMakeLists.txt /app/CMakeLists.txt

RUN mkdir /app/build
RUN cmake -G "Unix Makefiles" -S /app -B /app/build
RUN make -C /app/build

CMD ["/app/build/main"]
EXPOSE 8083