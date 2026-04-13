#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/include/CChildren.hpp"
#include "../../src/include/CFrameworkIf.hpp"
#include "../../src/include/CInput.hpp"
#include "../../src/include/CSelectorConfigurator.hpp"
#include "../../src/include/child-creators.hpp"
#include <memory>
#include <vector>

struct CChecker
{
    virtual void childConstructor() {}
    virtual void creatorConstructor() {}
    virtual void childDestructor() {}
    virtual void creatorDestructor() {}
    virtual void action() {}
};

struct CCheckerMock : CChecker
{
    MOCK_METHOD(void, childConstructor, (), (override));
    MOCK_METHOD(void, creatorConstructor, (), (override));
    MOCK_METHOD(void, childDestructor, (), (override));
    MOCK_METHOD(void, creatorDestructor, (), (override));
    MOCK_METHOD(void, action, (), (override));
};

CCheckerMock* checkerPtr;

/* ====================================== */

TEST(MemoryManagement, ChildDestructor)
{
    CCheckerMock checker;
    checkerPtr = &checker;

    struct CChild : CParent
    {
      public:
        CChild()
        {
            checkerPtr->childConstructor();
        }
        virtual void action() override
        {
            checkerPtr->action();
        }
        virtual ~CChild() override
        {
            checkerPtr->childDestructor();
        }
    };

    EXPECT_CALL(checker, childConstructor());
    std::unique_ptr<CChild> child(new CChild);

    EXPECT_CALL(checker, childDestructor());
}
TEST(MemoryManagement, ChildCreatorDestructorInFrameworkZeroConfig)
{
    try
    {
        CCheckerMock checker;
        checkerPtr = &checker;

        struct CChildCreatorX : CChildCreator<CChild2>
        {
            CChildCreatorX(int id_)
                : CChildCreator<CChild2>(id_)
            {
                checkerPtr->creatorConstructor();
            }
            virtual ~CChildCreatorX() override
            {
                checkerPtr->creatorDestructor();
            }
        };

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(nullptr));

        {
            EXPECT_CALL(checker, creatorConstructor());

            std::unique_ptr<CChildCreatorIf> newCreator(new CChildCreatorX(8));

            framework->configAdd(&newCreator);

            EXPECT_CALL(checker, creatorDestructor());
        }

        std::unique_ptr<CInputIf> input(CInputIf::createNew());
        input->init(new std::vector<int>{8, 0, 7});

        framework->mainLoop(&input);
    }
    catch (const char* result)
    {
        EXPECT_STREQ("Clean exit (event 'EXIT' on input)", result);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

TEST(MemoryManagement, ChildCreatorDestructorInFramework)
{
    try
    {
        CCheckerMock checker;
        checkerPtr = &checker;

        struct CChildCreatorX : CChildCreator<CChild2>
        {
            CChildCreatorX(int id_)
                : CChildCreator<CChild2>(id_)
            {
                checkerPtr->creatorConstructor();
            }
            virtual ~CChildCreatorX() override
            {
                checkerPtr->creatorDestructor();
            }
        };

        std::vector<int> selectorInitConfig({7});

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));

        {
            EXPECT_CALL(checker, creatorConstructor());

            std::unique_ptr<CChildCreatorIf> newCreator(new CChildCreatorX(8));

            framework->configAdd(&newCreator);

            EXPECT_CALL(checker, creatorDestructor()).Times(0);
        }

        std::unique_ptr<CInputIf> input(CInputIf::createNew());
        input->init(new std::vector<int>{8, 0, 7});

        EXPECT_CALL(checker, creatorDestructor());

        framework->mainLoop(&input);
    }
    catch (const char* result)
    {
        EXPECT_STREQ("Clean exit (event 'EXIT' on input)", result);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

TEST(MemoryManagement, CustomChildInFrameworkConstructorActionDestructor)
{
    try
    {
        CCheckerMock checker;
        checkerPtr = &checker;

        struct CChild : CParent
        {
          public:
            CChild()
            {
                checkerPtr->childConstructor();
            }
            virtual ~CChild() override
            {
                checkerPtr->childDestructor();
            }
            virtual void action() override
            {
                checkerPtr->action();
            }
        };

        std::vector<int> selectorInitConfig({7});

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));

        std::unique_ptr<CChildCreatorIf> newCreator(
            new CChildCreator<CChild>(8));
        framework->configAdd(&newCreator);

        EXPECT_CALL(checker, childConstructor());
        EXPECT_CALL(checker, action());

        std::unique_ptr<CParent> childEvent8(
            (CParent*)framework->getChildBasedOnNumber(8));
        childEvent8->action();

        EXPECT_CALL(checker, childDestructor());
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

TEST(MemoryManagement, ChildDestructorInFrameworkParametrizedAction)
{
    try
    {
        CCheckerMock checker;
        checkerPtr = &checker;

        using CActionParameter = int;
        using CActionResult = int;

        struct CChild : CParent
        {
            CChild()
            {
                checkerPtr->childConstructor();
            }
            virtual ~CChild() override
            {
                checkerPtr->childDestructor();
            }

            virtual void* action(void* actionParameterVoidPtr) override
            {
                CActionParameter* actionParameterPtr =
                    (CActionParameter*)actionParameterVoidPtr;
                ++(*actionParameterPtr);
                return actionParameterVoidPtr;
            }
        };

        std::vector<int> selectorInitConfig({7});

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));

        std::unique_ptr<CChildCreatorIf> newCreator(
            new CChildCreator<CChild>(8));
        framework->configAdd(&newCreator);

        constexpr int INIT_VALUE_RANDOM_EXAMPLE = 29;
        int actionParameter(INIT_VALUE_RANDOM_EXAMPLE);

        EXPECT_CALL(checker, childConstructor());

        std::unique_ptr<CParent> x(
            (CParent*)framework->getChildBasedOnNumber(8));

        CActionResult* actionResultPtr =
            (CActionResult*)(x->action(&actionParameter));

        ASSERT_TRUE(nullptr != actionResultPtr);
        EXPECT_EQ(INIT_VALUE_RANDOM_EXAMPLE + 1, *actionResultPtr);
        EXPECT_EQ(actionParameter, *actionResultPtr);

        EXPECT_CALL(checker, childDestructor());
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

TEST(MemoryManagement, ChildDestructorInFrameworkLoop)
{
    try
    {
        struct CChild : CParent
        {
          public:
            CChild()
            {
                checkerPtr->childConstructor();
            }
            virtual ~CChild() override
            {
                checkerPtr->childDestructor();
            }
            virtual void action() override
            {
                checkerPtr->action();
            }
        };

        CCheckerMock checker;
        checkerPtr = &checker;

        std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});

        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(&selectorInitConfig));

        std::unique_ptr<CChildCreatorIf> newCreator(
            new CChildCreator<CChild>(8));
        framework->configAdd(&newCreator);

        std::unique_ptr<CInputIf> input(CInputIf::createNew());
        input->init(new std::vector<int>{8, 0, 7});

        EXPECT_CALL(checker, childConstructor());
        EXPECT_CALL(checker, action());
        EXPECT_CALL(checker, childDestructor());

        framework->mainLoop(&input);
    }

    catch (const char* result)
    {
        EXPECT_STREQ("Clean exit (event 'EXIT' on input)", result);
    }

    catch (...)
    {
        ASSERT_TRUE(false);
    }
}
