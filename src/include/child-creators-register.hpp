#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

struct CCreatorsRegisterIf  {
    static CCreatorsRegisterIf* createNew(void* regConfigPtr);
    virtual ~CCreatorsRegisterIf() {}

    virtual void* newChildBasedOnEvent(int event) = 0;
};

#endif