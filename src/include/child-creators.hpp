#include"child-creator.hpp"


#include<memory>
#include<vector>

#include<cstdio>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using VecOfUptrChCrIf = std::vector<UptrChCrIf>;

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
    static void registerr(void* mapVoidPtr, int event) {
        VecOfUptrChCrIf* mapPtr = (VecOfUptrChCrIf*) mapVoidPtr;
        // printf("registering for event %i, sizeof map: %i\n", event, mapPtr->size());
        // fflush(NULL);
        mapPtr->at(event) = UptrChCrIf(new CChildCreator<CHILD>(event));
    }


    private:
    int id;
};
