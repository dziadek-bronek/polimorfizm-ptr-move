#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

#include"parent.hpp"

struct CCreatorsRegisterIf {
    static CCreatorsRegisterIf* createNew();
    virtual void init() = 0;
    virtual CParent* newChildBasedOnEvent(int event) = 0;
    virtual ~CCreatorsRegisterIf(){}
};

#endif