#!/bin/bash
sudo docker compose down
function docker_compose {
    echo "[script] Building database-service ..."
    cd database-service
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Building identity-service ..."
    cd identity-service
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Building gateway ..."
    cd gateway
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Building plane-service ..."

    cd plane-service
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Starting Docker services ..."
    sudo docker compose up
}
function docker_less {
    echo "not realized yet"
}

case "$1" in
    -d)
      docker_compose
      ;;
    -dl)
      docker_less
      ;;
    *)
      echo "Usage: $0 {-d|-dl}"
      exit 1
      ;;
esac
