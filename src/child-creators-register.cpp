#include"include/child-creators-register.hpp"
#include"include/parent.hpp"
#include"include/child-creator.hpp"

#include"include/throw.hpp"

#include<memory>
#include<list>
#include<vector>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;


void configure(MapOfUptrChCrIf& map, std::vector<int>& regConfig);
void* simple(int event);

struct CCreatorsRegister : CCreatorsRegisterIf {
    CCreatorsRegister(void* regConfigVoidPtr):
        regConfig(*((std::vector<int>*)regConfigVoidPtr))
    {
        printf("The register of child creators: constructing\n");
        configure(map, regConfig);
    }
    virtual ~CCreatorsRegister() {printf("The register of child creators: destructing\n");}

    virtual void* newChildBasedOnEvent(int event);

    private:
    std::list<std::unique_ptr<CChildCreatorIf>> map;    
    std::vector<int>& regConfig;
};

CCreatorsRegisterIf* CCreatorsRegisterIf::createNew(void* regConfigVoidPtr ) {
    if(nullptr == regConfigVoidPtr) {
        struct CSimpleChildSelector : CCreatorsRegisterIf {
            CSimpleChildSelector() {printf("The simple child selector: constructing\n"); }
            virtual ~CSimpleChildSelector() {printf("The simple child selector: destructing\n");}
            virtual void* newChildBasedOnEvent(int event) {
                return (void*)simple(event);
            }

        };
        return new  CSimpleChildSelector;
    }
    return new CCreatorsRegister(regConfigVoidPtr);
}

void* CCreatorsRegister::newChildBasedOnEvent(int event) {
    for(std::unique_ptr<CChildCreatorIf>& childCreator : map) {
        if(nullptr == childCreator) {
            THROW2("Clean exit", " (event 'EXIT' in sequenceOfEvents)");
        }
        void* tryToGetChild = (void*)childCreator->createNewChildIfIsNumber(event);
        if(nullptr != tryToGetChild) {
            printf("The register of child creators: new child created based on event %i\n",
                    event);
            return tryToGetChild;
        }
    }

    THROW2("Exit", " on error: unknown event");
}
