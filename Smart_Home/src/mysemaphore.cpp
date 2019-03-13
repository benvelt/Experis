#include "mysemaphore.h"

namespace advcpp {
namespace threads {

Semaphore::Semaphore()
{
  if(sem_init(&m_sem,0,0) == -1)
    throw std::runtime_error("semaphore init failed");
}

Semaphore::~Semaphore()
{
	sem_destroy(&m_sem);
}

void Semaphore::wait()
{
  if(-1 == sem_wait(&m_sem))
    throw std::runtime_error("semaphore wait failed");
}

void Semaphore::post()
{
  if(-1 == sem_post(&m_sem))
    throw std::runtime_error("semaphore post failed");
}

}} // advcpp::threads
