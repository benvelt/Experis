#ifndef __LOCKER_H__
#define __LOCKER_H__

#include "mutex.h"

namespace advcpp {
namespace threads {

class Locker {
public:
  Locker(Mutex& _mutex);
  ~Locker();

private:
  Mutex& m_mutex;
};

}}  // advcpp::threads



#endif //__LOCKER_H__
