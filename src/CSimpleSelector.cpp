#include "include/CSimpleSelector.hpp"
#include "CChildren/CChildren.hpp"
#include "include/CSelectorConfiguratorIf.hpp"
#include "include/throw.hpp"
#include <cstdio>

struct CSimpleSelector : CSelectorIf
{
    CSimpleSelector()
    {
        printf("The simple child selector: constructing\n");
        fflush(NULL);
    }
    virtual ~CSimpleSelector()
    {
        printf("The simple child selector: destructing\n");
    }

    virtual void* at(int event)
    {
        switch (event)
        {
        case 0:
            THROW2("Clean exit", " (event 'EXIT' on input)");
        case 1:
            return createNewCChild1();
        case 2:
            return createNewCChild2();
        case 3:
            return createNewCChild3();
        case 4:
            return createNewCChild4();
        }
        return nullptr;
    }
};

CSelectorIf* createNewCSimpleSelector()
{
    return new CSimpleSelector();
};
