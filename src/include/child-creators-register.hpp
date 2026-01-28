#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

#include"parent.hpp"

#include<list>
#include<memory>

struct CCreatorsRegisterIf {
    static std::unique_ptr<CCreatorsRegisterIf> createNew();
    virtual void init() = 0;
    virtual std::unique_ptr<CParent> newChildBasedOnEvent(int event) = 0;
};


#endif