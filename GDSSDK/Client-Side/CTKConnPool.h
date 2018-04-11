/**
 * Created by niuqiang on 4/8/18.
 */

#ifndef MUDUO_CTKCONNPOOL_H
#define MUDUO_CTKCONNPOOL_H

#include <muduo/net/TcpClient.h>

using namespace muduo::net;

class CTKConnectionPool {
public:
    CTKConnectionPool(void);
    virtual ~CTKConnectionPool(void);

public:
    bool reset(void * args);  // 根据参数重置连接池

    bool getConnection(void * args);  // 获取指定端点的连接

    bool GetConnection(void);  // 根据负载均衡策略获取具体连接

// 对单个连接的操作
public:
    bool GetPeerAddr(TcpClient * client);  // 获取对端地址
};

#endif //MUDUO_CTKCONNPOOL_H
