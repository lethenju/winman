#!/bin/bash
# Install script for Winman 
# It will clone necessary dependencies


echo "== Install Winman =="

echo "== Dep -> Clone Termlib =="
git clone git@github.com:lethenju/termlib.git
cd termlib

echo "== Dep -> Clone and install Resman =="
git clone git@github.com:lethenju/resman.github

echo "== Dep -> Clone LogSystem =="
git clone git@github.com:lethenju/log_system.git

cd ..

echo "== Install winman"
mkdir build 
cd build
cmake ..
sudo make install
