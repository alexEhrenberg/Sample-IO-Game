#!/bin/sh
# how to build a game server from scratch (using uwebsockets on digitalOcean's servers with a centos image)
yum update -y
yum install gcc-c++ -y
yum install openssl-devel -y
yum groupinstall "Development Tools" -y

yum install wget -y

wget "https://cmake.org/files/v3.12/cmake-3.12.0.tar.gz"
tar xvzf cmake-3.12.0.tar.gz
cd cmake-3.12.0
./bootstrap && make && make install
cd ..

wget "https://github.com/libuv/libuv/archive/v1.x.zip"
unzip v1.x.zip
cd libuv-1.x
sh autogen.sh
./configure
make
make check
make install
cd ..

yum install boost-devel -y

# download website
svn export https://github.com/alexEhrenberg/Sample-IO-Game/trunk/Part-1
cd Part-1

# build uWebSockets
wget "https://github.com/uNetworking/uWebSockets/archive/v0.14.8.zip"
unzip v0.14.8.zip
cd uWebSockets-0.14.8
make
make install
cd ..

# build website
cmake .
make
export LD_LIBRARY_PATH=/usr/local/lib
./server
