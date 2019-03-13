#include <pthread.h>

#include "thread.h"

namespace advcpp {
namespace threads {

Thread::Thread(Runnable& _r)
: m_r(_r)
{
  pthread_create(&m_thread, NULL, threadFunc, this);
}

Thread::~Thread()
{
  pthread_join(m_thread, NULL);
}


void* Thread::threadFunc(void* _pv)
{
  ((Thread*)_pv)->m_r.run();

  return NULL;
}


}} // advcpp::threads
