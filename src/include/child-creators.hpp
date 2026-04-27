#include "child-creator.hpp"
#include <cstdio>
#include <typeinfo>

template <typename CHILD> struct CChildCreator : CChildCreatorIf
{
    CChildCreator(int id_, void* initParametersVoidPtr_)
        : id(id_),
          initParametersVoidPtr(initParametersVoidPtr_)
    {
    }
    CChildCreator(int id_)
        : id(id_),
          initParametersVoidPtr(nullptr)
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

            CHILD* x(new CHILD());
            x->init(initParametersVoidPtr);
            return x;
#if 0
	    if(nullptr == initParametersVoidPtr) {
		    return new CHILD();
	    }

            return new CHILD(initParametersVoidPtr);
#endif
        }
        return nullptr;
    }

  private:
    int id;
    void* initParametersVoidPtr;
};
