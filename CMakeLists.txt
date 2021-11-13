cmake_minimum_required(VERSION 3.20)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
project(xcoin)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
# TODO: add_subdirectory(put_server_lib_folder_here)
enable_testing()
include_directories(googletest/googletest/include)
# TODO: include_directories(put_server_lib_include_folder_here)

find_package(OpenSSL REQUIRED)
find_package(drogon CONFIG REQUIRED)

add_executable(xcoin-test XBlockchain/tests/xblockchain-tests.cpp)
add_library(xcoinlib XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_executable(xcoin main.cpp XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_executable(xnode XNode/main.cpp XNode/main.cpp XNode/RSA_gen.h XNode/RSA_gen.cpp)
add_test(xcoin-test xcoin-test)
target_link_libraries(xnode PRIVATE drogon)
target_link_libraries(xcoin-test gtest gtest_main)
target_link_libraries(xcoin PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(xcoin-test xcoinlib)