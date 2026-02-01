#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

struct CCreatorsRegisterIf  {
    static CCreatorsRegisterIf* createNew();    
    virtual ~CCreatorsRegisterIf() {}      
    virtual void init() = 0;
    virtual void* newChildBasedOnEvent(int event) = 0;
};

#endif