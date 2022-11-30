To create new project
- add empty C++ project to solution
- in explorer copy source (*.ixx, *.cpp) and test data (*.txt) from template dir to solution dir - don't use 'solution explorer' it will create links only
- add reference to 'generalSolution' - internally this will add also project's dependency
- if required add boost dependency - $(MY_LIBS)\boost_1_80_0
- code solution :)
- profit!

prepare solution
- modify main - need only to update module name and namespace import
- fill data files with correct contents
 - sample_input_(abc).txt contains any input from examples
 - sample_input_(abc)_result_part(12).txt contains expected results from examples