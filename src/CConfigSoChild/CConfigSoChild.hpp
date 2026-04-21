#ifndef CONFIG_CHILD_HPP
#define CONFIG_CHILD_HPP

#include "../include/CParent.hpp"

struct CConfigSoChild : CParent
{
    virtual ~CConfigSoChild();

    virtual void init(void* initParameterVoidPtr)
    {
        mapVoidPtr = initParameterVoidPtr;
    }
    virtual void* action(void* childCreatorVoidPtr) override;
    void* mapVoidPtr;
};

#endif
