#ifndef CFRAMEWORKIF_HPP
#define CFRAMEWORKIF_HPP

struct CFrameworkIf
{
    static CFrameworkIf* createNew(void* selectorInitConfigVoidPtr);
    virtual ~CFrameworkIf() = 0;

    virtual void configAdd(void* childCreatorUPtrVoidPtr) = 0;
    virtual void mainLoop(void* inputVoidPtr) = 0;
    virtual void* getChildBasedOnNumber(int n) = 0;
};

#endif
