#ifndef CHILDREN_HPP
#define CHILDREN_HPP

#include"parent.hpp"
#include<cstdio>

struct CChild1 : CParent {
    CChild1() {printf("child 1 constructor\n");}
    virtual void action() { printf("behavior specific for child 1\n"); }
    virtual ~CChild1() {printf("child 1 destructor\n");}
};

struct CChild2 : CParent {
    CChild2() {printf("child 2 constructor\n");}
    virtual void action() { printf("behavior specific for child 2\n"); }
    virtual ~CChild2() {printf("child 2 destructor\n");}
};

struct CChild3 : CParent {
    CChild3() {printf("child 3 constructor\n");}
    virtual void action() { printf("behavior specific for child 3\n"); }
    virtual ~CChild3() {printf("child 3 destructor\n");}
};

CParent* createNewChild(int number) {
    if(1 == number) return new CChild1;
    if(2 == number) return new CChild2;
    if(3 == number) return new CChild3;
    throw "createNewChild problem";
}

#endif