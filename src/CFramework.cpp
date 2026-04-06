#include "include/CChildSelector.hpp"
#include "include/CParent.hpp"

#include "include/CSelectorConfigurator.hpp"
#include "include/selector-config.hpp"

#include "include/throw.hpp"

#include "include/CFrameworkIf.hpp"
#include "include/CInput.hpp"

#include <cstdio>
#include <memory>
struct CFramework : CFrameworkIf {
  CFramework(void* _selectorConfiguratorVoidPtr) {
    selectorConfiguratorVoidPtr = _selectorConfiguratorVoidPtr;

    std::unique_ptr<CSelectorConfiguratorIf>* selectorConfiguratorPtr =
        ((std::unique_ptr<
            CSelectorConfiguratorIf>*)(selectorConfiguratorVoidPtr));

    void* selectorCore = nullptr;
    if (nullptr != selectorConfiguratorPtr) {
      selectorCore = (*selectorConfiguratorPtr)->init();
    }

    childSelector = std::unique_ptr<CChildSelectorIf>(
        CChildSelectorIf::createNew(selectorCore));
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
  void* selectorConfiguratorVoidPtr;
};

CFrameworkIf* CFrameworkIf::createNew(void* selectorConfigVoidPtr) {
  return new CFramework(selectorConfigVoidPtr);
}
