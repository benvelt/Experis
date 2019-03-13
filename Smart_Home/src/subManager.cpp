#include <iostream>
#include <stdexcept>

#include "subManager.h"

namespace smartHome {
namespace mediator {


void SubManager::subscribe(const std::string& _subject, IController* _ctrl)
{
  if(!_ctrl) {
    throw std::runtime_error("null control pointer");
  }

  m_ctrls[_subject].insert(_ctrl);
}

std::set<IController*> SubManager::getBySubject(const std::string& _subject)
{
  return m_ctrls[_subject];
}

}}
