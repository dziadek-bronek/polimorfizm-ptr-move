#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

struct CCreatorsRegisterIf  {
    static CCreatorsRegisterIf* createNew();

    virtual void* getMapVoidPtr() = 0;
    virtual ~CCreatorsRegisterIf() {}
    virtual void registerr(void*,int) = 0;
    virtual void init() = 0;
    virtual void* newChildBasedOnEvent(int event) = 0;
};

#endif