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
include_directories(src/XBlockchain)

#find_package(OpenSSL REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

add_executable(xcoin-test src/XBlockchain/tests/xblockchain-tests.cpp)
add_library(xcoinlib src/XBlockchain/block.h src/XBlockchain/block.cpp src/XBlockchain/Blockchain.cpp src/XBlockchain/Blockchain.h src/XBlockchain/sha256.cpp src/XBlockchain/sha256.h src/XBlockchain/bignumber.cpp src/XBlockchain/bignumber.h)
add_executable(xcoin main.cpp src/XBlockchain/block.h src/XBlockchain/block.cpp src/XBlockchain/Blockchain.cpp src/XBlockchain/Blockchain.h src/XBlockchain/sha256.cpp src/XBlockchain/sha256.h src/XBlockchain/bignumber.cpp src/XBlockchain/bignumber.h)
add_executable(xnode src/XNode/main.cpp src/XNode/main.cpp src/XNode/blockchain.pb.cc src/XNode/interface.cpp src/XNode/interface.h)
add_test(xcoin-test xcoin-test)

target_link_libraries(xcoin-test gtest gtest_main)
target_link_libraries(xnode PRIVATE Drogon::Drogon protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite xcoinlib)
target_link_libraries(xcoin-test xcoinlib)