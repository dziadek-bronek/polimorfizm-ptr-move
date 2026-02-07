#include"include/child-selector.hpp"

#include"include/selector-config.hpp"
#include"include/child-creator.hpp"

#include"include/throw.hpp"

#include<memory>
#include<list>
#include<vector>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

struct CChildSelector : CChildSelectorIf {
    CChildSelector(void* selectorConfigVoidPtr)
    {
        printf("The selector of child creators: constructing\n");
        configureSelection(&map, selectorConfigVoidPtr);
    }
    virtual ~CChildSelector() {printf("The selector of child creators: destructing\n");}

    virtual void* getConfig() {return &map;}

    virtual void* newChildBasedOnEvent(int event) {
        for(std::unique_ptr<CChildCreatorIf>& childCreator : map) {
            if(nullptr == childCreator) {
                THROW2("Clean exit", " (event 'EXIT' in sequenceOfEvents)");
            }
            void* tryToGetChild = childCreator->createNewChildIfIsNumber(event);
            if(nullptr != tryToGetChild) {
                printf("The selector of child creators: new child created based on event %i\n",
                        event);
                return tryToGetChild;
            }
        }

        THROW2("Exit", " on error: unknown event");
    }
    
    private:
    MapOfUptrChCrIf map;    
};


        struct CSimpleChildSelector : CChildSelectorIf {
            CSimpleChildSelector() {
                printf("The simple child selector: constructing\n"); fflush(NULL);
                single = UptrChCrIf((CChildCreatorIf*)configureSimpleSelection());
            }
            virtual ~CSimpleChildSelector() {printf("The simple child selector: destructing\n");}
            virtual void* getConfig() {return nullptr;}
            virtual void* newChildBasedOnEvent(int event) {
                return single->createNewChildIfIsNumber(event);
            }
            private:
            UptrChCrIf single;
        };



CChildSelectorIf* CChildSelectorIf::createNew(void* selectorConfigVoidPtr ) {
    if(nullptr == selectorConfigVoidPtr) {
        return new CSimpleChildSelector;
    }
    
    return new CChildSelector(selectorConfigVoidPtr);
}
