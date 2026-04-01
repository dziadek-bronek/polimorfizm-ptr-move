
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <memory>
#include <vector>
// #include "../../src/include/CChildren.hpp"
// #include "../../src/include/CInput.hpp"
// #include "../../src/include/child-creators.hpp"
// #include "../../src/include/child-creators.hpp"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CSelectorConfigurator.hpp"

struct CChecker {
  virtual void scConstructor() {}
  virtual void scDestructor() {}
};

struct CCheckerMock : CChecker {
  MOCK_METHOD(void, scConstructor, (), (override));
  MOCK_METHOD(void, scDestructor, (), (override));
};

CCheckerMock* checkerPtr;

using CSC = CSelectorConfigurator;

TEST(AdvancedSelectorConfigurator, ConstructAndDelete) {
  try {
    CCheckerMock checker;
    checkerPtr = &checker;

    struct CSCMock : CSC {
      CSCMock() { checkerPtr->scConstructor(); }
      ~CSCMock() { checkerPtr->scDestructor(); }
    };

    EXPECT_CALL(checker, scConstructor());

    // sc stands for selector configurator
    std::unique_ptr<CSCMock> sc(new CSCMock);

    EXPECT_CALL(checker, scDestructor());
  } catch (...) {
  }
}

#if 0
TEST(AdvancedSelectorConfigurator, ConfiguredSelectorConstructAndDelete) {
  try {
    CCheckerMock checker;
    checkerPtr = &checker;

    struct CChildCreatorSelector : CSC {
      CSCMock() { checkerPtr->scConstructor(); }
      ~CSCMock() { checkerPtr->scDestructor(); }
    };

    std::vector<int> selectorConfig({7, -1, -1, -1, 4});

    EXPECT_CALL(checker, ChildCreatorSelectorConstructor());
    // sc stands for selector configurator
    std::unique_ptr<CSCMock> sc(new CSCMock);

    std::unique_ptr<CFrameworkIf> framework(CFrameworkIf::createNew(&sc));
    EXPECT_CALL(checker, ChildCreatorSelectorDestructor());
  } catch (...) {
  }
}
#endif
