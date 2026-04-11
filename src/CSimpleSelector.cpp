#include "include/CSimpleSelector.hpp"
#include <cstdio>
#include "include/CSelectorConfigurator.hpp"
#include "include/child-creator.hpp"

struct CSimpleSelector : CSelectorIf {
  CSimpleSelector() {
    singleCreator = nullptr;
    printf("The simple child selector: constructing\n");
    fflush(NULL);
  }
  virtual ~CSimpleSelector() {
    delete singleCreator;
    singleCreator = nullptr;
    printf("The simple child selector: destructing\n");
  }

  virtual void* init() {
    singleCreator = (CChildCreatorIf*)initializeSimpleSelector();
    return singleCreator;
  }

  virtual void* at(int event) {
    return singleCreator->createNewChildIfIsNumber(event);
  }

 private:
  CChildCreatorIf* singleCreator;
};

CSelectorIf* createNewCSimpleSelector() {
  return new CSimpleSelector();
};
