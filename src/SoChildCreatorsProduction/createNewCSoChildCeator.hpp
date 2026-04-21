#include "../include/CParent.hpp"

using CreateNewSoChild = CParent* (*)();
using DeleteSoChild = void (*)(CParent*);

void* createNewCSoChildCreator(int, void*, void*, CreateNewSoChild,
                               DeleteSoChild);
