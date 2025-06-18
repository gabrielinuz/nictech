#!/bin/bash
mkdir build
# g++ -Wall -std=c++17 -Iinclude src/main.cpp src/customer_manager.cpp src/console_utils.cpp -o build/nictech.exe
g++ -Wall -std=c++17 -Iinclude src/*.cpp -o build/nictech.exe
chmod +x build/nictech.exe