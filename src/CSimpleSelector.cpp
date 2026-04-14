#include "include/CSimpleSelector.hpp"
#include "include/CSelectorConfiguratorIf.hpp"
#include "include/child-creator.hpp"
#include <cstdio>

struct CSimpleSelector : CSelectorIf
{
    CSimpleSelector(void* singleCreatorVoidPtr)
        : singleCreatorPtr((CChildCreatorIf*)singleCreatorVoidPtr)
    {
        printf("The simple child selector: constructing\n");
        fflush(NULL);
    }
    virtual ~CSimpleSelector()
    {
        printf("The simple child selector: destructing\n");
        delete singleCreatorPtr;
        singleCreatorPtr = nullptr;
    }

    virtual void* at(int event)
    {
        return singleCreatorPtr->createNewChildIfIsNumber(event);
    }

  private:
    CChildCreatorIf* singleCreatorPtr;
};

CSelectorIf* createNewCSimpleSelector(void* singleCreatorVoidPtr)
{
    return new CSimpleSelector(singleCreatorVoidPtr);
};
