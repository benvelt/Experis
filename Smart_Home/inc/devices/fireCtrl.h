#ifndef __FIRECTRL_H__
#define __FIRECTRL_H__

#include "icontroller.h"
#include "idevice.h"
#include "event.h"

namespace smartHome {

class FireCtrl : public IController, public IDevice {
public:
  FireCtrl(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config);

  virtual void runEvent(const Event* _event);
  virtual void init(mediator::SubManager* _sub, mediator::Publisher* _pub);

private:
  std::string m_subject;
  mediator::SubManager* m_sub;
};


} // smartHome



#endif // __FIRECTRL_H__
