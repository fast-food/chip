#! /bin/sh

g++ main.cpp -o reader -I nfc/include/ nfc/src/*.cpp -I food/include/ food/src/*.cpp -std=c++11 -lnfc
./reader
