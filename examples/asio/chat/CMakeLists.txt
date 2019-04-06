# 一个与 Boost.Asio 的示例代码中的聊天服务器功能类似的网络服务程序
# 主要目的是介绍如何处理分包，并初步涉及 Muduo 的多线程功能
# 实际上是一个简单的基于 TCP 的应用层广播协议，由服务端负责把消息发送给每个连接到它的客户端

# 分包指的是在发生一个消息(message)或一帧(frame)数据时，通过一定的处理，让接收方能从字节流中识别并截取（还原）出一个个消息。

# 对于长连接的 TCP 服务，分包有四种方法：
# 消息长度固定，比如 muduo 的 roundtrip 示例就采用了固定的 16 字节消息；
# 使用特殊的字符或字符串作为消息的边界，例如 HTTP 协议的 headers 以 "/r/n" 为字段的分隔符；
# 在每条消息的头部加一个长度字段，这恐怕是最常见的做法，本文的聊天协议也采用这一办法；
# 利用消息本身的格式来分包，例如 XML 格式的消息中 ... 的配对，或者 JSON 格式中的 { ... } 的配对。解析这种消息格式通常会用到状态机。

add_executable(asio_chat_client client.cc codec.h)
target_link_libraries(asio_chat_client muduo_net)

add_executable(asio_chat_loadtest loadtest.cc)
target_link_libraries(asio_chat_loadtest muduo_net)

add_executable(asio_chat_server server.cc)
target_link_libraries(asio_chat_server muduo_net)

add_executable(asio_chat_server_threaded server_threaded.cc)
target_link_libraries(asio_chat_server_threaded muduo_net)

add_executable(asio_chat_server_threaded_efficient server_threaded_efficient.cc)
target_link_libraries(asio_chat_server_threaded_efficient muduo_net)

add_executable(asio_chat_server_threaded_highperformance server_threaded_highperformance.cc)
target_link_libraries(asio_chat_server_threaded_highperformance muduo_net)

