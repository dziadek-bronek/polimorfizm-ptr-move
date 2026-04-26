#include "child-creator.hpp"
#include <cstdio>
#include <typeinfo>

template <typename CHILD> struct CChildCreator : CChildCreatorIf
{
    CChildCreator(int id_)
        : id(id_)
    {
        printf("CChildCreator id=%i, for %s - constructor\n", id,
               typeid(CHILD).name() + 1);
    }
    ~CChildCreator()
    {
        printf("CChildCreator id=%i, for %s - destructor\n", id,
               typeid(CHILD).name() + 1);
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CChildCreator id=%i is creating new %s\n", id,
                   typeid(CHILD).name() + 1);
            return new CHILD;
        }
        return nullptr;
    }

  private:
    int id;
};
