#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__


namespace advcpp {
namespace threads {

class Runnable {
public:
  ~Runnable();

  virtual void run() = 0;
private:
};


}} // advcpp::threads



#endif // __RUNNABLE_H__
