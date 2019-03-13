#ifndef __FIRESENSOR_H__
#define __FIRESENSOR_H__

#include "publisher.h"
#include "event.h"
#include "idevice.h"
#include "runnable.h"

namespace smartHome {
using namespace mediator;

class FireSensor : public IDevice, public advcpp::threads::Runnable {
public:
  FireSensor(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config);

  virtual void init(mediator::SubManager* _sub, mediator::Publisher* _pub);
  virtual void run();

private:
  Event m_event;
  mediator::Publisher* m_pub;
};


} // smartHome



#endif // __FIRESENSOR_H__
