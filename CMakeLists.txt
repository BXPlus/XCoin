cmake_minimum_required(VERSION 3.20)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
#set(VCPKG_TARGET_TRIPLET x64-windows)
project(xblockchain)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

enable_testing()
include_directories(googletest/googletest/include googletest/googletest)
include_directories(src/XBlockchain src/XNode)

find_package(Protobuf CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(xblockchain-tests src/XBlockchain/tests/xblockchain-tests.cpp)
add_executable(xnode-tests src/XNode/tests/xnode-tests.cpp)
add_library(xblockchain-lib src/XBlockchain/block.h src/XBlockchain/block.cpp src/XBlockchain/Blockchain.cpp src/XBlockchain/Blockchain.h src/XBlockchain/sha256.cpp src/XBlockchain/sha256.h src/XBlockchain/bignumber.cpp src/XBlockchain/bignumber.h)
add_executable(xnode src/XNode/main.cpp src/XNode/node.h src/XNode/node.cpp src/XNode/interface.cpp src/XNode/interface.h src/XNode/XNodeSync.cpp src/XNode/XNodeSync.h src/XNode/blockchain.pb.h src/XNode/blockchain.pb.cc src/XNode/blockchain.grpc.pb.cc src/XNode/blockchain.grpc.pb.h src/XNode/archive.cpp src/XNode/archive.h src/XNode/XNodeSDK.h)

target_link_libraries(xblockchain-lib PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(xblockchain-tests gtest gtest_main)
target_link_libraries(xnode PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite xblockchain-lib gRPC::grpc++ spdlog::spdlog)
target_link_libraries(xblockchain-tests xblockchain-lib)