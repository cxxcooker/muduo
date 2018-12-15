hub
---
a server for broadcasting
服务程序，负责一对多的消息分发。它会记住每个 client 订阅了哪些 topic，只把消息发给特定的订阅者

pubsub
------
a client library of hub
一个简单的 client library，方便编写使用 hub 服务的应用程序。这个 library 可以订阅 topic、退订 topic、往指定 topic 发布消息

pub
---
a command line tool for publishing content on a topic
往某个 topic 发布一条消息，消息内容由命令行参数指定

sub
---
a demo tool for subscribing a topic
订阅一个或多个 topic，然后等待 hub 的数据