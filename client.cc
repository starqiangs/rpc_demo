#include <iostream>
#include <grpcpp/grpcpp.h>

#include "hello.grpc.pb.h"

class HelloClient
{
public:
    HelloClient(std::shared_ptr<grpc::Channel> channel) : stub_(rpc_demo::Greeter::NewStub(channel)) {}

    std::string SayHello(const std::string &name)
    {
        rpc_demo::HelloRequest request;
        request.set_name(name);

        rpc_demo::HelloReply response;
        grpc::ClientContext context;

        // 调用rpc接口
        grpc::Status status = stub_->SayHello(&context, request, &response);

        if (status.ok())
        {
            return response.message();
        }
        else
        {
            return "rpc failed!!!";
        }
    }

private:
    std::unique_ptr<rpc_demo::Greeter::Stub> stub_;
};

int main()
{
    // 服务器地址
    std::string server_addr = "localhost:50051";

    // 创建请求管道
    HelloClient client(
        grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials())
    );

    // 构造测试
    std::string name = "qiang";
    std::string response = client.SayHello(name);
    std::cout << "helloclient: " << response << std::endl;

    return 0;
}