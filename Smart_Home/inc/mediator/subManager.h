#ifndef __SUBMANAGER_H__
#define __SUBMANAGER_H__

#include <set>
#include <map>
#include <string>

#include "icontroller.h"

namespace smartHome {
namespace mediator {

class SubManager {
public:
  virtual void subscribe(const std::string& _subject, IController* _ctrl);
  std::set<IController*> getBySubject(const std::string& _subject);
private:
  std::map<std::string, std::set<IController*> > m_ctrls;

};

}} // smartHome::mediator




#endif // __SUBMANAGER_H__
