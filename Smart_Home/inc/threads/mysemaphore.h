#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <iostream>
#include <semaphore.h>

namespace advcpp {
namespace threads {

class Semaphore {
public:
  Semaphore();
  ~Semaphore();

  void wait();
  void post();
private:
  sem_t	m_sem;
};



}} // advcpp::threads



#endif // __SEMAPHORE_H__
