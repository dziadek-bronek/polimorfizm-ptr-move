#ifndef CPARENT_HPP
#define CPARENT_HPP

struct CParent {
    virtual void action() = 0;
    virtual ~CParent() {};
};

CParent* createNewChild(int number);

#endif