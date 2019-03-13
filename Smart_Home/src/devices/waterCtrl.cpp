#include <iostream>

#include "waterCtrl.h"

namespace smartHome {

extern "C" IDevice* Create(const char* _id, const char* _type, const char* _room, int _floor, const char* _log, const char* _config)
{
  return new WaterCtrl(_id, _type, _room, _floor, _log, _config);
}

WaterCtrl::WaterCtrl(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config)
: IDevice(_id, _type, _room, _floor, _log, _config)
, m_subject("water")
, m_sub(0)
{ }

void WaterCtrl::runEvent(const Event* _event)
{
  std::cout << "got event : " << _event->getSubject() << '\n';
}

void WaterCtrl::init(mediator::SubManager* _sub, mediator::Publisher* _pub)
{
  m_sub = _sub;
  m_sub->subscribe(m_subject, this);
}


} // smartHome
