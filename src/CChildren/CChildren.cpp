#include "CChildren.hpp"
#include <cstdio>

CChild1::CChild1()
{
    printf("constructor of CChild1\n");
}

CChild1::~CChild1()
{
    printf("destructor of CChild1\n");
}

void* CChild1::action(void* actionParameterVoidPtr)
{
    printf("behavior specific for child 1\n");
    return nullptr;
}

void CChild1::action()
{
    printf("behavior specific for child 1\n");
}

/*************************/

CChild2::CChild2()
{
    printf("constructor of CChild2\n");
}

CChild2::~CChild2()
{
    printf("destructor of CChild2\n");
}

void CChild2::action()
{
    printf("behavior specific for child 2\n");
}

void* CChild2::action(void* actionParameterVoidPtr)
{
    printf("behavior specific for child 2\n");
    return nullptr;
}
/*************************/

CChild3::CChild3()
{
    printf("constructor of CChild3\n");
}
CChild3::~CChild3()
{
    printf("destructor of CChild3\n");
}

void CChild3::action()
{
    printf("behavior specific for child 3\n");
}

void* CChild3::action(void* actionParameterVoidPtr)
{
    printf("behavior specific for child 3\n");
    return nullptr;
}

/*************************/
CChild4::CChild4()
{
    printf("constructor of CChild4\n");
}
CChild4::~CChild4()
{
    printf("destructor of CChild4\n");
}

void CChild4::action()
{
    printf("behavior specific for child 4\n");
}

void* CChild4::action(void* actionParameterVoidPtr)
{
    printf("behavior specific for child 4\n");
    return nullptr;
}
