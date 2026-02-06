#include<cstdio>
#include<vector>
#include"include/framework.hpp"

int main() {
    try {
        CInput input;
        input.init(new std::vector<int>{2,1,4,3,7});

        std::vector<int> selectorConfig({7,2, 1, 4, 3});

        std::unique_ptr<CFrameworkIf>
        framework(std::unique_ptr<CFrameworkIf>(CFrameworkIf::createNew()));
        framework->mainLoop(input, &selectorConfig);
        // framework->mainLoop(input, nullptr);

    } catch(const char* result) {
        printf("%s.\n", result); fflush(NULL);
        return 0;
    } catch(...) {
        printf("FATAL ERROR! Unhandled exception.");
        return 1;
    }

    return 0;
}
