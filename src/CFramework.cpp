#include "include/CChildSelector.hpp"
#include "include/CParent.hpp"

#include "include/CSelectorConfigurator.hpp"

#include "include/throw.hpp"

#include "include/CFrameworkIf.hpp"
#include "include/CInput.hpp"

#include <cstdio>
#include <memory>

struct CFramework : CFrameworkIf {
  CFramework(void* selectorInitConfigVoidPtr) {
    childSelector = std::unique_ptr<CChildSelectorIf>(
        CChildSelectorIf::createNew(selectorInitConfigVoidPtr));

    childSelectorCore = childSelector->init();
  }
  ~CFramework() { printf("CFramework destructor\n"); }

  virtual void configAction(int x, void* childCreatorVoidPtr) {
    std::unique_ptr<CParent> configChild((CParent*)getChildBasedOnNumber(x));

    if (nullptr == configChild) {
      printf("No action allowed in current configuration of selection!!!\n");
      return;
    }

    struct CActionParams {
      void* mapPtr;
      void* creator;
    } actionParams = {.mapPtr = childSelectorCore,
                      .creator = childCreatorVoidPtr};
    configChild->action(&actionParams);
  }

  virtual void mainLoop(void* inputVoidPtr) {
    CInput* input = (CInput*)inputVoidPtr;
    for (int event = input->getCurrentEvent();;
         event = input->nextCurrentEvent() /* input++*/) {
      void* x = childSelector->newChildBasedOnEvent(event);
      if (x == nullptr) {
        printf("-------- UNKNOWN EVENT %i.\n", event);
        continue;
      }
      std::unique_ptr<CParent> child((CParent*)x);
      child->action();
    }
  }

 private:
  void* getChildBasedOnNumber(int n) {
    return childSelector->newChildBasedOnEvent(n);
  }

  std::unique_ptr<CChildSelectorIf> childSelector;
  void* childSelectorCore;
};

CFrameworkIf* newCFramework(void* selectorInitConfigVoidPtr) {
  return new CFramework(selectorInitConfigVoidPtr);
}
