#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "publisher.h"
#include "subManager.h"
#include "runnable.h"

namespace smartHome {
namespace mediator {

class Dispatcher : public advcpp::threads::Runnable {
public:
  Dispatcher(Publisher& _publisher,SubManager& _subManager);

  void dispatch();
  virtual void run();

private:
  Publisher& m_publisher;
  SubManager& m_subManager;
};

}} // smartHome::mediator








#endif // __DISPATCHER_H__
