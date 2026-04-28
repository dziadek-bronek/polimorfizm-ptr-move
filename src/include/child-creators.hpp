#include "VOID.hpp"
#include "child-creator.hpp"
#include <cstdio>
#include <memory>
#include <typeinfo>

template <typename CHILD> struct CChildCreator : CChildCreatorIf
{
    CChildCreator(int id_, VOID* initParametersVoidPtr_)
        : id(id_)
    {
        printf("TTTTTTTTTTTTTTTTTTTTTTTT\n");
        fflush(NULL);
        initParametersUPtr = std::unique_ptr<VOID>(initParametersVoidPtr_);
    }
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

            CHILD* x(new CHILD());
            if (nullptr != initParametersUPtr)
            {
                x->init(initParametersUPtr.get());
                printf("\t\t\t\t\t\tTTTTTTTTTTTTTTTTTTTTTTTT\n");
                fflush(NULL);
            }
            return x;
        }
        return nullptr;
    }

  private:
    int id;
    std::unique_ptr<VOID> initParametersUPtr{nullptr};
};
