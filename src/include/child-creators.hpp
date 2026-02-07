#include"child-creator.hpp"

template <typename CHILD>
struct CChildCreator : CChildCreatorIf {
    CChildCreator(int id_): id(id_)
    {
        printf("ChildCreator constructor for  %s event %i \n",
                typeid(CHILD).name() + 1, id);
    }
    ~CChildCreator(){
        printf("ChildCreator destructor for  %s event %i \n",
                typeid(CHILD).name() + 1, id);
    }

    virtual void* createNewChildIfIsNumber(int id_) {
        if(id_ == id) {
            printf("CChildCreator on event %i is creating new %s\n",
                id, typeid(CHILD).name() + 1);
            return new CHILD;
        }
        return nullptr;
    }

    private:
    int id;
};