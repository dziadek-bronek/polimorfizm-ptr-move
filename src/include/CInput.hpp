#ifndef CINPUT_HPP
#define CINPUT_HPP

#include <memory>
#include <vector>

struct CInput {
  int indexOfCurrentEvent{0};
  std::unique_ptr<std::vector<int>> sequenceOfEvents;
  int currentEvent{0};

  void init(void* sequenceOfEvents_);

  int getCurrentEvent();

  int nextCurrentEvent();

  void setCurrentEvent();
};

#endif
