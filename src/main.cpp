#include"include/framework.hpp"

// for new child:
#include"include/children.hpp"
#include"include/child-creators.hpp"

#include<cstdio>
#include<vector>

// new child example
struct CNewChild : CChild4 {
    virtual void action() {
       printf("behavior specific for CHILD 4 --------------\n");
    }
};

int main() {
    try {
        CInput input;
        input.init(new std::vector<int>{2,1,4,3,7});

        std::vector<int> selectorConfig({7,2, 1, 4, 3});

        std::unique_ptr<CFrameworkIf>
        framework(
                    std::unique_ptr<CFrameworkIf>(
                        CFrameworkIf::createNew(
                            &selectorConfig
                            // nullptr
                        )
                    )
                );

{
        std::unique_ptr<CChildCreatorIf> newChildCreator (
                std::unique_ptr<CChildCreatorIf>(new CChildCreator<CNewChild>(8))
            );
        framework->selectorConfigAdd(&newChildCreator);
}

        framework->mainLoop(input);

    } catch(const char* result) {
        printf("%s.\n", result); fflush(NULL);
        return 0;
    } catch(...) {
        printf("FATAL ERROR! Unhandled exception.");
        return 1;
    }

    return 0;
}
