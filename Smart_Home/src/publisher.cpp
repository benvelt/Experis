#include "publisher.h"

namespace smartHome {
namespace mediator {

void Publisher::publishEvent(Event* _event)
{
  //m_eventsWQ.push(_event);
  m_eventsWQ.enqueue(_event);

}

Event* Publisher::getEvent()
{
  //Event* eventp = m_eventsWQ.front();
  //m_eventsWQ.pop();
  //return eventp;
  return m_eventsWQ.dequeue();
}

}} // smartHome::mediator
