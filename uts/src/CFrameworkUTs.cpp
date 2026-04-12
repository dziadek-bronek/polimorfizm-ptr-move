#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/include/CFramework.hpp"

#include "../../src/include/CInputIf.hpp"
#include "../../src/include/CSelectorConfiguratorIf.hpp"
#include "../../src/include/CSelectorIf.hpp"

struct CChecker
{
    virtual void CSimpleConfiguratorConstructor()
    {
    }
    virtual void CConfiguratorConstructor()
    {
    }
    virtual void CSimpleConfiguratorDestructor()
    {
    }
    virtual void CConfiguratorDestructor()
    {
    }
};

struct CCheckerMock : CChecker
{
    MOCK_METHOD(void, CSimpleConfiguratorConstructor, (), (override));
    MOCK_METHOD(void, CConfiguratorConstructor, (), (override));
    MOCK_METHOD(void, CSimpleConfiguratorDestructor, (), (override));
    MOCK_METHOD(void, CConfiguratorDestructor, (), (override));
};

CCheckerMock* checkerMockPtr;
int* checkerIntPtr;

struct CSelectorMock : CSelectorIf {

    virtual ~CSelectorMock(){}

    virtual void* at(int event) {return nullptr;}

};

struct CSimpleConfigurator : CSelectorConfiguratorIf
{
    CSimpleConfigurator()
    {
        checkerMockPtr->CSimpleConfiguratorConstructor();
    }
    virtual ~CSimpleConfigurator()
    {
        checkerMockPtr->CSimpleConfiguratorDestructor();
    }
    virtual void* initializeSelector()
    {
	    return new CSelectorMock();
    }
};

struct CConfigurator : CSelectorConfiguratorIf
{
    CConfigurator(void* initConfigVoidPtr)
    {
        checkerMockPtr->CConfiguratorConstructor();
    }
    virtual ~CConfigurator()
    {
        checkerMockPtr->CConfiguratorDestructor();
    }
    virtual void* initializeSelector()
    {
	    return new CSelectorMock();
    }
};

CSelectorConfiguratorIf* createNewCSimpleSelectorConfigurator()
{
    *checkerIntPtr = 1;
    return new CSimpleConfigurator;
}

CSelectorConfiguratorIf* createNewCSelectorConfigurator(void* initConfigVoidPtr)
{
    *checkerIntPtr = 2;
    return new CConfigurator(nullptr);
}

struct CInput : CInputIf
{
    virtual void init(void* sequenceOfEvents_)
    {
    }
    virtual int getCurrentEvent()
    {
        return 0;
    }
    virtual int nextCurrentEvent()
    {
        return 0;
    }
    virtual void setCurrentEvent()
    {
    }
};

TEST(CFrameworkUTs, CreateCSimpleConfigurator)
{
    int checkerInt = 0;
    checkerIntPtr = &checkerInt;

    CCheckerMock checkerMock;
    checkerMockPtr = &checkerMock;
    try
    {
        EXPECT_CALL(checkerMock, CSimpleConfiguratorConstructor());
        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(nullptr));
        EXPECT_EQ(checkerInt, 1);
        EXPECT_CALL(checkerMock, CSimpleConfiguratorDestructor());
    }
    catch (...)
    {
	    ASSERT_TRUE(false);
    }
}

TEST(CFrameworkUTs, CreateCConfigurator)
{
    int checkerInt = 0;
    checkerIntPtr = &checkerInt;

    CCheckerMock checkerMock;
    checkerMockPtr = &checkerMock;

    try
    {
        EXPECT_CALL(checkerMock, CConfiguratorConstructor());
        std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});
        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));
        EXPECT_EQ(checkerInt, 2);
        EXPECT_CALL(checkerMock, CConfiguratorDestructor());
    }
    catch (...)
    {
	    ASSERT_TRUE(false);
    }
}
