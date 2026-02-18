#include "include/CInput.hpp"
#include <cstdio>
#include "include/throw.hpp"

void CInput::init(void* sequenceOfEvents_) {
  sequenceOfEvents =
      std::unique_ptr<std::vector<int>>((std::vector<int>*)sequenceOfEvents_);
  setCurrentEvent();
}

int CInput::getCurrentEvent() {
  return currentEvent;
}

int CInput::nextCurrentEvent() {
  ++indexOfCurrentEvent;
  setCurrentEvent();
  return currentEvent;
}

void CInput::setCurrentEvent() {
  if (indexOfCurrentEvent < 0) {
    THROW2("Exit", " on error: invalid index of event");
  }

  if (sequenceOfEvents->size() <= indexOfCurrentEvent) {
    THROW2("Clean exit", " (no more events)");
  }

  currentEvent = (*sequenceOfEvents)[indexOfCurrentEvent];
}
