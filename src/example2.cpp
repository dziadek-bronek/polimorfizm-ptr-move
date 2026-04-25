/* To define and add an action provided by a developer. */
#include "include/CParent.hpp"
#include "include/child-creators.hpp"

#include "include/CInput.hpp"

#include "include/CDlGlobalHandle.hpp"
#include <dlfcn.h>
CDlGlobalHandle dlCSelectorConfiguratorGlobalHandle;

/* New action defined by a developer, to be added (registered) to framework
   (example/demonstration).
*/
struct CDevChild : CParent
{
    CDevChild()
    {
        constr();
    }
    virtual ~CDevChild() override
    {
        destr();
    }
    virtual void action() override
    {
        printf("behavior specific for CDevChild\n");
    }
    virtual void constr() override
    {
        printf("child CDevChild constructor\n");
    }
    virtual void destr() override
    {
        printf("child CDevChild destructor\n");
    }
};

#define DELETE_IF_FAILURE(_x_) (delete ((CChildCreatorIf*)(_x_)))
int main()
{
    try
    {
        /* Configuration for framework.
                exit: input 7,
                actions of CChild1, CChild2, CChild3 - disabled
                to perform action of CChild4 input 4
        */
        std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});

        /* Set framework with configuration. */
        std::unique_ptr<CFrameworkIf> framework(
            createNewCFramework(&selectorInitConfig));

        /* Example action is defined by developer in class CDevChild
           Here we add it to framework. Technically: a 'creator' is
           instantiated, dedicated for CDevChild class, parametrized by this
           class. It is initialized with with number 8. And then we add this
           creator to framework (next line). The result is: on input 8 the
           object of class CDevChild is created.
        */

        /* Add creator to framework */
        DELETE_IF_FAILURE(
            framework->configAdd(new CChildCreator<CDevChild>(8)));

        DELETE_IF_FAILURE(framework->configAdd(
            "./libCDemoSoChild.so", "createNewCDemoSoChildExternC",
            "deleteCDemoSoChildExternC", 13));

        /* Mock of input - vector represents input sequence */
        std::unique_ptr<CInputIf> input(CInputIf::createNew());
        input->init(new std::vector<int>{2, 4, 3, 8, 0, 12, 13, 14, 7});

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
