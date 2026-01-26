#ifndef PARENT_CREATOR_HPP
#define PARENT_CREATOR_HPP

#include"parent.hpp"
#include<memory>

struct CParentCreator {
    CParentCreator(int number): number(number) {}
    virtual std::unique_ptr<CParent> createNew() = 0;
    virtual ~CParentCreator() {};
    int number;
};

#endif