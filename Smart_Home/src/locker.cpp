#include <stdexcept>

#include "locker.h"

namespace advcpp {
namespace threads {

Locker::Locker(Mutex& _mutex)
: m_mutex(_mutex)
{
  try {
    m_mutex.lock();
  } catch(std::exception& _e) {
    // TODO do something
    throw;
  }
}

Locker::~Locker()
{
    //TODO:  try and catch(exception from mutex unlock)
    m_mutex.unlock();
    //TODO ASSERT
}

}}   // advcpp::threads
