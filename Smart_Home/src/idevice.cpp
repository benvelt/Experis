#include "idevice.h"

namespace smartHome {

IDevice::IDevice(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config)
: m_id(_id)
, m_type(_type)
, m_room(_room)
, m_floor(_floor)
, m_log(_log)
, m_config(_config)
{ }

const std::string& IDevice::getID() const
{
  return m_id;
}

const std::string& IDevice::getType() const
{
  return m_type;
}

const std::string& IDevice::getRoom() const
{
  return m_room;
}

int IDevice::getFloor() const
{
  return m_floor;
}

const std::string& IDevice::getConfig() const
{
  return m_config;
}



}
