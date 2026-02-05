#include"include/child-creators.hpp"
#include"include/children.hpp"

#include<memory>
#include<vector>

#include<cstdio>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using VecOfUptrChCrIf = std::vector<UptrChCrIf>;



#define PUSH_BACK(CHILD, EVENT) \
        (mapPtr->push_back((UptrChCrIf)(new CChildCreator<CHILD>(EVENT))))
void CChildCreatorIf::initMapWithCreators(void* mapVoidPtr) {
    VecOfUptrChCrIf* mapPtr = (VecOfUptrChCrIf*) mapVoidPtr;
    PUSH_BACK(CChild1, 1);
    PUSH_BACK(CChild2, 2);
    PUSH_BACK(CChild3, 3);
    PUSH_BACK(CChild4, 4);
}
