#!/bin/bash

PROJECT_DIR=$(pwd)

sudo add-apt-repository ppa:mhier/libboost-latest
sudo apt update

sudo apt install libboost1.68-dev
cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"

sudo apt-get install -y libgtest-dev google-mock cmake valgrind

cd /usr/src/gtest/
sudo cmake CMakeLists.txt
sudo make install -j4

cd ../gmock
sudo cmake CMakeLists.txt
sudo make install -j4

cd $PROJECT_DIR
