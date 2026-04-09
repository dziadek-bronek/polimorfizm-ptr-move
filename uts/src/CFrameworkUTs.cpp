#include "gtest/gtest.h"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CFramework.hpp"
#include "../../src/include/CSelectorIf.hpp"

int* checkerInt;

CSelectorIf* createNewCSimpleSelector() {
	*checkerInt = 1;
	return nullptr;
}

CSelectorIf* createNewCSelector(void* initConfigVoidPtr ) {
	*checkerInt = 2;
	return nullptr;
}


struct CSelector : CSelectorIf {
  virtual ~CSelector(){}

  virtual void* init(){return nullptr;}
  virtual void* newChildBasedOnEvent(int event){}
};


struct CSimpleSelector : CSelector {
  virtual ~CSimpleSelector(){}
};




TEST(CFrameworkUTSabc, CreateSelector) {
	int checker = 0;
	checkerInt = &checker;
try {

    {
	    std::unique_ptr<CFrameworkIf> framework(CFrameworkIf::createNew(nullptr));
	    EXPECT_EQ(checker, 2);

    }

    {
      std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});
	    std::unique_ptr<CFrameworkIf> framework(CFrameworkIf::createNew(&selectorInitConfig));
	    EXPECT_EQ(checker, 2);
    }


  } catch (...) {
  }
}
