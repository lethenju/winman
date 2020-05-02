#!/bin/bash
# Install script for Winman 
# It will clone necessary dependencies


echo "== Install Winman =="

echo "== Dep -> Install Termlib =="
git clone git@github.com:lethenju/termlib.git

cd termlib

echo "== Dep -> Install LogSystem =="
git clone git@github.com:lethenju/log_system.git



echo "== Dep -> Install Resman =="
git clone git@github.com:lethenju/resman.git