#include "factory.h"
#include "dispatcher.h"
#include "publisher.h"
#include "subManager.h"
#include "icontroller.h"
#include "fireCtrl.h"
#include "waterCtrl.h"
#include "idevice.h"
#include "fireSensor.h"
#include "waterSensor.h"
#include "configurator.h"



int main()
{
  using namespace smartHome;
  using namespace mediator;
  using namespace configuration;

  Factory factory("./src/lib/");
  Publisher pub;
  SubManager subM;
  Dispatcher disp(pub, subM);
  Configurator config("./config/config.txt");
  config.parsing();

  std::string ID[] = {"1","2","3","4","5"};
  std::string types[] = {"philips","philips","philips","philips","philips"};
  std::string rooms[] = {"1","3","1","1","1"};
  int floors[] = {1, 1, 1, 1, 1};

  IDevice* fSens = factory.Create(ID[3],"fireSensor", rooms[3], floors[3]);
  IDevice* wSens = factory.Create(ID[4],"waterSensor", rooms[4], floors[4]);

  IDevice* ctrl1 = factory.Create(ID[0],"fireCtrl", rooms[0], floors[0]);
  IDevice* ctrl2 = factory.Create(ID[1],"fireCtrl", rooms[1], floors[1]);
  IDevice* ctrl3   = factory.Create(ID[2],"waterCtrl", rooms[2], floors[2]);


  ctrl1->init(&subM, &pub);
  ctrl2->init(&subM, &pub);
  ctrl3->init(&subM, &pub);

  fSens->init(&subM, &pub);
  wSens->init(&subM, &pub);

  disp.run();

  while(1) {

  }

  return 0;
}
