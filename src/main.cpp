#include<cstdio>
#include<vector>
#include"include/framework.hpp"

int main() {
    try {

        CFramework framework;

        CInput input;
        input.init(new std::vector<int>{2,1,4,3,0});

        framework.mainLoop(input);


    } catch(const char* result) {
        printf("%s.\n", result);
        return 0;
    } catch(...) {
        printf("FATAL ERROR! Unhandled exception.");
        return 1;
    }

    return 0;
}
