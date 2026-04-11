#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/include/CFramework.hpp"

#include "../../src/include/CInputIf.hpp"
#include "../../src/include/CSelectorIf.hpp"

struct CChecker {
  virtual void CSimpleSelectorConstructor() {}
  virtual void CSelectorConstructor() {}
  virtual void CSimpleSelectorDestructor() {}
  virtual void CSelectorDestructor() {}
};

struct CCheckerMock : CChecker {
  MOCK_METHOD(void, CSimpleSelectorConstructor, (), (override));
  MOCK_METHOD(void, CSelectorConstructor, (), (override));
  MOCK_METHOD(void, CSimpleSelectorDestructor, (), (override));
  MOCK_METHOD(void, CSelectorDestructor, (), (override));
};

CCheckerMock* checkerMockPtr;
int* checkerIntPtr;

struct CSimpleSelector : CSelectorIf {
  CSimpleSelector() { checkerMockPtr->CSimpleSelectorConstructor(); }
  virtual ~CSimpleSelector() { checkerMockPtr->CSimpleSelectorDestructor(); }
  virtual void* init() { return nullptr; }
  virtual void* at(int event) { return 0; }
};

struct CSelector : CSelectorIf {
  CSelector() { checkerMockPtr->CSelectorConstructor(); }
  virtual ~CSelector() { checkerMockPtr->CSelectorDestructor(); }
  virtual void* init() { return nullptr; }
  virtual void* at(int event) { return 0; }
};

CSelectorIf* createNewCSimpleSelector() {
  *checkerIntPtr = 1;
  return new CSimpleSelector;
}

CSelectorIf* createNewCSelector(void* initConfigVoidPtr) {
  *checkerIntPtr = 2;
  return new CSelector;
}

struct CInput : CInputIf {
  virtual void init(void* sequenceOfEvents_) {}
  virtual int getCurrentEvent() { return 0; }
  virtual int nextCurrentEvent() { return 0; }
  virtual void setCurrentEvent() {}
};

TEST(CFrameworkUTSabc, CreateCSimpleSelector) {
  int checkerInt = 0;
  checkerIntPtr = &checkerInt;

  CCheckerMock checkerMock;
  checkerMockPtr = &checkerMock;
  try {
    EXPECT_CALL(checkerMock, CSimpleSelectorConstructor());
    std::unique_ptr<CFrameworkIf> framework(CFrameworkIf::createNew(nullptr));
    EXPECT_EQ(checkerInt, 1);
    EXPECT_CALL(checkerMock, CSimpleSelectorDestructor());
  } catch (...) {
  }
}

TEST(CFrameworkUTSabc, CreateCSelector) {
  int checkerInt = 0;
  checkerIntPtr = &checkerInt;

  CCheckerMock checkerMock;
  checkerMockPtr = &checkerMock;

  try {
    EXPECT_CALL(checkerMock, CSelectorConstructor());
    std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorInitConfig));
    EXPECT_EQ(checkerInt, 2);
    EXPECT_CALL(checkerMock, CSelectorDestructor());
  } catch (...) {
  }
}
