#include"include/selector-config.hpp"
#include"include/children.hpp"
#include"include/child-creator.hpp"
#include"include/throw.hpp"


#include<memory>
#include<list>
#include<vector>

#include<cstdio>
#include"include/child-creators.hpp"

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

struct CChildCreatorExit : CChildCreatorIf {
    CChildCreatorExit(int id_): id(id_)
    {
        printf("ChildCreator constructor for  EXIT event %i \n", id);
    }
    virtual ~CChildCreatorExit(){
        printf("ChildCreator destructor for  EXIT event %i \n", id);
    }

    virtual void* createNewChildIfIsNumber(int id_) {
        if(id_ == id) {
            printf("CChildCreator on event %i : exit\n", id);
            THROW2("Clean exit", " (event 'EXIT' on input)");
        }
        return nullptr;
    }

    private:
    int id;
};

static CChildCreatorIf* createNew(int childClass, int event) {
    switch(childClass) {
        case 1: return new CChildCreator<CChild1>(event);
        case 2: return new CChildCreator<CChild2>(event);
        case 3: return new CChildCreator<CChild3>(event);
        case 4: return new CChildCreator<CChild4>(event);
    }
    throw;
}

void configureSelection(void* mapVoidPtr, void* selectorConfigVoidPtr) {
    MapOfUptrChCrIf* mapPtr = (MapOfUptrChCrIf*)mapVoidPtr;
    std::vector<int>* selectorConfigPtr = (std::vector<int>*)selectorConfigVoidPtr;

    mapPtr->push_back(UptrChCrIf(new CChildCreatorExit(selectorConfigPtr->at(0))));

    int size = selectorConfigPtr->size();
    for(int i = 1; i < size; ++i) {
        int event = selectorConfigPtr->at(i);
        if(event < 0) {
            continue;
        }
        mapPtr->push_back(UptrChCrIf(createNew(i,event)));
    }
}








void configAdd(void* mapVoidPtr, void* newChildCreatorVoidPtr){
    MapOfUptrChCrIf* mapPtr = (MapOfUptrChCrIf*)mapVoidPtr;

    UptrChCrIf* x = (UptrChCrIf*)newChildCreatorVoidPtr;
    mapPtr->push_back(std::move(*x));
}


struct CChildCreatorSimple : CChildCreatorIf {

    virtual ~CChildCreatorSimple(){
        printf("ChildCreatorSimpleSelection destructor\n");
    }

    virtual void* createNewChildIfIsNumber(int id_) {
        switch(id_) {
        case 0: THROW2("Clean exit", " (event 'EXIT' on input)");
        case 1: return new CChild1;
        case 2: return new CChild2;
        case 3: return new CChild3;
        case 4: return new CChild4;
        }
        return nullptr;
    }
};

void* configureSimpleSelection(){
    return new CChildCreatorSimple;
}

