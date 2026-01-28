#ifndef CHILD_CREATOR_HPP
#define CHILD_CREATOR_HPP

#include"parent.hpp"

struct CChildCreatorIf {
    CChildCreatorIf() = default;
    CChildCreatorIf(int number){} 
    virtual CParent* createNewChildIfIsNumber(int number_) = 0;
    virtual ~CChildCreatorIf() {}

    void printoutOnConstructor(int number_);
    void printoutOnCreateNewChild(int number_);
    void printoutOnDestructor(int number_);

};

#endif
