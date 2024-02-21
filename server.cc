#include <grpc++/grpc++.h>

#include "hello.pb.h"
#include "hello.grpc.pb.h"

class HelloServiceImpl : public rpc_demo::Greeter::Service
{
public:
    virtual grpc::Status SayHello(grpc::ServerContext *context, const rpc_demo::HelloRequest *request, rpc_demo::HelloReply *reply) override
    {
        std::string prefix = "hello,";
        reply->set_message(prefix + std::string(request->name()));
        return grpc::Status::OK;
    }
};

void RunServer()
{
    std::string server_address("0.0.0.0:50051");
    //创建一个服务类
    HelloServiceImpl service;

    //创建工厂类
    grpc::ServerBuilder builder;

    //监听端口
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    //心跳探活
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, 5000);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
    
    // 多线程：动态调整 epoll 线程数量
    builder.SetSyncServerOption(grpc::ServerBuilder::MIN_POLLERS, 4);
    builder.SetSyncServerOption(grpc::ServerBuilder::MAX_POLLERS, 8);

    //注册服务
    builder.RegisterService(&service);

    //启动
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    //进入服务事件循环
    server->Wait();
}

int main()
{
    RunServer();

    return 0;
}