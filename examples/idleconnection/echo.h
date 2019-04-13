#ifndef MUDUO_EXAMPLES_IDLECONNECTION_ECHO_H
#define MUDUO_EXAMPLES_IDLECONNECTION_ECHO_H

#include "muduo/net/TcpServer.h"
//#include <muduo/base/Types.h>

#include <unordered_set>

#include <boost/circular_buffer.hpp>

// RFC 862
class EchoServer
{
 public:
  EchoServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr,
             int idleSeconds);

  void start();

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn);

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);

  void onTimer();

  void dumpConnectionBuckets() const;

  typedef std::weak_ptr<muduo::net::TcpConnection> WeakTcpConnectionPtr;

  struct Entry : public muduo::copyable
  {
    explicit Entry(const WeakTcpConnectionPtr& weakConn)
      : weakConn_(weakConn)
    {
    }

    ~Entry()
    {
      muduo::net::TcpConnectionPtr conn = weakConn_.lock();
      if (conn)
      {
        conn->shutdown();  // 如果conn还活着，就断开它
      }
    }

    WeakTcpConnectionPtr weakConn_;  // connection的弱引用。因为Entry析构时要负责断开connection，另外，Entry不应该管理connection的生命周期，所以不用shared_ptr
  };
  typedef std::shared_ptr<Entry> EntryPtr;
  typedef std::weak_ptr<Entry> WeakEntryPtr;
  typedef std::unordered_set<EntryPtr> Bucket;  // 桶
  typedef boost::circular_buffer<Bucket> WeakConnectionList;  // 队列

  muduo::net::TcpServer server_;
  WeakConnectionList connectionBuckets_;
};

#endif  // MUDUO_EXAMPLES_IDLECONNECTION_ECHO_H
