#!/bin/bash
# Install script for Winman 
# It will clone necessary dependencies


echo "== Install Winman =="

echo "== Dep -> Clone Termlib =="
git clone git@github.com:lethenju/termlib.git

cd termlib

echo "== Dep -> Clone and install Resman =="
git clone git@github.com:lethenju/resman.git
cd resman
mkdir build
cd build
cmake ..
sudo make install
cd ../..

echo "== Dep -> Clone and install LogSystem =="
git clone git@github.com:lethenju/log_system.git
cd log_system
mkdir build
cd build
cmake ..
sudo make install
cd ../..

echo "== Dep -> Install Termlib"
mkdir build
cd build
cmake ..
sudo make install
cd ../..

echo "== Install winman"
mkdir build 
cd build
cmake ..
sudo make install
