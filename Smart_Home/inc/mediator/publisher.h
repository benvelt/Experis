#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

//#include <queue>
#include "waitableq.h"


#include "event.h"

namespace smartHome {
namespace mediator {

class Publisher {
public:
  virtual void publishEvent(Event* _event);
  Event* getEvent();
private:
  //std::queue<Event*> m_eventsWQ;
  advcpp::threads::WaitableQueue<Event*> m_eventsWQ;
};

}} // smartHome::mediator








#endif // __PUBLISHER_H__
