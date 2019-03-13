#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <string>

#include "idevice.h"

namespace smartHome {
namespace configuration {

class Factory {
public:
  Factory(std::string _path);
  IDevice* Create(std::string _id, std::string _type, std::string _room, int _floor);
private:
  std::string m_path;
};

}} // smartHome::configuration


#endif // __FACTORY_H__
