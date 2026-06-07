#ifndef CFRAMEWORKIF_HPP
#define CFRAMEWORKIF_HPP

// #include "VOID.hpp"
#include <memory>

struct CFrameworkIf
{
    virtual ~CFrameworkIf() = default;

    virtual void* getChildBasedOnNumber(int n) = 0;

    virtual void configAddCreator(void* childCreatorVoidPtr) = 0;
    virtual void* configAdd(const char* fileName, const char* constructorName,
                            const char* destructorName, int id) = 0;
    virtual void* configAdd(const char* fileName, const char* constructorName,
                            const char* destructorName, int id,
                            void* initParameterVoidPtr) = 0;

    virtual void mainLoop(void* inputVoidPtr) = 0;
};

#endif
