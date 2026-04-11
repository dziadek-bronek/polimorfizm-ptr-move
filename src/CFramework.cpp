#include "include/CFramework.hpp"

#include "include/CParent.hpp"
#include "include/CSelectorIf.hpp"

#include "include/CSelectorConfigurator.hpp"

#include "include/throw.hpp"

#include "include/CInputIf.hpp"
#include "include/throw.hpp"

#include <cstdio>
#include <memory>

struct CFramework : CFrameworkIf
{
    CFramework(void *selectorInitConfigVoidPtr)
        : selector(nullptr),
          childSelectorCore(nullptr)
    {
        if (nullptr ==
            (selector = CSelectorIf::createNew(selectorInitConfigVoidPtr)))
        {
            THROW2("TERMINATED", " - FATAL ERROR (selector is nulptr in "
                                 "CFramework::CFramework())!");
        }

        if (nullptr == (childSelectorCore = selector->init()))
        {
            THROW2("TERMINATED",
                   " - FATAL ERROR (childSelectorCore is nulptr in "
                   "CFramework::CFramework())!");
        }
    }

    ~CFramework()
    {
        printf("CFramework destructor\n");
        delete selector;
        selector = nullptr;
    }

    virtual void configAction(int x, void *childCreatorVoidPtr)
    {
        std::unique_ptr<CParent> configChild((CParent *)selector->at(x));

        if (nullptr == configChild)
        {
            printf(
                "No action allowed in current configuration of selection!!!\n");
            return;
        }

        struct CActionParams
        {
            void *mapPtr;
            void *creator;
        } actionParams = {.mapPtr = childSelectorCore,
                          .creator = childCreatorVoidPtr};
        configChild->action(&actionParams);
    }

    virtual void mainLoop(void *inputVoidPtr)
    {
        std::unique_ptr<CInputIf> &input =
            *((std::unique_ptr<CInputIf> *)inputVoidPtr);
        for (int event = input->getCurrentEvent();;
             event = input->nextCurrentEvent() /* input++*/)
        {
            void *x = selector->at(event);
            if (x == nullptr)
            {
                printf("-------- UNKNOWN EVENT %i.\n", event);
                continue;
            }
            std::unique_ptr<CParent> child((CParent *)x);
            child->action();
        }
    }

    virtual void *getChildBasedOnNumber(int n)
    {
        return selector->at(n);
    }

  private:
    CSelectorIf *selector;
    void *childSelectorCore;
};

CFrameworkIf *createNewCFramework(void *selectorInitConfigVoidPtr)
{
    return new CFramework(selectorInitConfigVoidPtr);
}
