#include <stdexcept>

#include "mutex.h"

namespace advcpp {
namespace threads {

Mutex::Mutex(MutexMode _type)
: m_mode(_type)
{
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, m_mode);
  if(pthread_mutex_init(&m_lock, &attr)) {
    throw std::runtime_error("mutex init failed");
  }
  pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_lock);
}


void Mutex::lock()
{
	if(pthread_mutex_lock(&m_lock))
    throw std::runtime_error("mutex lock error");
}

void Mutex::unlock()
{
	if(pthread_mutex_unlock(&m_lock))
    throw std::runtime_error("mutex unlock error");
}


}} // advcpp::threads
