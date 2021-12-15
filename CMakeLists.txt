cmake_minimum_required(VERSION 3.20)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
#set(VCPKG_TARGET_TRIPLET x64-windows)
project(xblockchain VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_PREFIX_PATH "C:\\Qt\\5.12.12\\msvc2017") # For now, everyone needs to change that to their own QT path

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(googletest)

enable_testing()
include_directories(googletest/googletest/include googletest/googletest)
include_directories(src/XBlockchain src/XNode)

find_package(Qt5 COMPONENTS Core Widgets)
find_package(Protobuf CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB xcoin-client-sources
        "${PROJECT_SOURCE_DIR}/ui/*.h"
        "${PROJECT_SOURCE_DIR}/ui/*.cpp")

add_executable(xblockchain-tests src/XBlockchain/tests/xblockchain-tests.cpp)
add_executable(xtricount TricountAlgo/Tricount.cpp TricountAlgo/Tricount.h)
add_executable(xnode-tests src/XNode/tests/xnode-tests.cpp)
add_executable(xcoin-client ${xcoin-client-sources})
add_library(xblockchain-lib src/XBlockchain/block.h src/XBlockchain/block.cpp src/XBlockchain/Blockchain.cpp src/XBlockchain/Blockchain.h src/XBlockchain/sha256.cpp src/XBlockchain/sha256.h src/XBlockchain/bignumber.cpp src/XBlockchain/bignumber.h src/XBlockchain/transaction.cpp src/XBlockchain/transaction.h src/XBlockchain/wallet.cpp src/XBlockchain/wallet.h src/XBlockchain/transactionPool.cpp src/XBlockchain/transactionPool.h)
add_executable(xnode src/XNode/main.cpp src/XNode/node.h src/XNode/node.cpp src/XNode/interface.cpp src/XNode/interface.h src/XNode/keys.cpp src/XNode/keys.h src/XNode/blockchain.pb.h src/XNode/blockchain.pb.cc src/XNode/blockchain.grpc.pb.cc src/XNode/blockchain.grpc.pb.h src/XNode/archive.cpp src/XNode/archive.h)

target_link_libraries(xblockchain-lib PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(xblockchain-tests gtest gtest_main)
target_link_libraries(xnode PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite xblockchain-lib gRPC::grpc++ spdlog::spdlog)
target_link_libraries(xblockchain-tests xblockchain-lib)
target_link_libraries(xcoin-client PRIVATE Qt5::Widgets)

add_custom_command(TARGET xcoin-client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:xcoin-client>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:xcoin-client>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:xcoin-client>
        )