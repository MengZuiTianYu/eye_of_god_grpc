cmake_minimum_required(VERSION 3.5)
project(grpc_test)


if(CMAKE_COMPILER_IS_GNUCC)
    message("COMPILER IS GNUCC")
    ADD_DEFINITIONS ( -std=c++11 )
endif(CMAKE_COMPILER_IS_GNUCC)


IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-DDEBUG)
ENDIF()
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -ggdb3")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#/home/panhm/MyPorjects/grpc_test
#/home/panhm/.usr/aiit/eye/bin/protoc -I ./src/cifs_grpc/protos --grpc_out=./src/cifs_grpc/pb_gen --plugin=protoc-gen-grpc='/home/panhm/.usr/aiit/eye/bin/grpc_cpp_plugin' ./src/cifs_grpc/protos/eye_of_god.proto
#/home/panhm/.usr/aiit/eye/bin/protoc -I ./src/cifs_grpc/protos --cpp_out=./src/cifs_grpc/pb_gen ./src/cifs_grpc/protos/eye_of_god.proto

#execute_process(COMMAND /home/panhm/.usr/aiit/eye/bin/protoc "-I ${CMAKE_SOURCE_DIR}/src/cifs_grpc/protos --grpc_out=${CMAKE_SOURCE_DIR}/src/cifs_grpc/pb_gen --plugin=protoc-gen-grpc='/home/panhm/.usr/aiit/eye/bin/grpc_cpp_plugin' ${CMAKE_SOURCE_DIR}/src/cifs_grpc/protos/eye_of_god.proto")
#execute_process(COMMAND /home/panhm/.usr/aiit/eye/bin/protoc "-I ${CMAKE_SOURCE_DIR}/src/cifs_grpc/protos --cpp_out=${CMAKE_SOURCE_DIR}/src/cifs_grpc/pb_gen ${CMAKE_SOURCE_DIR}/src/cifs_grpc/protos/eye_of_god.proto")
#message(CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR})

#include_directories(SYSTEM "/foo/bar")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)

#protobuf3
#set(CMAKE_INCLUDE_PATH "/home/panhm/.usr/include")
#set(CMAKE_INCLUDE_PATH "/home/panhm/.usr/local/include")
#set(CMAKE_LIBRARY_PATH "/home/panhm/.usr/lib")
#set(CMAKE_LIBRARY_PATH "/home/panhm/.usr/local/lib")

#google::protobufv3

#INCLUDE_DIRECTORIES("/home/panhm/.usr/aiit/eye/")
INCLUDE_DIRECTORIES("/home/panhm/.usr/aiit/eye/include")
#INCLUDE_DIRECTORIES("/home/panhm/.usr/protobuf3/local")
#INCLUDE_DIRECTORIES("/home/panhm/.usr/protobuf3/local/include")


set(SRV_HEADER_SRCS
        ./src/cifs_grpc/pb_gen/eye_of_god.grpc.pb.h
        )

set(SRV_CPP_SRCS
        ./src/cifs_grpc/pb_gen/eye_of_god.grpc.pb.cc
        ./src/cifs_grpc/pb_gen/eye_of_god.pb.cc
        ./src/cifs_grpc/grpc_eye_server.cpp
        )

message(${SRV_HEADER_SRCS})
message(${SRV_CPP_SRCS})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
add_executable(grpc_test ${SRV_HEADER_SRCS} ${SRV_CPP_SRCS} ./src/main.cpp)

#protobuf3
#target_link_libraries(grpc_test /home/panhm/.usr/local/lib/libaddress_sorting.so)
#target_link_libraries(grpc_test /home/panhm/.usr/local/lib/libgpr.so)
#target_link_libraries(grpc_test /home/panhm/.usr/local/lib/libgrpc.so)
#target_link_libraries(grpc_test /home/panhm/.usr/local/lib/libgrpc++.so)
#target_link_libraries(grpc_test /home/panhm/.usr/lib/libz.so)
#target_link_libraries(grpc_test /home/panhm/.usr/lib/libprotobuf.so)


#google::protobufv3
target_link_libraries(grpc_test /home/panhm/.usr/lib/libz.so)
target_link_libraries(grpc_test /home/panhm/.usr/aiit/eye/lib/libaddress_sorting.so)
target_link_libraries(grpc_test /home/panhm/.usr/aiit/eye/lib/libgpr.so)
target_link_libraries(grpc_test /home/panhm/.usr/aiit/eye/lib/libgrpc.so)
target_link_libraries(grpc_test /home/panhm/.usr/aiit/eye/lib/libgrpc++.so)
target_link_libraries(grpc_test /home/panhm/.usr/aiit/eye/lib/libprotobufv3.so)

#target_link_libraries(grpc_test /usr/lib/x86_64-linux-gnu/libprotobuf.so)

##shared
ADD_LIBRARY(eyeggrpc  SHARED ${SRV_HEADER_SRCS} ${SRV_CPP_SRCS})
target_link_libraries(eyeggrpc /home/panhm/.usr/lib/libz.so)
target_link_libraries(eyeggrpc /home/panhm/.usr/aiit/eye/lib/libaddress_sorting.so)
target_link_libraries(eyeggrpc /home/panhm/.usr/aiit/eye/lib/libgpr.so)
target_link_libraries(eyeggrpc /home/panhm/.usr/aiit/eye/lib/libgrpc.so)
target_link_libraries(eyeggrpc /home/panhm/.usr/aiit/eye/lib/libgrpc++.so)
target_link_libraries(eyeggrpc /home/panhm/.usr/aiit/eye/lib/libprotobufv3.so)


#static
#ADD_LIBRARY(eyeggrpc   STATIC ${SRV_HEADER_SRCS} ${SRV_CPP_SRCS})
#target_link_libraries(eyeggrpc
#        /home/panhm/.usr/local/lib/libaddress_sorting.a
#        /home/panhm/.usr/local/lib/libgpr.a
#        /home/panhm/.usr/local/lib/libgrpc.a
#        /home/panhm/.usr/local/lib/libgrpc++.a
#        /home/panhm/.usr/lib/libz.a
#        /home/panhm/.usr/lib/libprotobuf.a
#        )



