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

    selectorConfigurator = std::unique_ptr<CSelectorConfiguratorIf> (CSelectorConfiguratorIf::createNew(selectorInitConfigVoidPtr));

    childSelector =
        std::unique_ptr<CChildSelectorIf>(CChildSelectorIf::createNew( selectorInitConfigVoidPtr));

    if (nullptr == selectorInitConfigVoidPtr) {
      selectorConfigurator->initSimple(childSelector->getConfig());
      return;
    }
      selectorConfigurator->init(childSelector->getConfig());
  }
  ~CFramework() { printf("CFramework destructor\n"); }

  virtual void configAction(int x, void* childCreatorVoidPtr) {

    void* selectorConfigReadyVoidPtr = childSelector->getConfig();

    if (nullptr == selectorConfigReadyVoidPtr) {
      printf("No action allowed in current configuration of selection!!!\n");
	    return;
    }
      struct CActionParams {
        void* mapPtr;
        void* creator;
      } actionParams = {.mapPtr = selectorConfigReadyVoidPtr,
                        .creator = childCreatorVoidPtr};

      std::unique_ptr<CParent> configChild((CParent*)getChildBasedOnNumber(x));

      if(nullptr == configChild) {
	      return;
      }

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

  virtual void* getChildBasedOnNumber(int n) {
    return childSelector->newChildBasedOnEvent(n);
  }

 private:
  std::unique_ptr<CChildSelectorIf> childSelector;
  std::unique_ptr<CSelectorConfiguratorIf> selectorConfigurator;
};

CFrameworkIf* CFrameworkIf::createNew(void* selectorConfigVoidPtr) {
  return new CFramework(selectorConfigVoidPtr);
}
