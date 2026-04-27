
using CreateNewPlugin = CParent* (*)();
using DeletePlugin = void (*)(CParent*);

void* createNewCSoChildCreator(int, void*, void*, CreateNewPlugin,
                               DeletePlugin);
