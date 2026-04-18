#ifndef CONFIG_CHILD_HPP
#define CONFIG_CHILD_HPP

#include "CParent.hpp"

struct CConfigChild : CParent
{
    CConfigChild() = default;
    CConfigChild(void* mapVoidPtr_)
        : mapVoidPtr(mapVoidPtr_)
    {
    }
    virtual ~CConfigChild();

    virtual void init(void* initParameterVoidPtr)
    {
        mapVoidPtr = initParameterVoidPtr;
    }
    virtual void* action(void* actionParameterVoidPtr) override;
    void* mapVoidPtr;
};

#endif
