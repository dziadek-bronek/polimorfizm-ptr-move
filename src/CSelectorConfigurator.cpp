#include "include/CSelectorConfigurator.hpp"
#include <cstdio>
#include <list>
#include <memory>
#include "include/child-creators.hpp"

struct CSelectorConfigurator : CSelectorConfiguratorIf {
  CSelectorConfigurator(void* selectorInitConfigVoidPtr) {
    initConfigVoidPtr = selectorInitConfigVoidPtr;
  }

  virtual void* getInitConfig() { return initConfigVoidPtr; }
  virtual void setMap(void* _mapVoidPtr) { mapVoidPtr = _mapVoidPtr; }

  virtual void action(int x, void* childCreatorVoidPtr) {
    using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
    using MapOfUptrChCrIf = std::list<UptrChCrIf>;

    MapOfUptrChCrIf* mapPtr = (MapOfUptrChCrIf*)mapVoidPtr;
    UptrChCrIf* childCreatorPtr = (UptrChCrIf*)childCreatorVoidPtr;

    mapPtr->push_back(std::move(*childCreatorPtr));
  }

 private:
  void* initConfigVoidPtr;

  void* mapVoidPtr;
};

CSelectorConfiguratorIf* CSelectorConfiguratorIf::createNew(
    void* selectorInitConfigVoidPtr) {
  return new CSelectorConfigurator(selectorInitConfigVoidPtr);
}
