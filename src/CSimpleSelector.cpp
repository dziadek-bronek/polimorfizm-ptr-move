#include "include/CSimpleSelector.hpp"
#include "include/child-creator.hpp"
#include "include/CSelectorConfigurator.hpp"
#include <cstdio>

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
  virtual void* newChildBasedOnEvent(int event) {
    return singleCreator->createNewChildIfIsNumber(event);
  }

 private:
  CChildCreatorIf* singleCreator;
};

CSelectorIf* createNewCSimpleSelector(){
	return new CSimpleSelector();
};
