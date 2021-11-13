cmake_minimum_required(VERSION 3.20)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
#set(VCPKG_TARGET_TRIPLET x64-windows)
project(xcoin)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
enable_testing()
include_directories(googletest/googletest/include)
include_directories(XBlockchain)

#find_package(OpenSSL REQUIRED)
find_package(Drogon CONFIG REQUIRED)

add_executable(xcoin-test XBlockchain/tests/xblockchain-tests.cpp)
add_library(xcoinlib XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_executable(xcoin main.cpp XBlockchain/block.h XBlockchain/block.cpp XBlockchain/Blockchain.cpp XBlockchain/Blockchain.h XBlockchain/sha256.cpp XBlockchain/sha256.h XBlockchain/bignumber.cpp XBlockchain/bignumber.h)
add_executable(xnode XNode/main.cpp XNode/main.cpp)
add_test(xcoin-test xcoin-test)
target_link_libraries(xcoin-test gtest gtest_main)
target_link_libraries(xnode PRIVATE Drogon::Drogon xcoinlib)
target_link_libraries(xcoin-test xcoinlib)