#ifndef VOID_HPP
#define VOID_HPP
#include <cstdio>
struct VOID
{
    virtual ~VOID()
    {
        printf("VOID DESTRUCTOR\n");
    } //= default;
};
#endif
