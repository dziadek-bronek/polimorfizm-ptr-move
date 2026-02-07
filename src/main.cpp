#include"include/framework.hpp"

// for new child:
#include"include/parent.hpp"
#include"include/child-creators.hpp"

#include<cstdio>
#include<vector>

// new child demonstration
struct CNewChild : CParent {
    CNewChild() {printf("child CNewChild constructor\n");}
    virtual void action() { printf("behavior specific for NEW CHILD  --------------\n"); }
    virtual ~CNewChild() {printf("child CNewChild destructor\n");}
};

int main() {
    try {

        // std::vector<int> selectorConfig({7,2, 1, 4, 3});
        std::vector<int> selectorConfig({7, 3});

        std::unique_ptr<CFrameworkIf> framework(
            std::unique_ptr<CFrameworkIf>(
                CFrameworkIf::createNew(
                    //&selectorConfig
                    nullptr
                )
            )
        );

// for new child demonstration
{
        std::unique_ptr<CChildCreatorIf> newChildCreator (
            std::unique_ptr<CChildCreatorIf>(
                new CChildCreator<CNewChild>(8)
            )
        );
        framework->selectorConfigAdd(&newChildCreator);
}

        CInput input;
        // input.init(new std::vector<int>{2,1,4,3,8,7});
        input.init(new std::vector<int>{4, 8, 7});
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
