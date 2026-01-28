
#include"include/child-creators-register.hpp"

#include"include/child-creator.hpp"
#include<list>
struct CCreatorsRegister: CCreatorsRegisterIf {
        CCreatorsRegister(){printf("The register of child: constructed\n");}
        virtual void init();
        virtual ~CCreatorsRegister(){printf("CCreatorsRegister destructor\n");}
        virtual std::unique_ptr<CParent> newChildBasedOnEvent(int event);
    private:
        std::list<std::unique_ptr<CChildCreatorIf>> map; /* mapOfEventsAndChildrenCreators; */
};

#include"include/child-creators-registering.hpp"
void CCreatorsRegister::init() {
    registerChildCreators((void*)&map);
}

std::unique_ptr<CParent> CCreatorsRegister::newChildBasedOnEvent(int event) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }

    for(std::unique_ptr<CChildCreatorIf>& childCreator : map) {
        CParent* x = childCreator->createNewChildIfIsNumber(event);
        if(nullptr != x) {
            return std::unique_ptr<CParent>(x);
        }
    }

    throw "Exit on error: unknown event";
}

std::unique_ptr<CCreatorsRegisterIf> CCreatorsRegisterIf::createNew() {
    return std::unique_ptr<CCreatorsRegisterIf>(new CCreatorsRegister());
} 