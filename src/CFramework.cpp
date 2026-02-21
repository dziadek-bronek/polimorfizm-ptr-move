#include "include/CChildSelector.hpp"
#include "include/CParent.hpp"

#include "include/selector-config.hpp"

#include "include/throw.hpp"

#include "include/CFrameworkIf.hpp"
#include "include/CInput.hpp"

#include <cstdio>
#include <memory>
#include <vector>
struct CFramework : CFrameworkIf {
  CFramework(void* selectorConfigVoidPtr) {
    childSelector = std::unique_ptr<CChildSelectorIf>(
        CChildSelectorIf::createNew(selectorConfigVoidPtr));
  }
  ~CFramework() { printf("CFramework destructor\n"); }

  virtual void selectorConfigAdd(void* childCreatorVoidPtr) {
    void* selectorConfigReadyVoidPtr = childSelector->getConfig();
    if (selectorConfigReadyVoidPtr) {
      configAdd(selectorConfigReadyVoidPtr, childCreatorVoidPtr);
    } else {
      printf("No Add allowed in current configuration of selection!!!\n");
    }
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
  std::unique_ptr<CChildSelectorIf> childSelector;
};

CFrameworkIf* CFrameworkIf::createNew(void* selectorConfigVoidPtr) {
  return new CFramework(selectorConfigVoidPtr);
}
