#! /bin/sh

g++ main.cpp -o reader -I include/ src/*.cpp -std=c++11 -lnfc
./reader
