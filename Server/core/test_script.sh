#!/bin/bash

g++ -std=c++20 test_message_parser.cpp MessageParser.cpp  \
    -I.. \
    $(pkg-config --cflags Qt6Core) \
    $(pkg-config --libs Qt6Core) \
    -lgtest -lgtest_main -pthread \
    -lgtest -lgtest_main -pthread -o test_parser

