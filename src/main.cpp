/*
Software module (mylib): what it can help and how to use it.
Description and the example of usage.

Mylib software module (library) is a kind of very simple tool (facility tool, framework).

====
Abstract: the module (framework) is dedicated for sw developers
Provides easy concept and scheme to  define action (function),
and to configure input number (event) on which this action is performed.

====
Details: Two examples are presented.
First example just introduces the approach to the concept proposed here
(i.e. we have actions predefined in module (mylib) and we only
configure numbers, on which each action is performed)
The second example presents the 'advanced', main case of use:
how have action action defined by developer
and how to define number on which this action is performed

====
1. As a simple demonstration: the four actions are predefined as examples in
mylib module (each action is a simple demo printouts).
Technically: each of 4 actions is defined in method 'action' of class dedcated for this action
(a wrapper of this action). Classes are : CChild1, CChild2, CChild3, CChild4.

Using headers and precompiled mylib developer can easily program the scenario
on an input number a computer performs some (one of predefined) action associated
to this input number.
A pair number-action is configured as a sequence of numbers,
where position of a number in a sequence is significant with meaning:
Having position N and a number I on this position
means that action number N is to be performed on input number I.
Having negative number on position N means that action number N is disabled.
Number on position 0 defines input on which exit is performed,
i.e number 7 on position 0 (first position) means that program is terminated on input number 7. 

For example configuration {7, 4} means that:
If input number is 7 then terminate program.
If input number is 4 then perform action defined in method 'action' of class CChild4.
If input number is other than 4 and other than 7, then computers informs about unknown input
and terminate.

THE EXAMPLE 1 IS NOT RECOMMENDED FOR USE IN DEVELOPMENT. INTENTION OF HAVING SUCH USE
IT WAS ONLY TO APPROACH MAIN USAGE

====
2.  Advanced usage of software module:
Defining any action (definition of action provided by sw developer on his own).
Configuring it to be invoked on any number (triger number provided by sw developer on his own)

*/


/* The choice between examples/demos */
#define EXAMPLE 2


#include"include/framework.hpp"

#if (EXAMPLE == 2)
/* To define and add an action provided by a developer. */
#include"include/CParent.hpp"
#include"include/child-creators.hpp"
#endif

/* For several printouts */
#include<cstdio>

/* Needed for passing parameters/configuration to objects */
#include<vector>

#if (EXAMPLE == 2)
/* New action defined by a developer, to be added (registered) to framework
   (example/demonstration.)
*/
struct CDevChild : CParent {
    CDevChild() {printf("child CDevChild constructor\n");}
    virtual void action() { printf("behavior specific for CDevChild  --------------\n"); }
    virtual ~CDevChild() {printf("child CDevChild destructor\n");}
};
#endif

int main() {
    try {
        using UPtrFrameworkIf = std::unique_ptr<CFrameworkIf>;

#if (EXAMPLE == 1)
        UPtrFrameworkIf framework;
            /* Configure framework.
            /* Configuratiof of complex selector in framework: examples. */
            std::vector<int> selectorConfig({7, 2, -1, 4});
            /* to exit - input 7 ,
               to perform child1 action - input 2,
               child2 action - disabled
               to perform child3 action - press 4,
               child4 action - disabled
            */


            framework = UPtrFrameworkIf(
                            CFrameworkIf::createNew(
                                &selectorConfig /* complex selector */
                                //nullptr       /* use this option for basic selector */
                            )
                    );


        /* Mock of input - vector presents input sequence*/
        CInput input;
        input.init(new std::vector<int>{2,4,7});

#else
#if (EXAMPLE == 2)

        UPtrFrameworkIf framework;
            /* Configure framework.
            /* Configuratiof of selector in framework: example */
            std::vector<int> selectorConfig({7}); /* exit: press 7, CChild1 press 4 */
            framework = UPtrFrameworkIf(
                            CFrameworkIf::createNew(
                                &selectorConfig /* complex selector */
                                //nullptr       /* use this option for basic selector */
                            )
                    );

        /* Mock of input - vector presents input sequence*/
        CInput input;
        input.init(new std::vector<int>{4, 8, 7});

        using UPtrCreatorIf = std::unique_ptr<CChildCreatorIf>;

        /* Example action defined by developer (see CDevChild): add to framework.
           Technically: new instance of object which on demand will create
           objects of class CDevChild. This instance is added.
        */
        UPtrCreatorIf newCreator;
        newCreator = UPtrCreatorIf(new CChildCreator<CDevChild>(8));

        /* Add creator. */
        framework->selectorConfigAdd(&newCreator);

#endif
#endif







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
