#ifndef CHILD_CREATOR_HPP
#define CHILD_CREATOR_HPP

#include"parent.hpp"
#include<memory>
#include<list>

struct CChildCreator {
    CChildCreator() = delete;
    CChildCreator(int number): number(number) {
        printf("childCreator constructor %i\n", number);
    }    
    virtual std::unique_ptr<CParent> createNewChild() {
        printf("CChildCreator is creating new child id %i\n", number);
        return std::unique_ptr<CParent>(::createNewChild(number));
    }
    ~CChildCreator() {
        printf("childCreator destructor %i\n", number);
    }   
    
    int number;
};

void registerChildCreators(std::list<std::unique_ptr<CChildCreator>>& map);

#endif
