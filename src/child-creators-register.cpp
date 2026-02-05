#include"include/child-creators-register.hpp"
#include"include/parent.hpp"
#include"include/child-creator.hpp"

#include"include/throw.hpp"

#include<list>
#include<memory>

void configure(std::list<std::unique_ptr<CChildCreatorIf>>& mapVoidPtr);

struct CCreatorsRegister : CCreatorsRegisterIf {
    CCreatorsRegister() { printf("The register of child creators: constructing\n");}
    virtual ~CCreatorsRegister() {printf("The register of child creators: destructing\n");}

    virtual void* newChildBasedOnEvent(int event);

    void configure() {
        ::configure(map);
    }

    private:
    std::list<std::unique_ptr<CChildCreatorIf>> map;    
};

CCreatorsRegisterIf* CCreatorsRegisterIf::createNew() {
    CCreatorsRegister* x = new CCreatorsRegister;
    x->configure();
    return x;
}

void* CCreatorsRegister::newChildBasedOnEvent(int event) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }
    for(std::unique_ptr<CChildCreatorIf>& childCreator : map) {
        if(nullptr == childCreator) continue;
        void* tryToGetChild = (void*)childCreator->createNewChildIfIsNumber(event);
        if(nullptr != tryToGetChild) {
            printf("The register of child creators: new child created based on event %i\n",
                    event);
            return tryToGetChild;
        }
    }

    THROW2("Exit", " on error: unknown event");
}
