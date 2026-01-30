#ifndef CHILD_CREATOR_HPP
#define CHILD_CREATOR_HPP

#include"parent.hpp"

    #include<cstdio>
template <typename PARENT>
struct CChildCreatorIf {
    CChildCreatorIf() = default;
    CChildCreatorIf(int number){} 
    virtual PARENT* createNewChildIfIsNumber(int number_) = 0;
    virtual ~CChildCreatorIf() {}


    void printoutOnConstructor(int number_) {
        printf("CChildCreator %i constructor\n", number_);
    }
  
    void printoutOnCreateNewChild(int number_) {
        printf("CChildCreator %i is creating new child\n", number_);
    }

    void printoutOnDestructor(int number_) {
        printf("CChildCreator %i destructor\n", number_);
    }


#if 0
    void printoutOnConstructor(int number_);
    void printoutOnCreateNewChild(int number_);
    void printoutOnDestructor(int number_);
#endif
 };

#endif
