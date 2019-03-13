#ifndef __IDEVICE_H__
#define __IDEVICE_H__

#include <string>

#include "subManager.h"
#include "publisher.h"

namespace smartHome {

class IDevice {
public:
  IDevice(std::string _id, std::string _type, std::string _room, int _floor, std::string _log, std::string _config);
  virtual void init(mediator::SubManager* _sub, mediator::Publisher* _pub) = 0;

  const std::string& getID() const;
  const std::string& getType() const;
  const std::string& getRoom() const;
  int getFloor() const;
  const std::string& getConfig() const;

private:
  std::string m_id;
  std::string m_type;
  std::string m_room;
  int m_floor;
  std::string m_log;
  std::string m_config;
};

} // smartHome




#endif // __IDEVICE_H__
