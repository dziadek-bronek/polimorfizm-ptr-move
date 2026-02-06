#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

struct CChildSelectorIf  {
    static CChildSelectorIf* createNew(void* regConfigPtr);
    virtual ~CChildSelectorIf() {}

    virtual void* newChildBasedOnEvent(int event) = 0;
};

#endif