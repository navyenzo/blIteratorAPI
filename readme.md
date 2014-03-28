# blIteratorAPI

## What is this?

This *header-only-library* provides a set of classes/functors that
allows a programmer to easily create custom iterators.

## How do I install and use it?

The library is a set of header files collected in one folder.

1.  Copy the folder to your preferred workspace (for ex.
    c:/blIteratorAPI).

1.  Include the blIteratorAPI.hpp file in your code.

2.  Access the functionality through the blIteratorAPI:: namespace like
    in the following example:

<!-- -->

    #include <iterator>
    #include <memory>
    #include <iostream>


    // Include the blIteratorAPI
    // library file

    #include "blIteratorAPI.hpp"


    int main()
    {
        // Create a raw array

        int myArray[] = {2,23,5,56,2354,-23,23,-432,231};

        // The library provides a
        // raw array wrapper

        auto myArrayWrapper = blIteratorAPI::getRawArrayWrapper(mammaArray);

        // The library provides
        // a flexible iterator
        // library to create custom
        // iterators.

        // Here we create an
        // iterator to linearly
        // move through the
        // array.
        // This iterator never
        // goes past the array's
        // end even if the user
        // tries to.

        blLinearIterator<decltype(myArrayWrapper)> myIter(mammaArrayWrapper);

        for(auto iter = Gioa.begin();
            iter != Gioa.end();
            ++iter)
        {
            std::cout << "iter pos = " << 
    iter.getDistanceFromBeginToIter();
            std::cout << ", dist from end = " << iter.getDistanceFromIterToEnd();

            std::cout << ", value = " << *iter << "\n";
        }

        std::cout << "\n\n\n";

        // Get input from user
        // before quitting

        int inputFromUser;
        std::cin >> inputFromUser;

        return 0;
    }

## How is the library structured?

The aim of this library is to allow users to create interesting custom
iterators for their own needs. In order to do that, it introduces some
basic tools, and they are broken down in the following header files:

-   **blSmartPointerFunctions.hpp** -- A collection of simple functions
    to ease the creation of std::shared\_ptr pointers of resources.

-   blRawIterators.hpp -- Defines a random access *iterator* and
    *reverse\_iterator* that can be used in custom classes.

-   **blArray.hpp** -- A static templated array with helper functions
    such as "begin", "end" and "size" that make it easy to use with stl
    algorithms.

-   **blRawArrayWrapper.hpp** -- A class that wraps existing raw static
    or dynamic arrays with functions such as "begin", "end" and "size"
    to make it easy to use with stl algorithms. This only wraps raw
    arrays, but does not delete them on destruction.

## What is the license?

[The MIT License (MIT)][]

  [The MIT License (MIT)]: http://www.opensource.org/licenses/mit-license.php
