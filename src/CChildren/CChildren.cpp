#include "CChildren.hpp"
#include "../include/CParent.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>

struct CChild1 : CParent
{
    CChild1();
    virtual ~CChild1();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

struct CChild2 : CParent
{
    CChild2();
    virtual ~CChild2();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

struct CChild3 : CParent
{
    CChild3();
    virtual ~CChild3();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

struct CChild4 : CParent
{
    CChild4();
    virtual ~CChild4();
    virtual void action() override;
    virtual void* action(void* actionParameterVoidPtr) override;
};

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

void* createNewCChild1()
{
    return new CChild1;
}
void* createNewCChild2()
{
    return new CChild2;
}
void* createNewCChild3()
{
    return new CChild3;
}
void* createNewCChild4()
{
    return new CChild4;
}

static void* createNewCChild1Creator(int id)
{
    return new CChildCreator<CChild1>(id);
}
static void* createNewCChild2Creator(int id)
{
    return new CChildCreator<CChild2>(id);
}
static void* createNewCChild3Creator(int id)
{
    return new CChildCreator<CChild3>(id);
}
static void* createNewCChild4Creator(int id)
{
    return new CChildCreator<CChild4>(id);
}

void* createChildCreatorWithId(int childClass, int creatorId)
{
    switch (childClass)
    {
    case 1:
        return createNewCChild1Creator(creatorId);
    case 2:
        return createNewCChild2Creator(creatorId);
    case 3:
        return createNewCChild3Creator(creatorId);
    case 4:
        return createNewCChild4Creator(creatorId);
    }
    throw;
}
