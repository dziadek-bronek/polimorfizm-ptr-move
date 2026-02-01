
#include"child-creator.hpp"

template <typename CHILD>
struct CChildCreator : CChildCreatorIf {
    CChildCreator(int number_): number(number_) {
       this->printoutOnConstructor(number); 
    }

    ~CChildCreator(){this->printoutOnDestructor(number);}

    virtual void* createNewChildIfIsNumber(int number_) {
        if(number_ == number) {
            this->printoutOnCreateNewChild(number);
            return (void*)new CHILD;
        }
        return nullptr;
    }

    private: int number;
};
