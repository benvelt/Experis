#include "event.h"

namespace smartHome {

Event::Event(std::string _subject)
: m_subject(_subject)
{ }

const std::string& Event::getSubject() const
{
  return m_subject;
}


}
