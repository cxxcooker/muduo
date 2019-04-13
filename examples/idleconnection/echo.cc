#include "examples/idleconnection/echo.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"

#include <assert.h>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;


EchoServer::EchoServer(EventLoop* loop,
                       const InetAddress& listenAddr,
                       int idleSeconds)
  : server_(loop, listenAddr, "EchoServer"),
    connectionBuckets_(idleSeconds)
{
  server_.setConnectionCallback(
      std::bind(&EchoServer::onConnection, this, _1));
  server_.setMessageCallback(
      std::bind(&EchoServer::onMessage, this, _1, _2, _3));
  loop->runEvery(1.0, std::bind(&EchoServer::onTimer, this));
  connectionBuckets_.resize(idleSeconds);  //  定长时间轮
  dumpConnectionBuckets();
}

void EchoServer::start()
{
  server_.start();
}

void EchoServer::onConnection(const TcpConnectionPtr& conn)
{
  LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");

  if (conn->connected())
  {
    EntryPtr entry(new Entry(conn));
    connectionBuckets_.back().insert(entry);
    dumpConnectionBuckets();
    WeakEntryPtr weakEntry(entry);
    conn->setContext(weakEntry);
  }
  else
  {
    assert(!conn->getContext().empty());
    WeakEntryPtr weakEntry(boost::any_cast<WeakEntryPtr>(conn->getContext()));
    LOG_DEBUG << "Entry use_count = " << weakEntry.use_count();
  }
}

void EchoServer::onMessage(const TcpConnectionPtr& conn,
                           Buffer* buf,
                           Timestamp time)
{
  string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " echo " << msg.size()
           << " bytes at " << time.toString();
  conn->send(msg);

  assert(!conn->getContext().empty());
  WeakEntryPtr weakEntry(boost::any_cast<WeakEntryPtr>(
      conn->getContext()));  // 把Entry的弱引用传给connection 持有。在新消息到来时更新bucket，不持shared_ptr是因为connection不应该增加Entry的引用计数，否则如果connection一直活着，Entry就无法析构
  EntryPtr entry(weakEntry.lock());  // 将弱引用提升为强引用
  if (entry)
  {
    connectionBuckets_.back().insert(entry);  // 当bucket被挤出队列时，bucket会析构，如果Entry 引用计数为0，就会析构，从而断开connection，所以要用shared_ptr
    dumpConnectionBuckets();
  }
}

void EchoServer::onTimer()
{
  connectionBuckets_.push_back(Bucket());
  dumpConnectionBuckets();
}

void EchoServer::dumpConnectionBuckets() const
{
  LOG_INFO << "size = " << connectionBuckets_.size();
  int idx = 0;
  for (WeakConnectionList::const_iterator bucketI = connectionBuckets_.begin();
      bucketI != connectionBuckets_.end();
      ++bucketI, ++idx)
  {
    const Bucket& bucket = *bucketI;
    printf("[%d] len = %zd : ", idx, bucket.size());
    for (const auto& it : bucket)
    {
      bool connectionDead = it->weakConn_.expired();
      printf("%p(%ld)%s, ", get_pointer(it), it.use_count(),
          connectionDead ? " DEAD" : "");
    }
    puts("");
  }
}

