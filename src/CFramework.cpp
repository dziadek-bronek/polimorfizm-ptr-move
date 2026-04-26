#include "include/throw.hpp"
#include <cstdio>
#include <memory>

#include "include/CParent.hpp"

#include "include/CCreatorSelectorIf.hpp"

#include "CSelectorConfigurator/CSelectorConfiguratorIf.hpp"

#include "include/throw.hpp"

#include "include/CInputIf.hpp"

#include "include/CFramework.hpp"
#include "include/CSoConfiguratorProducer.hpp"

struct CFramework : CFrameworkIf
{
    CFramework(void* selectorInitConfigVoidPtr)
    {
        configurator = std::unique_ptr<CSelectorConfiguratorIf>(
            (CSelectorConfiguratorIf*)(produceNewCSoConfigurator(
                selectorInitConfigVoidPtr)));

        if (nullptr == configurator)
        {
            THROW2("TERMINATED", " - FATAL ERROR (configurator is nulptr in "
                                 "CFramework::CFramework())!");
        }

        selector = std::unique_ptr<CSelectorIf>(
            (CSelectorIf*)configurator->initializeSelector());

        if (nullptr == selector)
        {
            THROW2("TERMINATED", " - FATAL ERROR (selector is nulptr in "
                                 "CFramework::CFramework())!");
        }
    }

    ~CFramework()
    {
        printf("CFramework destructor\n");
    }

    virtual void* configAdd(const char* fileName, const char* constructorName,
                            const char* destructorName, int id)
    {
        std::unique_ptr<CParent> configChild((CParent*)selector->at(221));

        if (nullptr == configChild)
        {
            printf("------------------ PRODUCER NOT DEFINED!!!\n");
            return nullptr;
        }

        struct
        {
            const char* fileName;
            const char* constructorName;
            const char* destructorName;
            int id;
            void* initParameterVoidPtr;
        } soChildOrigin{fileName, constructorName, destructorName, id, nullptr};

        void* soChildCreator = configChild->action(&soChildOrigin);
        if (nullptr == soChildCreator)
        {
            printf("HOUSTON WEVE GOTTA PROBLEM\n");
            return nullptr;
        }

        return configAdd(soChildCreator);
    }

    virtual void* configAdd(void* childCreatorVoidPtr)
    {
        std::unique_ptr<CParent> configChild((CParent*)selector->at(222));

        if (nullptr == configChild)
        {
            printf(
                "No action allowed in current configuration of selection!!!\n");
            return childCreatorVoidPtr;
        }

        return configChild->action(childCreatorVoidPtr);
    }

    virtual void mainLoop(void* inputVoidPtr)
    {
        std::unique_ptr<CInputIf>& input =
            *((std::unique_ptr<CInputIf>*)inputVoidPtr);
        for (int event = input->getCurrentEvent();;
             event = input->nextCurrentEvent() /* input++*/)
        {
            std::unique_ptr<CParent> child((CParent*)(selector->at(event)));
            if (child == nullptr)
            {
                printf("-------- UNKNOWN EVENT %i.\n", event);
                continue;
            }
            child->action();
        }
    }

    virtual void* getChildBasedOnNumber(int n)
    {
        return selector->at(n);
    }

  private:
    std::unique_ptr<CSelectorConfiguratorIf> configurator;
    std::unique_ptr<CSelectorIf> selector;
};

CFrameworkIf* createNewCFramework(void* selectorInitConfigVoidPtr)
{
    return new CFramework(selectorInitConfigVoidPtr);
}
