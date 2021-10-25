cmake_minimum_required(VERSION 3.20)
project(xcoin)

set(CMAKE_CXX_STANDARD 17)

add_executable(xcoin main.cpp XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
