#include"include/children.hpp"
#include"include/child-creator.hpp"


#include<memory>
#include<list>

#include<cstdio>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

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

static CChildCreatorIf* createNew(int childClass, int event) {
    switch(childClass) {
        case 1: return new CChildCreator<CChild1>(event);
        case 2: return new CChildCreator<CChild2>(event);
        case 3: return new CChildCreator<CChild3>(event);
        case 4: return new CChildCreator<CChild4>(event);
    }
    throw;
}

void configure(MapOfUptrChCrIf& map) {
    map.push_back(UptrChCrIf(createNew(3,2)));
}
