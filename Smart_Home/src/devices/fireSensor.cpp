#include "fireSensor.h"
#include "thread.h"

namespace smartHome {

extern "C" IDevice* Create(const char* _id, const char* _type, const char* _room, int _floor, const char* _log, const char* _config)
{
  return new FireSensor(_id, _type, _room, _floor, _log, _config);
}

FireSensor::FireSensor(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config)
: IDevice(_id, _type, _room, _floor, _log, _config)
, m_event("fire")
, m_pub(0)
{ }

void FireSensor::init(mediator::SubManager* _sub, mediator::Publisher* _pub)
{
  m_pub = _pub;
  advcpp::threads::Thread t(*this);
}

void FireSensor::run()
{
  for(int i = 3; i > 0; --i)
  {
    m_pub->publishEvent(&m_event);
  }
}


} // smartHome
