#ifndef CONFIG_CHILD_HPP
#define CONFIG_CHILD_HPP

#include "CParent.hpp"

struct CConfigChild : CParent
{
#if 0
    CConfigChild(void* constructorParameterVoidPtr)
        : mapVoidPtr(constructorParameterVoidPtr)
    {
    }
#endif
    virtual ~CConfigChild();

    virtual void init(void* initParameterVoidPtr)
    {
        mapVoidPtr = initParameterVoidPtr;
    }
    virtual void* action(void* childCreatorVoidPtr) override;
    void* mapVoidPtr;
};

#endif
