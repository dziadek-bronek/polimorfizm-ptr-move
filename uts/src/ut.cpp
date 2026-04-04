#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <memory>
#include <vector>
#include "../../src/include/CChildren.hpp"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CInput.hpp"
#include "../../src/include/child-creators.hpp"

struct CChecker {
  virtual void childConstructor() {}
  virtual void creatorConstructor() {}
  virtual void childDestructor() {}
  virtual void creatorDestructor() {}
  virtual void action() {}
};

struct CCheckerMock : CChecker {
  MOCK_METHOD(void, childConstructor, (), (override));
  MOCK_METHOD(void, creatorConstructor, (), (override));
  MOCK_METHOD(void, childDestructor, (), (override));
  MOCK_METHOD(void, creatorDestructor, (), (override));
  MOCK_METHOD(void, action, (), (override));
};

CCheckerMock* checkerPtr;

/* ====================================== */

TEST(MemoryManagement, Child1Destructor) {
  CCheckerMock checker;
  checkerPtr = &checker;

  struct CChildMock : CChild1 {
   public:
    CChildMock() { checkerPtr->childConstructor(); }
    virtual void action() override { checkerPtr->action(); }
    virtual ~CChildMock() override { checkerPtr->childDestructor(); }
  };

  EXPECT_CALL(checker, childConstructor());
  std::unique_ptr<CChildMock> childMock(new CChildMock);

  EXPECT_CALL(checker, childDestructor());
}

TEST(MemoryManagement, ChildCreatorDestructorInFramework) {
  try {
    CCheckerMock checker;
    checkerPtr = &checker;

    struct CChildCreatorMock : CChildCreator<CChild1> {
      CChildCreatorMock(int id_) : CChildCreator<CChild1>(id_) {
        checkerPtr->creatorConstructor();
      }
      virtual ~CChildCreatorMock() override { checkerPtr->creatorDestructor(); }
    };

    std::vector<int> selectorConfig({7});
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorConfig));

    EXPECT_CALL(checker, creatorConstructor());
    std::unique_ptr<CChildCreatorIf> newCreator(new CChildCreatorMock(8));

    framework->selectorConfigAdd(&newCreator);

    CInput input;
    input.init(new std::vector<int>{8, 0, 7});

    EXPECT_CALL(checker, creatorDestructor());

    framework->mainLoop(&input);
  } catch (...) {
  }
}

TEST(MemoryManagement, CustomChildInFrameworkConstructorActionDestructor) {
  try {
    struct CChildMock : CChild1 {
     public:
      CChildMock() { checkerPtr->childConstructor(); }
      virtual ~CChildMock() override { checkerPtr->childDestructor(); }
      virtual void action() override { checkerPtr->action(); }
    };

    CCheckerMock checker;
    checkerPtr = &checker;

    std::vector<int> selectorConfig({7});
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorConfig));

    std::unique_ptr<CChildCreatorIf> newCreator(
        new CChildCreator<CChildMock>(8));
    framework->selectorConfigAdd(&newCreator);

    EXPECT_CALL(checker, childConstructor());
    EXPECT_CALL(checker, action());

    std::unique_ptr<CParent> x((CParent*)framework->getChildBasedOnNumber(8));
    x->action();

    EXPECT_CALL(checker, childDestructor());
  } catch (...) {
  }
}

TEST(MemoryManagement, ChildDestructorInFrameworkParametrizedAction) {
  try {
    using CActionParameter = int;
    using CActionResult = int;
    struct CChildMock : CChild1 {
      CChildMock() { checkerPtr->childConstructor(); }
      virtual ~CChildMock() override { checkerPtr->childDestructor(); }

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

    std::unique_ptr<CChildCreatorIf> newCreator(
        new CChildCreator<CChildMock>(8));
    framework->selectorConfigAdd(&newCreator);

    constexpr int INIT_VALUE_RANDOM_EXAMPLE = 29;
    int actionParameter(INIT_VALUE_RANDOM_EXAMPLE);

    EXPECT_CALL(checker, childConstructor());

    std::unique_ptr<CParent> x((CParent*)framework->getChildBasedOnNumber(8));

    CActionResult* actionResultPtr =
        (CActionResult*)(x->action((void*)&actionParameter));

    EXPECT_EQ(INIT_VALUE_RANDOM_EXAMPLE + 1, *actionResultPtr);
    EXPECT_EQ(actionParameter, *actionResultPtr);

    EXPECT_CALL(checker, childDestructor());

  } catch (...) {
  }
}

TEST(MemoryManagement, ChildDestructorInFrameworkLoop) {
  try {
    struct CChildMock : CChild1 {
     public:
      CChildMock() { checkerPtr->childConstructor(); }
      virtual ~CChildMock() override { checkerPtr->childDestructor(); }
      virtual void action() override { checkerPtr->action(); }
    };

    CCheckerMock checker;
    checkerPtr = &checker;

    std::vector<int> selectorConfig({7, -1, -1, -1, 4});
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorConfig));

    std::unique_ptr<CChildCreatorIf> newCreator(
        new CChildCreator<CChildMock>(8));
    framework->selectorConfigAdd(&newCreator);

    CInput input;
    input.init(new std::vector<int>{8, 0, 7});

    EXPECT_CALL(checker, childConstructor());
    EXPECT_CALL(checker, action());
    EXPECT_CALL(checker, childDestructor());

    framework->mainLoop(&input);
  } catch (...) {
  }
}
