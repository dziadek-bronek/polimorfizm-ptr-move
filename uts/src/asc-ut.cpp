
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <memory>
#include <vector>
#include "../../src/include/CChildren.hpp"
#include "../../src/include/CConfigChild.hpp"
// #include "../../src/include/CInput.hpp"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CSelectorConfigurator.hpp"
#include "../../src/include/child-creators.hpp"

struct CChecker {
  virtual void CSCMockConstructor() {}
  virtual void CSCMockDestructor() {}
  virtual void CChildMockConstructor() {}
  virtual void CChildMockDestructor() {}
};

struct CCheckerMock : CChecker {
  MOCK_METHOD(void, CSCMockConstructor, (), (override));
  MOCK_METHOD(void, CSCMockDestructor, (), (override));
  MOCK_METHOD(void, CChildMockConstructor, (), (override));
  MOCK_METHOD(void, CChildMockDestructor, (), (override));
};

CCheckerMock* checkerPtr;

using CSC = CSelectorConfigurator;

TEST(AdvancedSelectorConfigurator, ConstructAndDelete) {
  try {
    CCheckerMock checker;
    checkerPtr = &checker;

    struct CSCMock : CSC {
      CSCMock() { checkerPtr->CSCMockConstructor(); }
      ~CSCMock() { checkerPtr->CSCMockDestructor(); }
    };

    EXPECT_CALL(checker, CSCMockConstructor());

    // sc stands for selector configurator
    std::unique_ptr<CSCMock> sc(new CSCMock);

    EXPECT_CALL(checker, CSCMockDestructor());
  } catch (...) {
  }
}

TEST(AdvancedSelectorConfigurator,
     ConfigActionAddsChildWhichIsIncrementingParameter) {
  try {
    using CActionParameter = int;
    using CActionResult = int;

    struct CChildMock : CParent {
      CChildMock() { checkerPtr->CChildMockConstructor(); }
      virtual ~CChildMock() override { checkerPtr->CChildMockDestructor(); }

      virtual void* action(void* actionParameterVoidPtr) override {
        CActionParameter* actionParameterPtr =
            (CActionParameter*)actionParameterVoidPtr;
        ++(*actionParameterPtr);
        return actionParameterVoidPtr;
      }
    };

    CCheckerMock checker;
    checkerPtr = &checker;

    std::vector<int> selectorConfig({7});
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorConfig));

    {
      std::unique_ptr<CChildCreatorIf> mockChildCreator(
          new CChildCreator<CChildMock>(11));
      framework->configAction(222, &mockChildCreator);
    }

    constexpr int INIT_VALUE_RANDOM_EXAMPLE = 29;
    int actionParameter(INIT_VALUE_RANDOM_EXAMPLE);

    EXPECT_CALL(checker, CChildMockConstructor());

    std::unique_ptr<CParent> childMock(
        (CParent*)framework->getChildBasedOnNumber(11));
    CActionResult* actionResultPtr =
        (CActionResult*)(childMock->action(&actionParameter));

    ASSERT_TRUE(nullptr != actionResultPtr);
    EXPECT_EQ(INIT_VALUE_RANDOM_EXAMPLE + 1, *actionResultPtr);
    EXPECT_EQ(actionParameter, *actionResultPtr);

    EXPECT_CALL(checker, CChildMockDestructor());

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
