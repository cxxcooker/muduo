examples
|-- asio 从 Boost.Asio 移植的例子
| |-- chat 多人聊天的服务端和客户端，示范打包和拆包（codec）
| \-- tutorial 一系列 timers
|-- cdns 基于 c-ares 的异步 DNS 解析
|-- curl 基于 curl 的异步 HTTP 客户端
|-- filetransfer 简单的文件传输，示范完整发送 TCP 数据
|-- hub 一个简单的 pub/sub/hub 服务，演示应用级的广播
|-- idleconnection 踢掉空闲连接
|-- maxconnection 控制最大连接数
|-- multiplexer 1:n 串并转换服务
|-- netty 从 JBoss Netty 移植的例子
| |-- discard 可用于测试带宽，服务器可多线程运行
| |-- echo 可用于测试带宽，服务器可多线程运行
| \-- uptime 带自动重连的 TCP 长连接客户端
|-- pingpong pingpong 协议，用于测试消息吞吐量
|-- protobuf Google Protobuf 的网络传输示例
| |-- codec 自动反射消息类型的传输方案
| |-- rpc RPC 示例，实现 Sudoku 服务
| \-- rpcbench RPC 性能测试示例
|-- roundtrip 测试两台机器的网络延时与时间差
|-- shorturl 简单的短址服务
|-- simple 5 个简单网络协议的实现
| |-- allinone 在一个程序里同时实现下面 5 个协议
| |-- chargen RFC 864，可测试带宽
| |-- chargenclient chargen 的客户端
| |-- daytime RFC 867
| |-- discard RFC 863
| |-- echo RFC 862
| |-- time RFC 868
| \-- timeclient time 协议的客户端
|-- socks4a Socks4a 代理服务器，示范动态创建 TcpClient
|-- sudoku 数独求解器，示范 muduo 的多线程模型
|-- twisted 从 Python Twisted 移植的例子
| \-- finger finger01 ~ 07
\-- zeromq 从 ZeroMQ 移植的性能（消息延迟）测试