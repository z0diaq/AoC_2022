To create new project
- add empty C++ project to solution
- in explorer copy source (*.ixx, *.cpp) and test data (*.txt) from template dir to solution dir - don't use 'solution explorer' it will create links only
- add reference to 'generalSolution' - internally this will add also project's dependency
- if required add boost dependency - $(MY_LIBS)\boost_1_80_0
- code solution :)
- profit!

prepare solution
- modify main - add known test value for part 1
- prepare solution for part 1
- repeat above for part 2
- profit!