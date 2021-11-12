cmake_minimum_required(VERSION 3.20)
project(xcoin)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
# TODO: add_subdirectory(put_server_lib_folder_here)
enable_testing()
include_directories(googletest/googletest/include)
# TODO: include_directories(put_server_lib_include_folder_here)

add_executable(xcoin-test XBlockchain/tests/xblockchain-tests.cpp)
target_link_libraries(xcoin-test gtest gtest_main)
# TODO: Link server lib here
target_link_libraries(xcoin-test xcoinlib)
add_library(xcoinlib XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_executable(xcoin main.cpp XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h XNode/RSA_gen.h XNode/RSA_gen.cpp)
add_executable(xnode XNode/main.cpp XNode/main.cpp)
add_test(xcoin-test xcoin-test)