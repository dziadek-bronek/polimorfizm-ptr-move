#include "include/CSelector.hpp"
#include "include/CSimpleSelector.hpp"

#if 0
CSelectorIf* CSelectorIf::createNew(void* selectorCoreVoidPtr)
{
    return nullptr;

    // here static cast and based on this return correspondig selector

    if (nullptr == selectorCoreVoidPtr)
    {
        return createNewCSimpleSelector(selectorCoreVoidPtr);
    }

    return createNewCSelector(selectorCoreVoidPtr);
}
#endif
