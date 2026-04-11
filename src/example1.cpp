#include "include/CParent.hpp"
#include "include/CSelectorConfigurator.hpp"

#include "include/CInputIf.hpp"

int main()
{
    try
    {
        /* Configuration for framework: example.
                to exit - input 7 ,
                to perform child1 action - input 2,
                performing child2 action - disabled
                to perform child3 action - input 4,
                performing child4 action - disabled
        */

#if 0
    std::vector<int> selectorInitConfig({7, 2, -1, 4});

    /* Set framework with configuration. */
    std::unique_ptr<CFrameworkIf> framework(
        CFrameworkIf::createNew(&selectorInitConfig));

#else

        /* Use option below to use simple selector (simple hardcoded switch)
           instead the complex one
        */
        std::unique_ptr<CFrameworkIf> framework(
            CFrameworkIf::createNew(nullptr));

#endif

        /* Mock input - vector represents input sequence */
        std::unique_ptr<CInputIf> input(CInputIf::createNew());
        input->init(new std::vector<int>{2, 4, 3, 8, 0, 7});

        framework->mainLoop(&input);
    }
    catch (const char* result)
    {
        printf("%s.\n", result);
        fflush(NULL);
        return 0;
    }
    catch (...)
    {
        printf("FATAL ERROR! Unhandled exception.");
        return 1;
    }

    return 0;
}
