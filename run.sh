#!/usr/bin/env bash

# Linux
# C++

g++ ./src/antifraud.cpp ./src/NetWork.cpp -o main -std=c++0x
./main ./paymo_input/batch_payment.txt ./paymo_input/stream_payment.txt ./paymo_output/output1.txt ./paymo_output/output2.txt ./paymo_output/output3.txt
