cmake_minimum_required(VERSION 3.20)
project(xcoin)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
enable_testing()
include_directories(googletest/googletest/include)

add_executable(xcoin-test XBlockchain/tests/xblockchain-tests.cpp)
target_link_libraries(xcoin-test gtest gtest_main)
target_link_libraries(xcoin-test xcoinlib)
add_library(xcoinlib XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_executable(xcoin main.cpp XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_test(xcoin-test xcoin-test)