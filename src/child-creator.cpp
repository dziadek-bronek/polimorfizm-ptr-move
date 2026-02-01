#include"include/child-creator.hpp"
#include"include/children.hpp"

#include<memory>
#include<vector>

#include<cstdio>

template <typename CHILD>
struct CChildCreator : CChildCreatorIf {
    CChildCreator(int id_): id(id_) { printf("CChildCreator %i constructor\n", id); }
    ~CChildCreator(){ printf("CChildCreator %i destructor\n", id); }

    virtual void* createNewChildIfIsNumber(int id_) {
        if(id_ == id) {
            printf("CChildCreator %i is creating new child\n", id);
            return (void*)new CHILD;
        }
        return nullptr;
    }

    private:
    int id;
};

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using VecOfUptrChCrIf = std::vector<UptrChCrIf>;
#define PUSH_BACK(CHILD, EVENT) \
        (mapPtr->push_back((UptrChCrIf)(new CChildCreator<CHILD>(EVENT))));
void CChildCreatorIf::initMapWithCreators(void* mapVoidPtr) {
    VecOfUptrChCrIf* mapPtr = (VecOfUptrChCrIf*) mapVoidPtr;
    mapPtr->push_back(UptrChCrIf(nullptr)); /* exit */
    PUSH_BACK(CChild1, 1);
    PUSH_BACK(CChild2, 2);
    PUSH_BACK(CChild3, 3);
    PUSH_BACK(CChild4, 4);
}
