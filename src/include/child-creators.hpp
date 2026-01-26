#ifndef CHILD_CREATORS_HPP
#define CHILD_CREATORS_HPP

#include"parent-creator.hpp"
#include"children.hpp"

#include<list>
#include<memory>

template <typename CHILD>
struct CChildCreator : CChildCreatorP {
    CChildCreator() = delete;
    CChildCreator(int number): CChildCreatorP(number) {
        printf("childCreator constructor %i\n", number);
    }
    virtual std::unique_ptr<CParent> createNew() {
        return std::unique_ptr<CParent> (new CHILD);
    }
    virtual ~CChildCreator() {
        printf("childCreator destructor %i\n", number);
        }
};




#endif