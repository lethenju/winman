#!/bin/bash
# Install script for Winman 
# It will clone necessary dependencies


echo "== Install Winman =="

echo "== Dep -> Clone Termlib =="
git clone git@github.com:lethenju/termlib.git
cd termlib

echo "== Dep -> Clone Resman =="
git clone git@github.com:lethenju/resman.git

echo "== Dep -> Clone LogSystem =="
git clone git@github.com:lethenju/log_system.git
cd ..

echo "== Install winman and dependencies"
mkdir build 
cd build
cmake ..
make
sudo make install

