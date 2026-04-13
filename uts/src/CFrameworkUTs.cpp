#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/include/CFramework.hpp"

#include "../../src/include/CInputIf.hpp"
#include "../../src/include/CSelectorConfiguratorIf.hpp"
#include "../../src/include/CSelectorIf.hpp"

struct CChecker
{
    virtual void CSelectorConfiguratorMockConstructor() = 0;
    virtual void CSelectorMockConstructor() = 0;
    virtual void CSelectorConfiguratorMockDestructor() = 0;
    virtual void CSelectorMockDestructor() = 0;
};

struct CCheckerMock : CChecker
{
    MOCK_METHOD(void, CSelectorConfiguratorMockConstructor, (), (override));
    MOCK_METHOD(void, CSelectorMockConstructor, (), (override));
    MOCK_METHOD(void, CSelectorConfiguratorMockDestructor, (), (override));
    MOCK_METHOD(void, CSelectorMockDestructor, (), (override));
};

CCheckerMock* checkerMockPtr;

// CSelectorIf* createNewCSelectorMock();

CSelectorIf::~CSelectorIf() {}

// CSelectorIf* CSelectorIf::createNew() {return createNewCSelectorMock(); }

struct CSelectorMock : CSelectorIf
{
    CSelectorMock()
    {
        checkerMockPtr->CSelectorMockConstructor();
    }
    virtual ~CSelectorMock()
    {
        checkerMockPtr->CSelectorMockDestructor();
    }

    virtual void* at(int event)
    {
        return nullptr;
    }
};
// CSelectorIf* createNewCSelectorMock() { return new CSelectorMock; }

CSelectorMock* selectorMockPtr;

//-------------

CSelectorConfiguratorIf* createNewCSelectorConfiguratorMock();

CSelectorConfiguratorIf::~CSelectorConfiguratorIf() {}

CSelectorConfiguratorIf* CSelectorConfiguratorIf::createNew(
    void* initConfigVoidPtr)
{
    return createNewCSelectorConfiguratorMock();
}

struct CSelectorConfiguratorMock : CSelectorConfiguratorIf
{
    CSelectorConfiguratorMock()
    {
        checkerMockPtr->CSelectorConfiguratorMockConstructor();
    }

    virtual ~CSelectorConfiguratorMock()
    {
        checkerMockPtr->CSelectorConfiguratorMockDestructor();
    }
    virtual void* initializeSelector()
    {
        return new CSelectorMock;
    }
};
CSelectorConfiguratorIf* createNewCSelectorConfiguratorMock()
{
    return new CSelectorConfiguratorMock;
}

CSelectorConfiguratorMock* selectorConfiguratorMockPtr;

struct CInput : CInputIf
{
    virtual void init(void* sequenceOfEvents_) {}
    virtual int getCurrentEvent()
    {
        return 0;
    }
    virtual int nextCurrentEvent()
    {
        return 0;
    }
    virtual void setCurrentEvent() {}
};

TEST(CFrameworkUTs, CreateCSimpleConfigurator)
{
    CCheckerMock checkerMock;
    checkerMockPtr = &checkerMock;

    try
    {
        EXPECT_CALL(checkerMock, CSelectorConfiguratorMockConstructor());
        EXPECT_CALL(checkerMock, CSelectorMockConstructor());

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(nullptr));
        EXPECT_CALL(checkerMock, CSelectorMockDestructor());
        EXPECT_CALL(checkerMock, CSelectorConfiguratorMockDestructor());
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

#if 0
TEST(CFrameworkUTs, CreateCConfigurator)
{
    // int checkerInt = 0;
    // checkerIntPtr = &checkerInt;

    CCheckerMock checkerMock;
    checkerMockPtr = &checkerMock;

    try
    {
        EXPECT_CALL(checkerMock, CSelectorConfiguratorMockConstructor());
        std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});
        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));
        // EXPECT_EQ(checkerInt, 2);
        EXPECT_CALL(checkerMock, CSelectorConfiguratorMockDestructor());
    }
    catch (...)
    {
	    ASSERT_TRUE(false);
    }
}
#endif
