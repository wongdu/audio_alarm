cmake_minimum_required(VERSION 3.5)
project(audioAlarmServer C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fvisibility=hidden -fno-common -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads REQUIRED)

#find_library(glog REQUIRED)
find_package(glog REQUIRED)

#find_package(gRPC CONFIG REQUIRED)

find_package(OpenSSL REQUIRED)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
message("CMAKE_CROSSCOMPILING true")
find_program(_PROTOBUF_PROTOC protoc)
else()
message("CMAKE_CROSSCOMPILING false")
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
message("CMAKE_CROSSCOMPILING true grpc_cpp_plugin")
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
message("CMAKE_CROSSCOMPILING false grpc_cpp_plugin")
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()


include_directories(
    ${OPENSSL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/grpc
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/teemo/include
)

LINK_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/teemo/lib)

add_executable(audioAlarmServer
    src/CameraDh.cpp
    src/CameraHik.cpp
    src/CameraSdk.cpp
    grpc/alarm.pb.cc
    grpc/AudioAlarmService.cpp
    grpc/alarm.grpc.pb.cc
    src/AudioAlarmServer.cpp
    src/ThreadPool.cpp    
    src/main.cpp
)

target_link_libraries(audioAlarmServer
	${_REFLECTION}
	${_GRPC_GRPCPP}
	${_PROTOBUF_LIBPROTOBUF}
    teemo
    glog
)
