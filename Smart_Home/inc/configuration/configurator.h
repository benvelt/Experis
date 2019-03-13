#ifndef __CONFIGURATOR_H__
#define __CONFIGURATOR_H__

#include <iostream>
#include <fstream>
#include <string>

#include "waitableq.h"
#include "deviceparams.h"

namespace smartHome {
namespace configuration {

class Configurator {
public:
  Configurator(std::string _fName);

  void parsing();
private:
  std::string m_fName;
  advcpp::threads::WaitableQueue<DeviceParams*> m_DPWQ;

};

}} // smartHome::configuration






#endif // __CONFIGURATOR_H__
