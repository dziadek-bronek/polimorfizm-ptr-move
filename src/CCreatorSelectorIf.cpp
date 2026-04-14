#include "include/CSimpleSelector.hpp"
#include "include/CSelector.hpp"

#if 0
CSelectorIf* CSelectorIf::createNew(void** selectorCoreVoidPtrVoidPtr)
{
    return nullptr;
    if (nullptr == *selectorCoreVoidPtrVoidPtr)
    {
        return createNewCSimpleSelector(selectorCoreVoidPtrVoidPtr);
    }

    return createNewCSelector(selectorCoreVoidPtrVoidPtr);
}
#endif

CSelectorIf::~CSelectorIf() {}
