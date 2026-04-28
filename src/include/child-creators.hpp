#include "VOID.hpp"
#include "child-creator.hpp"
#include <cstdio>
#include <memory>
#include <typeinfo>

template <typename CHILD> struct CChildCreator : CChildCreatorIf
{
    CChildCreator(int id_, std::unique_ptr<VOID> initParametersVoidUPtr_)
        : id(id_)
    {
        printf("TTTTTTTTTTTTTTTTTTTTTTTT\n");
        fflush(NULL);
        initParametersVoidUPtr =
            std::unique_ptr<VOID>(std::move(initParametersVoidUPtr_));
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
            if (nullptr != initParametersVoidUPtr)
            {
                x->init(initParametersVoidUPtr.get());
                printf("\t\t\t\t\t\tTTTTTTTTTTTTTTTTTTTTTTTT\n");
                fflush(NULL);
            }
            return x;
        }
        return nullptr;
    }

  private:
    int id;
    std::unique_ptr<VOID> initParametersVoidUPtr{nullptr};
};
