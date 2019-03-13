#ifndef __WATERSENSOR_H__
#define __WATERSENSOR_H__

#include "publisher.h"
#include "event.h"
#include "idevice.h"
#include "runnable.h"

namespace smartHome {
using namespace mediator;

class WaterSensor : public IDevice, public advcpp::threads::Runnable {
public:
  WaterSensor(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config);

  virtual void init(mediator::SubManager* _sub, mediator::Publisher* _pub);
  virtual void run();

private:
  Event m_event;
  mediator::Publisher* m_pub;
};


} // smartHome



#endif // __WATERSENSOR_H__
