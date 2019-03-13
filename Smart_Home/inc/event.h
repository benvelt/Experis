#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

namespace smartHome {

class Event {
public:
  Event(std::string _subject);
  const std::string& getSubject() const;
private:
  std::string m_subject;
};

} // smartHome



#endif // __EVENT_H__
