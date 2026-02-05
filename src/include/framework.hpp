#include"child-creators-register.hpp"
#include<memory>
#include<vector>

struct CInput {
    int indexOfCurrentEvent{0};
    std::unique_ptr<std::vector<int>> sequenceOfEvents;
    int currentEvent{0};

    void init(std::vector<int>* sequenceOfEvents_);

    int getCurrentEvent();

    int nextCurrentEvent();

    void setCurrentEvent();
};


struct CFramework {
    CFramework();
    void mainLoop(CInput& input);
    std::unique_ptr<CCreatorsRegisterIf> creatorsRegister; 
};