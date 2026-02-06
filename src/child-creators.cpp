#include"include/children.hpp"
#include"include/child-creator.hpp"
#include"include/throw.hpp"


#include<memory>
#include<list>
#include<vector>

#include<cstdio>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

template <typename CHILD>
struct CChildCreator : CChildCreatorIf {
    CChildCreator(int id_): id(id_)
    {
        printf("ChildCreator constructor for  %s event %i \n",
                typeid(CHILD).name(), id);
    }
    ~CChildCreator(){
        printf("ChildCreator destructor for  %s event %i \n",
                typeid(CHILD).name(), id);
    }

    virtual void* createNewChildIfIsNumber(int id_) {
        if(id_ == id) {
            printf("CChildCreator on event %i is creating new %s\n",
                id, typeid(CHILD).name());
            return (void*)new CHILD;
        }
        return nullptr;
    }

    private:
    int id;
};

struct CChildCreatorExit : CChildCreatorIf {
    CChildCreatorExit(int id_): id(id_)
    {
        printf("ChildCreator constructor for  EXIT event %i \n", id);
    }
    ~CChildCreatorExit(){
        printf("ChildCreator destructor for  EXIT event %i \n", id);
    }

    virtual void* createNewChildIfIsNumber(int id_) {
        if(id_ == id) {
            printf("CChildCreator on event %i : exit\n", id);
            THROW2("Clean exit", " (event 'EXIT' in sequenceOfEvents)");
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

void configure(MapOfUptrChCrIf& map, std::vector<int>& regConfig) {
    map.push_back(UptrChCrIf(new CChildCreatorExit(regConfig[0])));

    int size = regConfig.size();
    for(int i = 1; i < size; ++i) {
        map.push_back(UptrChCrIf(createNew(i,regConfig[i])));
    }
}

void* simple(int event) {
    switch(event) {
        case 0: throw "exit event simple";
        case 1: return new CChild1;
        case 2: return new CChild2;
        case 3: return new CChild3;
        case 4: return new CChild4;
        }
        throw "unknownd event simple";
}
