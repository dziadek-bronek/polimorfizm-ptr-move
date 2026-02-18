/*
Software module (mylib): what it can help and how to use it.
Description and the example of usage.

Mylib software module (library) is a kind of very simple tool (facility tool,
framework).

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
Technically: each of 4 actions is defined in method 'action' of class dedcated
for this action (a wrapper of this action). Classes are : CChild1, CChild2,
CChild3, CChild4.

Using headers and precompiled mylib developer can easily program the scenario
on an input number a computer performs some (one of predefined) action
associated to this input number. A pair number-action is configured as a
sequence of numbers, where position of a number in a sequence is significant
with meaning: Having position N and a number I on this position means that
action number N is to be performed on input number I. Having negative number on
position N means that action number N is disabled. Number on position 0 defines
input on which exit is performed, i.e number 7 on position 0 (first position)
means that program is terminated on input number 7.

For example configuration {7, 4} means that:
If input number is 7 then terminate program.
If input number is 4 then perform action defined in method 'action' of class
CChild4. If input number is other than 4 and other than 7, then computers
informs about unknown input and terminate.

THE EXAMPLE 1 IS NOT RECOMMENDED FOR USE IN DEVELOPMENT. INTENTION OF HAVING
SUCH USE IT WAS ONLY TO APPROACH MAIN USAGE

====
2.  Advanced usage of software module:
Defining any action (definition of action provided by sw developer on his own).
Configuring it to be invoked on any number (triger number provided by sw
developer on his own)

*/

#include "include/CFrameworkIf.hpp"
#include "include/CInput.hpp"

/* Needed for unique_ptr */
#include <memory>

/* Needed for passing parameters/configuration to objects */
#include <vector>

/* Needed for several printouts */
#include <cstdio>

/* Select definition of function main: from the file 'example1.cpp' or
 * 'example2.cpp'. */
#include "example2.cpp"
