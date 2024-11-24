#!/bin/bash
sudo docker compose down

echo "[script] Building database-service ..."
cd database-service
sudo chmod +x script.bash
sudo ./script.bash -bd
cd ..

echo "[script] Building identity-service ..."
cd identity-service
sudo chmod +x script.bash
sudo ./script.bash -bd
cd ..

echo "[script] Building gateway ..."
cd gateway
sudo chmod +x script.bash
sudo ./script.bash -bd
cd ..

echo "[script] Building plane-service ..."

cd plane-service
sudo chmod +x script.bash
sudo ./script.bash -bd
cd ..

echo "[script] Starting Docker services ..."
sudo docker compose up