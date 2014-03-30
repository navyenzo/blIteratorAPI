**blIteratorAPI**
=================

*- A template library for creating custom iterators*
----------------------------------------------------



**What is this?**
-----------------

This *header-only-library* provides a set of classes that allow a programmer to
easily create custom iterators.



**How do I install it?**
------------------------

Just copy the blIteratorAPI folder with its content to your 'include' directory,
and include it into your code:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "blIteratorAPI/blIteratorAPI.hpp"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



**Dependencies**
----------------

-   c++11

-   \<memory\>

-   \<iterator\>



**Example usage**
-----------------

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iterator>
#include <memory>
#include <iostream>

// Include the blIteratorAPI

#include "blIteratorAPI.hpp"

int main()
{
    // Create a raw array
    
    int myArray[] = {2,23,5,56,2354,-23,23,-432,231};

    // The library provides a class
    // to wrap a raw array

    auto myArrayWrapper = blIteratorAPI::getRawArrayWrapper(myArray);

    // The library provides a
    // flexible iterator class
    // to create custom iterators

    // Here we create an iterator
    // to linearly move through
    // the array.
    // This iterator never goes
    // past the array's end even
    // if the user tries to.

    blLinearIterator<decltype(myArrayWrapper)> myIter(myArrayWrapper);

    for(auto iter = myIter.begin();
        iter != myIter.end();
        ++iter)
    {
        std::cout << "iter pos = " << iter.getDistanceFromBeginToIter();
        std::cout << ", dist from end = " << iter.getDistanceFromIterToEnd();
        std::cout << ", value = " << *iter << "\n";
    }

    std::cout << "\n\n";

    // Get input from user
    // before quitting

    int inputFromUser;
    std::cin >> inputFromUser;

    return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



**What does this library actually provide?**
--------------------------------------------

The aim of the blIteratorAPI library is to allow a user to easily create custom
iterators for their own needs.

In order to do that, it introduces tools broken down in the following header
files:



-   **blSmartPointerFunctions.hpp** -- A collection of simple template functions
    to get std::shared_ptr pointers of resources.

    -   For example:

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Some object of whatever type
    myType object;

    // Get a shared_ptr to object
    auto objectPtr = get_shared_ptr(object);
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



-   **blRawIterators.hpp** -- Defines a random access *iterator* and
    *reverse_iterator* that can be used in custom classes to allow their use in
    stl algorithms.

    -   For example in a custom container class, define the following
        *typedefs*:

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    template<typename blDataType>
    class customArray
    {
    public:

        // Define the iterator typedefs
        typdef blRawIterator<blDataType> iterator;
        typdef blRawReverseIterator<blDataType> reverse_iterator;
        .
        .
        .
        iterator begin(){return iterator(&m_container[0]);}
        iterator end(){return iterator(&m_container[size()];}
        reverse_iterator rbegin(){return reverse_iterator(&m_container[size()-1];}
        reverse_iterator rend(){return reverse_iterator(&m_container[-1];}
        .
        .
        .
        blDataType m_container;
    };
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



-   **blArray.hpp** -- A static templated array with helper functions such as
    "begin", "end" and "size" that make it easy to use with stl algorithms.

[^]: Similar to std::array, but can be used where there is no stl like for
Arduino.

[^]: blArray is null terminatedand like std::string, its nul terminated data can
be accessed with functions "c_std()" and "data()"

[^]: blArray size is known at compile time, it can be declared and used like in
the following examples:

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Ex. 1
    blIteratorAPI::blArray<int,3> myArray1;

    // Ex. 2 (From a null terminated string)
    auto myArray2 = blIteratorAPI::getArrayFromNullTerminated("hello world");

    // Ex. 3 (From begin/end iterators)
    std::vector<float> myVector(13,4);
    auto myArray3 = blIteratorAPI::blArray<float,13>(myVector.begin(),myVector.end());

    // Ex. 4 (From a static array)
    int a[] = {4,23,24,43,1};
    auto myArray4 = blIteratorAPI::blArray(a);

    // Ex. 5 (From an initializer list)
    blIteratorAPI::blArray<int,6> myArray5 = {1,2,3,4,5,6};
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



-   **blRawArrayWrapper.hpp** -- A class that wraps existing raw static or
    dynamic arrays with iterator functionality to make it easy to use with stl
    algorithms. This only wraps raw arrays, but does not delete them on
    destruction.

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Create a static
    // array and wrap it

    int myArray[] = {2,3,4,5,2,12,3,43,234,121,90};
    auto myArrayWrapper = getRawArrayWrapper(myArray);

    // Iterate over it

    for(auto iter = myArrayWrapper.begin();
        iter != myArrayWrapper.end();
        ++iter)
    {
        std::cout << "iter = " << *iter << "\n";
    }

    // Create a dynamic
    // array and wrap it
    // NOTE: With a dynamic
    //       array, we have to
    //       specify the size

    char* myWord = "hello world";
    auto myWordWrapper = getRawArrayWrapper(myWord,12);

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



-   **blIteratorFunctors.hpp** -- Functors defined in this header file are used
    by the custom iterator class to make it behave as desired.

    -   There are two types of functors defined in this file:

    1.  **blBeginEndFunctor** -- Used to know how to call the container's
        begin() and end() functions. A user can define his/her own
        blBeginEndFunctorType to customize the behaviour.

    2.  **blAdvanceDistanceFunctor** -- Used to know how to advance the iterator
        and how to calculate the distance between two custom iterators.  A user
        can define his/her own blAdvanceDistanceFunctor to customize the
        behaviour.

    [^]: The "begin" and "end" functions inside a blBeginEndFunctor are defined
    as static functions.

    [^]: The "advance" and "distance" functions inside a
    blAdvanceDistanceFunctor are defined as static functions.



-   **blIterator.hpp** -- Finally, the custom iterator class.  This class can be
    used to create iterators with custom behaviour.

    -   The library already provides some common use iterators, for example:

        -   **blLinearIterator**, **blLinearConstIterator**,
            **blLinearReverseIterator**, **blLinearConstReverseIterator** --
            These iterators advance linearly, but never go past their "end" or
            never past their "begin" when moving backwards.

        -   **blCircularIterator**, **blCircularConstIterator**,
            **blCircularReverseIterator**, **blCircularConstReverseIterator** --
            These iterators advance through the container in a circular fashion,
            never reaching their "end".

        [^]: NOTE:  Be careful with circular iterators, because they never reach
        their "end"

        -   The following are the steps necessary to define your own custom
            iterator:

        1.  Create a blBeginEndFunctor that defines two static functions:

            -   begin(T& container) -- Calls iterator to first element of
                container

            -   end(T& container) -- Call iterator to one place after last
                element of container

        2.  Create a blAdvanceDistanceFunctor that defines two static functions:

            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            template            <typename blIteratorType>
            static void advance(blIteratorType& iter,
                                const ptrdiff_t& howManyStepsToAdvanceIter,
                                const blIteratorType& beginIter,
                                const blIteratorType& endIter,
                                const ptrdiff_t& distanceFromBeginToIter,
                                const ptrdiff_t& distanceFromIterToEnd)
            {
            }

            template            <typename blIteratorType>
            static ptrdiff_t distance(const blIteratorType& iter1,
                                      const blIteratorType& iter2,
                                      const ptrdiff_t& distanceFromBeginToIter1,
                                      const ptrdiff_t& distanceFromBeginToIter2,
                                      const ptrdiff_t& distanceFromIterToEnd1,
                                      const ptrdiff_t& distanceFromIterToEnd2)
            {
                return whateverDistance;
            }
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



**What is the license?**
------------------------

[The MIT License (MIT)][]

[The MIT License (MIT)]: http://www.opensource.org/licenses/mit-license.php



To do:
======

Add more examples showing how to create and use custom iterators
