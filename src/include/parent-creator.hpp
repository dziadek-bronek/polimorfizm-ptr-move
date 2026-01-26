#ifndef CHILD_CREATOR_PARENT_HPP
#define CHILD_CREATOR_PARENT_HPP

#include"parent.hpp"
#include<memory>

struct CChildCreatorP {
    CChildCreatorP(int number): number(number) {}
    virtual std::unique_ptr<CParent> createNew() = 0;
    virtual ~CChildCreatorP() {};
    int number;
};



#endif