#include"include/child-creator.hpp"
#include<cstdio>

    void CChildCreatorIf::printoutOnConstructor(int number_) {
        printf("childCreator constructor %i\n", number_);
    }
  
    void CChildCreatorIf::printoutOnCreateNewChild(int number_) {
        printf("CChildCreator is creating new child %i\n", number_);
    }

    void CChildCreatorIf::printoutOnDestructor(int number_) {
        printf("childCreator destructor %i\n", number_);
    }


