#!/bin/bash

service_name="client"

function clean {
    echo "[script] cleaning $service_name ..."
    rm -rf build
    echo "[script] cleaning $service_name finished"
}

function build {
    echo "[script] building $service_name exec ..."
    mkdir build
    cmake -G "Unix Makefiles" -B ./build
    cd build || exit
    make
    cd ..
    echo "[script] building $service_name exec finished"
}
function test {
    echo "[script] building $service_name exec ..."
    mkdir build
    cmake -G "Unix Makefiles" -B ./build
    cd build || exit
    make
    make test
    cd ..
    echo "[script] building $service_name exec finished"
}
case "$1" in
    -cl)
        clean
        ;;
    -b)
        build
        ;;
    -t)
        test
        ;;
    *)
        echo "Usage: $0 {-cl|-b}"

esac