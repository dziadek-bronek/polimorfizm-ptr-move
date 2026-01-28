#include"include/child-creator.hpp"

static void assignChildCreatorToEvent(
        int event, std::list<std::unique_ptr<CChildCreator>>& map) {
    map.push_back(std::unique_ptr<CChildCreator>(new CChildCreator(event)));
}

void registerChildCreators(std::list<std::unique_ptr<CChildCreator>>& map) {
    assignChildCreatorToEvent(1, map);
    assignChildCreatorToEvent(2, map);
    assignChildCreatorToEvent(3, map);
}
