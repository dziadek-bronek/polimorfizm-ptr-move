#include "include/CChildSelector.hpp"
#include "include/CParent.hpp"

#include "include/CSelectorConfigurator.hpp"

#include "include/throw.hpp"

#include "include/CFrameworkIf.hpp"
#include "include/CInput.hpp"

#include <cstdio>
#include <memory>

struct CFramework : CFrameworkIf {
  CFramework(void* selectorConfiguratorVoidPtr) {
    selectorConfiguratorPtr =
        ((std::unique_ptr<
            CSelectorConfiguratorIf>*)(selectorConfiguratorVoidPtr));

    childSelector =
        std::unique_ptr<CChildSelectorIf>(CChildSelectorIf::createNew(
            (*selectorConfiguratorPtr)->getInitConfig()));

    if (nullptr == (*selectorConfiguratorPtr)->getInitConfig()) {
      (*selectorConfiguratorPtr)->initSimple(childSelector->getConfig());
    } else {
      (*selectorConfiguratorPtr)->init(childSelector->getConfig());
    }
  }
  ~CFramework() { printf("CFramework destructor\n"); }

  virtual void configAction(int x, void* childCreatorVoidPtr) {
    void* selectorConfigReadyVoidPtr = childSelector->getConfig();
    if (selectorConfigReadyVoidPtr) {
      struct CActionParams {
        void* mapPtr;
        void* creator;
      } actionParams = {.mapPtr = selectorConfigReadyVoidPtr,
                        .creator = childCreatorVoidPtr};

      std::unique_ptr<CParent> configChild((CParent*)getChildBasedOnNumber(x));
      configChild->action(&actionParams);
    }

    else {
      printf("No action allowed in current configuration of selection!!!\n");
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

  virtual void* getChildBasedOnNumber(int n) {
    return childSelector->newChildBasedOnEvent(n);
  }

 private:
  std::unique_ptr<CChildSelectorIf> childSelector;
  std::unique_ptr<CSelectorConfiguratorIf>* selectorConfiguratorPtr;
};

CFrameworkIf* CFrameworkIf::createNew(void* selectorConfigVoidPtr) {
  return new CFramework(selectorConfigVoidPtr);
}
