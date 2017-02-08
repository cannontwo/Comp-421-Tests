# Comp-421-Tests

Repository containing test cases for use in Rice University COMP 421: Operating Systems and Concurrent Programming. Let's break some code!

## Contributing

If you would like to contribute to this repository, please place your test cases in a folder named after your netid under the appropriate lab folder (i.e. **/lab1/wcl2**) and create a pull request.

## Honor Code

As stated on Piazza, it is within the Honor Code to share tests, but **no other code** for COMP 421 labs. Please do not attempt to share code that constitutes a violation of the Honor Code.

## Note for Compilation with wcl2 Tests

If you are using the wcl2 tests for lab1, they have a dependency on **utils.c** and **utils.h** in the same directory. To get these files to compile and link properly with the tests, add `utils.h` after `$(MONTTY)` in the provided Makefile on the line beginning with `ALL` and the line beginning `$(TEST)`. Everything should then compile correctly with make.
