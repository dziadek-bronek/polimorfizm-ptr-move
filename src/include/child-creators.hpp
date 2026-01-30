
#include"child-creator.hpp"

template <typename CHILD, typename PARENT>
struct CChildCreator : CChildCreatorIf<PARENT> {
    CChildCreator(int number_): number(number_) {
       this->printoutOnConstructor(number); 
    }

    ~CChildCreator(){this->printoutOnDestructor(number);}

    virtual PARENT* createNewChildIfIsNumber(int number_) {
        if(number_ == number) {
            this->printoutOnCreateNewChild(number);
            return new CHILD;
        }
        return nullptr;
    }

    private: int number;
};
