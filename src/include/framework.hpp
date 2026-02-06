#include"child-selector.hpp"
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

struct CFrameworkIf {
    static CFrameworkIf* createNew();
    virtual void mainLoop(CInput& input, void* regConfigVoidPtr) = 0;
    virtual ~CFrameworkIf(){}
};

