#include "CChildren/CChildren.hpp"
#include "include/child-creator.hpp"
#include "include/throw.hpp"
#include <cstdio>

struct CChildCreatorSimple : CChildCreatorIf
{
    virtual ~CChildCreatorSimple()
    {
        printf("ChildCreatorSimpleSelection destructor\n");
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        switch (id_)
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

CChildCreatorIf* createNewCChildCreatorSimple()
{
    return new CChildCreatorSimple();
}
