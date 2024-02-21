# c++ grpc 网络通信demo

# 项目介绍
简单的grpc c++ c/s通信

注：代码中有详细解释

# grpc服务通信流程
![通信构造原理图](source.png)
grpc依据protobuf作为服务定义语言，protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` 你的protobuf文件生成grpc.pb和pb文件

# 安装grpc+protobuf
- **注意**：安装过程中会遇到版本不匹配问题，请按照以下流程安装
项目目录为rpc_demo

- 安装cmake：cmake最低版本是3.15 这里我们安装3.23
    ```c++
    # 卸载原有的 cmake
    sudo apt-get autoremove cmake
    ​
    # 下载解压 cmake 3.23
    wget https://cmake.org/files/v3.23/cmake-3.23.0-linux-x86_64.tar.gz
    tar xvzf cmake-3.23.0-linux-x86_64.tar.gz
    ​
    # 创建软链接
    sudo mv cmake-3.23.0-linux-x86_64 /opt/cmake-3.23.0
    sudo ln -sf /opt/cmake-3.23.0/bin/*  /usr/bin/
    ​
    # 测试
    cmake -version
    ```

- 安装gcc\g++: ubuntu原有6.x,我们安装10.X
    ```c++
    # 安装 gcc/g++ 10
    sudo apt-get install -y software-properties-common
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt update
    sudo apt install g++-10 -y
    ​
    # 创建软链接
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 60 --slave /usr/bin/g++ g++ /usr/bin/g++-10 

    sudo update-alternatives --config gcc
    ​
    # 测试
    gcc -v
    g++ -v
    ```

- 安装grpc\protobuf：安装grpc过程中携带了安装protobuf
    ```c++
    # 下载源码
    git clone https://github.com/grpc/grpc
    # 选择版本 v1.45.2
    git tag
    git checkout v1.45.2
    # 下载第三方依赖
    git submodule update --init

    mkdir -p cmake/build
    cd cmake/build
    cmake ../..
    make
    sudo make install

    # 测试protobuf
    protoc --version
    ```

- 测试
    ```c++
    cd grpc/examples/cpp/helloworld/
    mkdir build
    cd build/
    cmake ..

    # 启动服务端，监听在50051端口
    ./greeter_server
    Server listening on 0.0.0.0:50051
    # 启动客户端，服务端返回Hello world
    ./greeter_client 
    Greeter received: Hello world
    ```

- 参考网址
  `https://zhuanlan.zhihu.com/p/589436751`
