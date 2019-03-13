#ifndef __WAITABLEQ_H__
#define __WAITABLEQ_H__

#include <queue>

#include "locker.h"
#include "mysemaphore.h"

namespace advcpp {
namespace threads {

template<typename T>
class WaitableQueue {
public:
  ~WaitableQueue();

  WaitableQueue();

  void enqueue(const T& _item);
  T dequeue();
private:
  WaitableQueue(const WaitableQueue& _wq);
  WaitableQueue<T>& operator= (const WaitableQueue<T>& _wq);
private:
  std::queue<T> m_q;
  Mutex m_mtx;
  Semaphore m_sem;
};

template<typename T>
WaitableQueue<T>::~WaitableQueue()
{

}

template<typename T>
WaitableQueue<T>::WaitableQueue()
: m_mtx(Mutex::ErrorCheck)
{

}

template<typename T>
void WaitableQueue<T>::enqueue(const T& _item)
{
  {
    Locker lock(m_mtx);
    m_q.push(_item);
  }
  m_sem.post();
}

template<typename T>
T WaitableQueue<T>::dequeue()
{
  T tmp;
  try {
    m_sem.wait();
    Locker lock(m_mtx);
    tmp = m_q.front();
    m_q.pop();
  } catch(...) {
    // TODO exception HANDLER
    throw;
  }
  return tmp;
}


}} // advcpp::threads


#endif // __WAITABLEQ_H__
