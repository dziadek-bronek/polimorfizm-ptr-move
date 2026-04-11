#ifndef CONFIG_CHILD_HPP
#define CONFIG_CHILD_HPP

#include "CParent.hpp"

struct CConfigChild : CParent
{
    CConfigChild(void* mapVoidPtr)
        : mapPtr(mapVoidPtr)
    {
    }
    virtual void* action(void* actionParameterVoidPtr) override;
    void* mapPtr;
};

#endif
