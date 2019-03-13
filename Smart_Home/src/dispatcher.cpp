#include <set>
#include <unistd.h>

#include "dispatcher.h"
#include "event.h"

namespace smartHome {
namespace mediator {

Dispatcher::Dispatcher(Publisher& _publisher,SubManager& _subManager)
: m_publisher(_publisher)
, m_subManager(_subManager)
{ }

void Dispatcher::dispatch()
{
  Event* ep = m_publisher.getEvent();
  const std::string& epSbjct = ep->getSubject();
  std::set<IController*> ctrlsSet = m_subManager.getBySubject(epSbjct);

  std::set<IController*>::iterator itrEnd = ctrlsSet.end();
  for(std::set<IController*>::iterator itr = ctrlsSet.begin(); itr != itrEnd; itr++)
  {
    (*itr)->runEvent(ep);
  }
}

void Dispatcher::run()
{
  while(1)
  {
    dispatch();
    usleep(200000);
  }
}


}} // smartHome::mediator
