#include<list>

#include"include/children.hpp"
#include"include/child-creator.hpp"

template <typename CHILD>
struct CChildCreator : CChildCreatorIf {
    CChildCreator(int number_): number(number_) {
       printoutOnConstructor(number); 
    }
    ~CChildCreator(){printoutOnDestructor(number);}

    virtual CParent* createNewChildIfIsNumber(int number_) {
        if(number_ == number) {
            printoutOnCreateNewChild(number);
            return new CHILD;
        }
        return nullptr;
    }

    private: int number;
};

#include<list>
#include<memory>
template <typename CHILD>
void assignChildCreatorToEvent(int number, std::list<std::unique_ptr<CChildCreatorIf>>* map) {
    map->push_back(std::unique_ptr<CChildCreatorIf>(new CChildCreator<CHILD>(number)));
}

void registerChildCreators(void* mapVoidPtr) {
    auto map = static_cast<std::list<std::unique_ptr<CChildCreatorIf>>*>(mapVoidPtr);
    assignChildCreatorToEvent<CChild1>(1, map);
    assignChildCreatorToEvent<CChild2>(2, map);
    assignChildCreatorToEvent<CChild3>(3, map);
}
