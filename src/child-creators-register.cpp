#include"include/child-creators-register.hpp"
#include"include/parent.hpp"
#include"include/child-creator.hpp"

#include"include/throw.hpp"

#include<vector>
#include<memory>

struct CCreatorsRegister : CCreatorsRegisterIf<CParent> {
    CCreatorsRegister() { printf("The register of child creators: constructing\n");}
    virtual ~CCreatorsRegister() {printf("The register of child creators: destructing\n");}    
    virtual void init();
    virtual CParent* newChildBasedOnEvent(int event);

    private:
    std::vector<std::unique_ptr<CChildCreatorIf>> map{std::vector<std::unique_ptr<CChildCreatorIf>>(0)};    
};

template<>
CCreatorsRegisterIf<CParent>* CCreatorsRegisterIf<CParent>::createNew() {
    return new CCreatorsRegister;
}

CParent* CCreatorsRegister::newChildBasedOnEvent(int event) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }
    // for list:
    // for(std::unique_ptr<CChildCreatorIf>& childCreator : map) {
    //     PARENT* x = (PARENT*)childCreator->createNewChildIfIsNumber(event);
        CParent* x = (CParent*)((map.at(event))->createNewChildIfIsNumber(event));
        if(nullptr != x) {
            printf("The register of child creators: new child created based on event %i\n",
                    event);
            return x;
        }
    // }

    THROW2("Exit", " on error: unknown event");
}

void initMapWithCreators(void* mapVoidPtr);
void CCreatorsRegister::init() {
    initMapWithCreators((void*) &map);    
}
