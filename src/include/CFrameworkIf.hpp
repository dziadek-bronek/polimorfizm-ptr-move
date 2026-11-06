#ifndef CFRAMEWORKIF_HPP
#define CFRAMEWORKIF_HPP

// #include "VOID.hpp"
#include <memory>

/* Forward declarations only: the header pulls no implementation types. */
struct CParent;
struct CEventSourceIf;

struct CFrameworkIf
{
    virtual ~CFrameworkIf() = default;

    /* The caller becomes the owner. Empty = nobody knows this number. */
    virtual std::unique_ptr<CParent> getChildBasedOnNumber(int n) = 0;

    virtual void configAddCreator(void* childCreatorVoidPtr) = 0;
    virtual void* configAdd(const char* fileName, const char* constructorName,
                            const char* destructorName, int id) = 0;
    virtual void* configAdd(const char* fileName, const char* constructorName,
                            const char* destructorName, int id,
                            void* initParameterVoidPtr) = 0;

    /* The framework runs the loop. The source is only borrowed.
       Returns normally when the source reports the end of events. */
    virtual void mainLoop(CEventSourceIf& source) = 0;
};

#endif
