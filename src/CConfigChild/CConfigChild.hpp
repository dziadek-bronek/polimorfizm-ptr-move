#ifndef CONFIG_CHILD_HPP
#define CONFIG_CHILD_HPP

#include "../include/CParent.hpp"

struct CConfigChild : CParent
{
    virtual ~CConfigChild();

    virtual void init(void* initParameterVoidPtr)
    {
        mapVoidPtr = initParameterVoidPtr;
    }
    virtual void* action(void* childCreatorVoidPtr) override;
    void* mapVoidPtr;
};

#endif
