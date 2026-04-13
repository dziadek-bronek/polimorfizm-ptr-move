#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/include/CSelectorConfigurator.hpp"
#include "../../src/include/CSelectorConfiguratorIf.hpp"

#include "../../src/include/CSelectorIf.hpp"

struct CChecker
{
    virtual void CSimpleSelectorMockConstructor() = 0;
    virtual void CSelectorMockConstructor() = 0;
    virtual void CSimpleSelectorMockDestructor() = 0;
    virtual void CSelectorMockDestructor() = 0;
};

struct CCheckerMock : CChecker
{
    MOCK_METHOD(void, CSimpleSelectorMockConstructor, (), (override));
    MOCK_METHOD(void, CSelectorMockConstructor, (), (override));
    MOCK_METHOD(void, CSimpleSelectorMockDestructor, (), (override));
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

CSelectorMock* selectorMockPtr;

TEST(CSelectorConfiguratorUTs, CConfiguratorInitializesSelector)
{

    try
    {
        CCheckerMock checkerMock;
        checkerMockPtr = &checkerMock;

        std::vector<int> initConfig{7, 3};
        std::unique_ptr<CSelectorConfiguratorIf> configurator(
            (CSelectorConfiguratorIf*)createNewCSelectorConfigurator(
                &initConfig));

        EXPECT_CALL(checkerMock, CSelectorMockConstructor());

        std::unique_ptr<CSelectorIf> selector(
            (CSelectorIf*)configurator->initializeSelector());

        EXPECT_CALL(checkerMock, CSelectorMockDestructor());
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}
#if 0
TEST(CConfiguratorUTs, CreateConfigChildNotDefinedTest1){
}

TEST(CConfiguratorUTs, CreateConfigChildNotDefinedTest2){
}
#endif
