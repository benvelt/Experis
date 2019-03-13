#ifndef __ICONTROLLER_H__
#define __ICONTROLLER_H__

#include "event.h"

namespace smartHome {

class IController {
public:
  virtual ~IController();
  virtual void runEvent(const Event* _event) = 0;

private:

};


} // smartHome







#endif // __ICONTROLLER_H__
