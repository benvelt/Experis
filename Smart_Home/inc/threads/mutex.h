#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>

namespace advcpp {
namespace threads {

class Mutex {
public:
  enum MutexMode {
    Normal = PTHREAD_MUTEX_NORMAL
    ,ErrorCheck = PTHREAD_MUTEX_ERRORCHECK
    ,Recursive = PTHREAD_MUTEX_RECURSIVE
    ,Default = PTHREAD_MUTEX_DEFAULT
  };
  Mutex(MutexMode _mode = Normal);
  ~Mutex();

  void lock();
  void unlock();
private:
  pthread_mutex_t m_lock;
  MutexMode m_mode;
};



}} // advcpp::threads



#endif // __MUTEX_H__
