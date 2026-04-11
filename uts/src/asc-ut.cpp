
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/include/CChildren.hpp"
#include "../../src/include/CConfigChild.hpp"
#include <memory>
#include <vector>
// #include "../../src/include/CInput.hpp"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CSelectorConfigurator.hpp"
#include "../../src/include/child-creators.hpp"

struct CChecker
{
    virtual void CSCMockConstructor()
    {
    }
    virtual void CSCMockDestructor()
    {
    }
    virtual void CChildMockConstructor()
    {
    }
    virtual void CChildMockDestructor()
    {
    }
};

struct CCheckerMock : CChecker
{
    MOCK_METHOD(void, CSCMockConstructor, (), (override));
    MOCK_METHOD(void, CSCMockDestructor, (), (override));
    MOCK_METHOD(void, CChildMockConstructor, (), (override));
    MOCK_METHOD(void, CChildMockDestructor, (), (override));
};

CCheckerMock* checkerPtr;

#if 0
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
#endif

TEST(AdvancedSelectorConfigurator,
     ConfigChildActionAddsChildWhichIsIncrementingParameter)
{
    try
    {
        using CActionParameter = int;
        using CActionResult = int;

        struct CChildMock : CParent
        {
            CChildMock()
            {
                checkerPtr->CChildMockConstructor();
            }
            virtual ~CChildMock() override
            {
                checkerPtr->CChildMockDestructor();
            }

            virtual void* action(void* actionParameterVoidPtr) override
            {
                CActionParameter* actionParameterPtr =
                    (CActionParameter*)actionParameterVoidPtr;
                ++(*actionParameterPtr);
                return actionParameterVoidPtr;
            }
        };

        CCheckerMock checker;
        checkerPtr = &checker;

        std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));

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
        ASSERT_TRUE(nullptr != childMock);
        CActionResult* actionResultPtr =
            (CActionResult*)(childMock->action(&actionParameter));

        ASSERT_TRUE(nullptr != actionResultPtr);
        EXPECT_EQ(INIT_VALUE_RANDOM_EXAMPLE + 1, *actionResultPtr);
        EXPECT_EQ(actionParameter, *actionResultPtr);

        EXPECT_CALL(checker, CChildMockDestructor());
    }
    catch (...)
    {
    }
}

TEST(AdvancedSelectorConfigurator,
     ConfiguratorClassActionAddsChildWhichIsIncrementingParameter)
{
    try
    {
        using CActionParameter = int;
        using CActionResult = int;

        CCheckerMock checker;
        checkerPtr = &checker;

        struct CChildMock : CParent
        {
            CChildMock()
            {
                checkerPtr->CChildMockConstructor();
            }
            virtual ~CChildMock() override
            {
                checkerPtr->CChildMockDestructor();
            }

            virtual void* action(void* actionParameterVoidPtr) override
            {
                CActionParameter* actionParameterPtr =
                    (CActionParameter*)actionParameterVoidPtr;
                ++(*actionParameterPtr);
                return actionParameterVoidPtr;
            }
        };

        std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));

        {
            std::unique_ptr<CChildCreatorIf> mockChildCreator(
                new CChildCreator<CChildMock>(73));
            framework->configAction(222, &mockChildCreator);
        }

        constexpr int INIT_VALUE_RANDOM_EXAMPLE = 29;
        int actionParameter(INIT_VALUE_RANDOM_EXAMPLE);

        std::unique_ptr<CParent> childMock(
            (CParent*)framework->getChildBasedOnNumber(73));
        ASSERT_TRUE(nullptr != childMock);
        CActionResult* actionResultPtr =
            (CActionResult*)(childMock->action(&actionParameter));

        ASSERT_TRUE(nullptr != actionResultPtr);
        EXPECT_EQ(INIT_VALUE_RANDOM_EXAMPLE + 1, *actionResultPtr);
        EXPECT_EQ(actionParameter, *actionResultPtr);

        EXPECT_CALL(checker, CChildMockDestructor());
    }
    catch (...)
    {
    }
}

#if 0
TEST(AdvancedSelectorConfigurator, AdvancedSelectorVsSimpleSelector) {
try{


CSelectorConfig {

int type{1};
    std::vector<int> config{7}};
} selectorInitConfig;


    std::unique_ptr<CSelectorConfiguratorIf> selectorConfigurator(
        CSelectorConfiguratorIf::createNew(&selectorInitConfig));

    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorConfigurator));







  } catch (...) {
  }
}
#endif
