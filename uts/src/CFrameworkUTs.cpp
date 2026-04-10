#include "gtest/gtest.h"

#include "../../src/include/CFramework.hpp"

#include "../../src/include/CSelectorIf.hpp"
#include "../../src/include/CInputIf.hpp"

int* checkerInt;

struct CSelector : CSelectorIf {
  virtual ~CSelector(){}

  virtual void* init(){return nullptr;}
  virtual void* newChildBasedOnEvent(int event){return 0;}
};

struct CSimpleSelector : CSelector {
  virtual ~CSimpleSelector(){}
};

CSelectorIf* createNewCSimpleSelector() {
	*checkerInt = 1;
	return new CSimpleSelector;
}

CSelectorIf* createNewCSelector(void* initConfigVoidPtr ) {
	*checkerInt = 2;
	return new CSelector;
}

struct CInput : CInputIf  {
  int indexOfCurrentEvent{0};
  std::unique_ptr<std::vector<int>> sequenceOfEvents;
  int currentEvent{0};

  virtual void init(void* sequenceOfEvents_) {}

  virtual int getCurrentEvent() {return 0;}

  virtual int nextCurrentEvent() {return 0;}

  virtual void setCurrentEvent() {}
};


TEST(CFrameworkUTSabc, CreateSelector) {
	int checker = 0;
	checkerInt = &checker;
try {

    {
	    std::unique_ptr<CFrameworkIf> framework(CFrameworkIf::createNew(nullptr));
	    EXPECT_EQ(checker, 1);

    }

    {
      std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});
	    std::unique_ptr<CFrameworkIf> framework(CFrameworkIf::createNew(&selectorInitConfig));
	    EXPECT_EQ(checker, 2);
    }

  } catch (...) {
  }
}
