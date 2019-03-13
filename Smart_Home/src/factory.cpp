#include <dlfcn.h>
#include <stdexcept>
#include <iostream>

#include "factory.h"

namespace smartHome {
namespace configuration {

using namespace std;

Factory::Factory(std::string _path)
: m_path(_path)
{ }


IDevice* Factory::Create(string _id, string _type, string _room, int _floor)
{
  std::string pathTmp = m_path;
  pathTmp += _type.c_str();
  pathTmp += ".so";

  void* handle = dlopen(pathTmp.c_str(), RTLD_NOW);
  if(!handle) {
    cout << dlerror() << endl;
    throw runtime_error("dl open failed");
  }

  IDevice* (*create)(const char*,const char*,const char*,int);
  *(void**)&create = dlsym(handle, "Create");

  if(!create) {
    throw runtime_error("could not find create function");
  }

  IDevice* newDevice;
  newDevice = create(_id.c_str(),_type.c_str(),_room.c_str(),_floor);

  return newDevice;
}


}} // smartHome::configuration
