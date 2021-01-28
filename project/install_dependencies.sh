#!/bin/bash

PROJECT_DIR=$(pwd)

sudo add-apt-repository ppa:mhier/libboost-latest
sudo apt update

sudo apt install libboost1.70-dev
cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"

sudo apt-get install -y libgtest-dev google-mock cmake valgrind

cd /usr/src/gtest/
sudo cmake CMakeLists.txt
sudo make -j4
sudo cp lib/*.a /usr/lib
sudo cp -r include/gtest /usr/include

cd ../gmock
sudo cmake CMakeLists.txt
sudo make -j4
sudo cp lib/* /usr/lib
sudo cp -r include/gmock /usr/include

cd $PROJECT_DIR
