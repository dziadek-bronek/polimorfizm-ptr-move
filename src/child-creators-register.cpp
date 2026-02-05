#include"include/child-creators-register.hpp"
#include"include/parent.hpp"
#include"include/child-creator.hpp"

#include"include/throw.hpp"

#include<vector>
#include<memory>

struct CCreatorsRegister : CCreatorsRegisterIf {
    CCreatorsRegister() { printf("The register of child creators: constructing\n");}
    virtual ~CCreatorsRegister() {printf("The register of child creators: destructing\n");}

    virtual void init();
    virtual void* newChildBasedOnEvent(int event);
    virtual void registerr(void* creator, int event) {
        CChildCreatorIf* x = (CChildCreatorIf*) creator;
        map.at(event) = std::unique_ptr<CChildCreatorIf>(x);
    }
    virtual void* getMapVoidPtr() {
        return (void*)&map;
    }

    private:
    std::vector<std::unique_ptr<CChildCreatorIf>> map{std::vector<std::unique_ptr<CChildCreatorIf>>(0)};    
};

CCreatorsRegisterIf* CCreatorsRegisterIf::createNew() {
    return new CCreatorsRegister;
}



void* CCreatorsRegister::newChildBasedOnEvent(int event) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }
    // for list:
    // for(std::unique_ptr<CChildCreatorIf>& childCreator : map) {
    //     void* x = (void*)childCreator->createNewChildIfIsNumber(event);
        auto& x = map.at(event);
        if (nullptr != x) {
        void* y = (map.at(event))->createNewChildIfIsNumber(event);
        if(nullptr != y) {
            printf("The register of child creators: new child created based on event %i\n",
                    event);
            return y;
        }
        }
    // }

    THROW2("Exit", " on error: unknown event");
}


void CCreatorsRegister::init() {

    map.push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */

    map.push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */
    map.push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */
    map.push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */
    map.push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */
    map.push_back(std::unique_ptr<CChildCreatorIf>(nullptr)); /* exit */


//    CChildCreatorIf::initMapWithCreators((void*) &map);    
}
