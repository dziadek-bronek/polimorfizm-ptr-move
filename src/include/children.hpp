#ifndef CHILDREN_HPP
#define CHILDREN_HPP

#include"parent.hpp"

struct CChild1 : CParent {
    CChild1();
    virtual void action();
    virtual ~CChild1();
};

struct CChild2 : CParent {
    CChild2();
    virtual void action();
    virtual ~CChild2();
};

struct CChild3 : CParent {
    CChild3();;
    virtual void action();
    virtual ~CChild3();
};

#endif