/* To define and add an action provided by a developer. */
#include "include/CParent.hpp"
#include "include/child-creators.hpp"

/* New action defined by a developer, to be added (registered) to framework
   (example/demonstration).
*/
struct CDevChild : CParent {
  CDevChild() { printf("child CDevChild constructor\n"); }
  virtual ~CDevChild() override { printf("child CDevChild destructor\n"); }
  virtual void action() override { printf("behavior specific for CDevChild  --------------\n"); }
  virtual void constr() override { printf("child CDevChild constructor\n"); }
  virtual void destr() override { printf("child CDevChild destructor\n"); }
};

int main() {
  try {
    /* Configuration for framework.
            exit: input 7,
            actions of CChild1, CChild2, CChild3 - disabled
            to perform action of CChild4 input 4
    */
    std::vector<int> selectorConfig({7, -1, -1, -1, 4});

    using UPtrFrameworkIf = std::unique_ptr<CFrameworkIf>;
    UPtrFrameworkIf framework(
        UPtrFrameworkIf(CFrameworkIf::createNew(&selectorConfig)));

    /* Example action defined by developer (see CDevChild definition) -
       adding to framework. Technically: a 'creator' is instantiated,
       dedicated for CDevChild class. It is initialized with int 8. After
       adding this creator to framework (next line) it will creates objects
       of class CDevChild, every time when input is 8.
    */
    using UPtrCreatorIf = std::unique_ptr<CChildCreatorIf>;
    UPtrCreatorIf newCreator;
    newCreator = UPtrCreatorIf(new CChildCreator<CDevChild>(8));

    /* Add creator to framework */
    framework->selectorConfigAdd(&newCreator);

    /* Mock of input - vector represents input sequence */
    CInput input;
    input.init(new std::vector<int>{2, 4, 3, 8, 0, 7});

    framework->mainLoop(&input);

  } catch (const char* result) {
    printf("%s.\n", result);
    fflush(NULL);
    return 0;
  } catch (...) {
    printf("FATAL ERROR! Unhandled exception.");
    return 1;
  }

  return 0;
}
