#include "include/CSelectorIf.hpp"
#include "include/CSelector.hpp"
#include "include/CSimpleSelector.hpp"

CSelectorIf *CSelectorIf::createNew(void *initConfigVoidPtr)
{
    if (nullptr == initConfigVoidPtr)
    {
        return createNewCSimpleSelector();
    }

    return createNewCSelector(initConfigVoidPtr);
}

CSelectorIf::~CSelectorIf()
{
}
