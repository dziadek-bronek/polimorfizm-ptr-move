#include "include/CSimpleSelector.hpp"
#include "include/CSelectorConfigurator.hpp"
#include "include/child-creator.hpp"
#include <cstdio>

struct CSimpleSelector : CSelectorIf
{
    CSimpleSelector(void **selectorCoreVoidPtrVoidPtr)
        : singleCreator(nullptr)
    {
        printf("The simple child selector: constructing\n");
        fflush(NULL);
        *selectorCoreVoidPtrVoidPtr = &singleCreator;
    }
    virtual ~CSimpleSelector()
    {
        printf("The simple child selector: destructing\n");
        delete singleCreator;
        singleCreator = nullptr;
    }

    virtual void *at(int event)
    {
        return singleCreator->createNewChildIfIsNumber(event);
    }

  private:
    CChildCreatorIf *singleCreator;
};

CSelectorIf *createNewCSimpleSelector(void **selectorCoreVoidPtrVoidPtr)
{
    return new CSimpleSelector(selectorCoreVoidPtrVoidPtr);
};
