#ifndef __THREAD_H__
#define __THREAD_H__

#include "runnable.h"

namespace advcpp {
namespace threads {

class Thread {
public:
  Thread(Runnable& _r);
  ~Thread();

private:
  static void* threadFunc(void* _pv);
  Runnable& m_r;
  pthread_t m_thread;
};

}} // advcpp::threads

#endif // __THREAD_H__
