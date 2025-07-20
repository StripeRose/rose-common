# Rose Common

## About the project

For a decent few years now, I've kept building on code I wrote back in school. Containers and file management I never really needed. While it has worked decently, it turned more and more into a copy of C#'s basic classes since I liked the way those were setup.

But for the sake of my own learning and to simplify the code I write, I'd like to start over on this collection of code with a more C++-oriented mindset, trying to use the standard library as much as possible instead of reinventing the wheel constantly.

## Project goals

* Further my understanding in when and how the C++ standard library should and can be used.
* Rebuild the set of useful classes and code not otherwise available in STL, to hopefully serve as a good base for the future.
* Let the repository be easy to include for use in other projects.
* Target the latest C++ standard, to be able to use some additional features added there.
* Provide appropriate tests for all features.

## Running tests

**Prerequisites**

- Visual Studio 2022 with CMake. Earlier versions are untested but may function.

The repository uses the following sub-modules to simplify running tests:

- [Catch2](https://github.com/catchorg/Catch2) as a test framework
- [Sharpmake](https://github.com/ubisoft/Sharpmake) to generate solutions

To download and prepare them for usage, execute `./Init-Repository.ps1`.

Once done, execute `./Run-Tests.ps1` to re-generate the solution, build and run the tests.