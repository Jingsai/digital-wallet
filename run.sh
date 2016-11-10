#!/usr/bin/env bash

# LINUX
# C++
g++ ./src/antifraud.cpp ./src/NetWork.cpp -std=c++0x -o main
./main ./paymo_input/batch_payment.txt ./paymo_input/stream_payment.txt ./paymo_output/output1.txt ./paymo_output/output2.txt ./paymo_output/output3.txt ./paymo_output/output4.txt
