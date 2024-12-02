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
    cmake -G "MinGW Makefiles" -B ./build
    cd build || exit
    make
    cd ../
    echo "[script] building $service_name exec finished"
}

case "$1" in
    -cl)
        clean
        ;;
    -b)
        build
        ;;
    *)
        echo "Usage: $0 {-cl|-b}"

esac