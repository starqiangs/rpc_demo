cmake_minimum_required(VERSION 3.10)

project(MyGRPCProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)


add_executable(server server.cc hello.grpc.pb.cc hello.pb.cc)
add_executable(client client.cc hello.grpc.pb.cc hello.pb.cc)


# 链接 gRPC 和 Protobuf 库
target_link_libraries(server
    gRPC::grpc++ gRPC::grpc++_reflection
    protobuf::libprotobuf
)

target_link_libraries(client
    gRPC::grpc++ gRPC::grpc++_reflection
    protobuf::libprotobuf
)
