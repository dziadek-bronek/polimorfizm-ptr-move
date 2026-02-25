#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <memory>
#include <vector>
#include "../../src/include/CChildren.hpp"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CInput.hpp"
#include "../../src/include/child-creators.hpp"

struct CChecker {
  virtual void constr() {}
  virtual void action() {}
  virtual void destr() {}
};

struct CCheckerMock : CChecker {
  MOCK_METHOD(void, constr, (), (override));
  MOCK_METHOD(void, action, (), (override));
  MOCK_METHOD(void, destr, (), (override));
};

CCheckerMock* checkerPtr;

struct CChildMock : CChild1 {
 public:
  CChildMock() { checkerPtr->constr(); }
  virtual void action() { checkerPtr->action(); }
  virtual ~CChildMock() { checkerPtr->destr(); }
};

/* ====================================== */

TEST(MemoryManagement, Child1Destructor) {
  CCheckerMock checker;
  checkerPtr = &checker;

  std::unique_ptr<CChildMock> childMock(new CChildMock);
  EXPECT_CALL(checker, destr());
}

TEST(MemoryManagement, ChildDestructorInFramework) {
  try {
    CCheckerMock checker;
    checkerPtr = &checker;

    std::vector<int> selectorConfig({7, -1, -1, -1, 4});
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorConfig));

    std::unique_ptr<CChildCreatorIf> newCreator(
        new CChildCreator<CChildMock>(8));
    // EXPECT_CALL(newCreator, constr());
    framework->selectorConfigAdd(&newCreator);

    CInput input;
    // input.init(new std::vector<int>{2, 4, 3, 8, 0, 7});

    input.init(new std::vector<int>{8, 0, 7});
    EXPECT_CALL(checker, constr());
    EXPECT_CALL(checker, action());
    EXPECT_CALL(checker, destr());

    framework->mainLoop(&input);

    // EXPECT_CALL(*newCreator, destr());
  } catch (...) {
  }
}
