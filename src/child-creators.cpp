#include"include/child-creators.hpp"
#include"include/children.hpp"

#include<memory>
#include<vector>

#include<cstdio>

template<typename CHILD>
void CChildCreator<CHILD>::printoutOnConstructor(int number_) {
        printf("CChildCreator %i constructor\n", number_);
    }
template<typename CHILD>
void CChildCreator<CHILD>::printoutOnCreateNewChild(int number_) {
        printf("CChildCreator %i is creating new child\n", number_);
    }
template<typename CHILD>
void CChildCreator<CHILD>::printoutOnDestructor(int number_) {
        printf("CChildCreator %i destructor\n", number_);
    }

template<typename CHILD>
static void pushBackChildCreator(std::vector<std::unique_ptr<CChildCreatorIf>>* mapPtr,
        int number)
{
    mapPtr->push_back(std::unique_ptr<CChildCreatorIf>(new CChildCreator<CHILD>(number)));
}

void initMapWithCreators(void* mapVoidPtr) {
    std::vector<std::unique_ptr<CChildCreatorIf>>* mapPtr
        = (std::vector<std::unique_ptr<CChildCreatorIf>>*) mapVoidPtr;
    mapPtr->push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */
    pushBackChildCreator<CChild1>(mapPtr, 1);
    pushBackChildCreator<CChild2>(mapPtr, 2);
    pushBackChildCreator<CChild3>(mapPtr, 3);
    pushBackChildCreator<CChild4>(mapPtr, 4);    
}