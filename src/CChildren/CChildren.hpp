#ifndef CHILDREN_HPP
#define CHILDREN_HPP

#include "../include/CParent.hpp"

struct CChild1 : CParent
{
    CChild1();
    virtual ~CChild1();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

struct CChild2 : CParent
{
    CChild2();
    virtual ~CChild2();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

struct CChild3 : CParent
{
    CChild3();
    virtual ~CChild3();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

struct CChild4 : CParent
{
    CChild4();
    virtual ~CChild4();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

#endif
