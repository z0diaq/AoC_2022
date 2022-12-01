PLEASE READ TILL END (very important info at the end)

Required setup:
- some projects rely on boost libraries so You need to setup them first
- go to boost.org and download latest zip/7z - as of current day it is 1.80.0
- extract it somewhere - I use c:\dev\libs, so full path is c:\dev\libs\boost_1_80_0
- BEFORE starting visual studio add new env variable - simplest way is to use windows' shell (menu start -> cmd) and type this: "setx MY_LIBS c:\dev\libs" (without quotes) - this will create env var that is preserved between OS restarts
- now VS will be able to expand it in each project's setings - if You different name (not MY_LIBS) then remember to update all projects or You will get failures about missing boost files

To create new project
- add empty C++ project to solution
- in Windows explorer copy source (*.ixx, *.cpp) and test data (*.txt) from template dir to newly created project's dir - don't use copy in 'solution explorer' (in vS) it will create links only and this will make problems later
- add reference to 'generalSolution' - internally this will add also project's dependency
- if required add boost dependency - $(MY_LIBS)\boost_1_80_0
- code solution :)
- profit!

prepare solution
- modify main - need only to update module name and namespace import
- fill data files with correct contents
 - sample_input_(abc).txt contains any input from examples
 - sample_input_(abc)_result_part(12).txt contains expected results from examples
 - input.txt contains input data - update this with your data ('get your puzzle input') since it is different per account (so each account have different results also), input_result_part1.txt and input_result_part2.txt are computed values (our solutions) that can be filled after solving puzzle (and verified on AoC site) and put here to verify algo correctness in case of any refactoring You'd like to do ;)