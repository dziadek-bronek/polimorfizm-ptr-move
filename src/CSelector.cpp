#include "include/CSelector.hpp"
#include "include/child-creator.hpp"

#include "include/CSelectorConfigurator.hpp"

#include "include/child-creator.hpp"

#include "include/throw.hpp"

#include <cstdio>
#include <list>
#include <memory>
#include <vector>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

struct CSelector : CSelectorIf {
  CSelector(void* selectorInitConfigVoidPtr) {
    selectorInitConfig = (std::vector<int>*)selectorInitConfigVoidPtr;
    printf("The selector of child creators: constructing\n");
  }

  virtual ~CSelector() {
    printf("The selector of child creators: destructing\n");
  }

  virtual void* init() {
    initializeSelector(&map, selectorInitConfig);
    return &map;
  }

  virtual void* at(int event) {
    for (std::unique_ptr<CChildCreatorIf>& childCreator : map) {
      if (nullptr == childCreator) {
        THROW2("Clean exit", " (event 'EXIT' in sequenceOfEvents)");
      }
      void* tryToGetChild = childCreator->createNewChildIfIsNumber(event);
      if (nullptr != tryToGetChild) {
        printf(
            "The selector of child creators: new child created based on event "
            "%i\n",
            event);
        return tryToGetChild;
      }
    }
    return nullptr;

    // THROW2("Exit", " on error: unknown event");
  }

 private:
  MapOfUptrChCrIf map;
  std::vector<int>* selectorInitConfig;
};

CSelectorIf* createNewCSelector(void* initConfigVoidPtr) {
  return new CSelector(initConfigVoidPtr);
}
