#ifndef CFRAMEWORKIF_HPP
#define CFRAMEWORKIF_HPP

struct CFrameworkIf
{
    virtual ~CFrameworkIf() {}

    virtual void* getChildBasedOnNumber(int n) = 0;

    virtual void* configAdd(void* childCreatorUPtrVoidPtr) = 0;
    virtual void* configAdd(const char* fileName, const char* constructorName,
                            const char* destructorName, int id) = 0;

    virtual void mainLoop(void* inputVoidPtr) = 0;
};

#endif
