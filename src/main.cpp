#include<cstdio>
#include<vector>
#include"include/framework.hpp"

int main() {
    try {

        CFramework framework;

        CInput input;
        input.init(new std::vector<int>{2,1,4,1,7});

        std::vector<int> regConfig({7,1, 2, 3, 4});

        // framework.mainLoop(input, (void*)&regConfig);
        framework.mainLoop(input, nullptr);


    } catch(const char* result) {
        printf("%s.\n", result);
        return 0;
    } catch(...) {
        printf("FATAL ERROR! Unhandled exception.");
        return 1;
    }

    return 0;
}
