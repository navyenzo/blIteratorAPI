#ifndef BL_IteratorAPI_HPP
#define BL_IteratorAPI_HPP


//-------------------------------------------------------------------
// FILE:            blIteratorAPI.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         This API plays with the concept of iterators
//                  to give "smart" functionality to generic data
//                  buffers.
//
//                  The API introduces two types of iterators:
//
//                  - Raw iterators -- They wrap raw pointers and can be
//                                     used to add the concept of iterators
//                                     to contiguous buffer storage classes.
//
//                  - Smart iterators -- They add "smart" functionality to
//                                       buffers which already define raw
//                                       iterators.
//                                       By specifying an "Advance" functor,
//                                       the user can change the behaviour of
//                                       the iterator.
//
// ASSUMPTIONS:     - Assumptions made for raw iterators:
//
//                    - The buffer is contiguous
//
//                  - Assumptions made for smart iterators:
//
//                    - The buffer has to define the following members:
//
//                      - size() -- Returns the buffer's size/length
//
//                      - iterator
//                      - const_iterator
//                      - reverse_iterator
//                      - const_reverse_iterator
//
//                      - begin()
//                      - end()
//                      - cbegin()
//                      - cend()
//                      - rbegin()
//                      - rend()
//                      - crbegin()
//                      - crend()
//
// LOGIC:           - The library works in the following way:
//
//                    - It introduces the concept of an "Advance Functor"
//
//                      - This function is assigned by the user to
//                        advance the iterator forward/backward in
//                        different ways:
//                      - For ex. advance the iterator linearly but
//                        never passing the buffer's beginning nor its end.
//                      - For ex. advance the iterator circularly.
//                      - Or the user can provide an "Advance Functor"
//                        to advance the iterator whichever other
//                        way.
//
//                    - It gives random access to non-contiguous buffers
//                      - For examples, buffers that don't offer random access
//                        like std::set, can be used in algorithms that require
//                        random access functionality.
//
//                    - The iterators can be used in standard algorithms.
//                      - NOTE:  Care must be taken when advancing iterators
//                               circularly, because algorithms could fall
//                               into infinite loops.
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:
//
// NOTES:
//
// DATE CREATED:    Dec/30/2013
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
#include <iterator>
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
namespace blIteratorAPI
{
    // A collection of simple functions used to
    // get smart pointers of resources

    #include "blSmartPointerFunctions.hpp"




    // These classes define a raw pointer
    // iterator and reverse iterator for
    // iterating through raw arrays of data

    #include "blRawIterators.hpp"




    // A simple static templated array
    // with some helper functions such
    // as begin, end, size that makes
    // it easy to work with iterators
    // defined in this library

    #include "blArray.hpp"




    // This class is used to wrap a raw
    // static or dynamic array with the
    // basic functionality needed to use
    // the array with the smart iterators
    // in the blIteratorAPI library

    #include "blRawArrayWrapper.hpp"




    // Functors defined in this file are used
    // by iterators in the blIteratorAPI library
    // to "advance" and to get "begin" and "end"
    // iterators.

    #include "blIteratorFunctors.hpp"




    // This class provides a generic iterator which
    // wraps a user specified container.
    // The iterator is customizable through user-provided
    // begin, end, advance and distance functors.
    // Through the user-provided functors, the iterator
    // can for example be made circular, be made to never
    // go pass its end, be made to skip every other place
    // while moving forward, be made into a reverse iterator
    // or much more.

    #include "blIterator.hpp"




    // Define some useful linear iterators

    template<typename blContainerType>
    class blLinearIterator : public blIterator<blContainerType,blAdvanceLinearly,blBeginEnd>{using blIterator<blContainerType,blAdvanceLinearly,blBeginEnd>::blIterator;};

    template<typename blContainerType>
    class blLinearConstIterator : public blIterator<blContainerType,blAdvanceLinearly,blcBeginEnd>{using blIterator<blContainerType,blAdvanceLinearly,blcBeginEnd>::blIterator;};

    template<typename blContainerType>
    class blLinearReverseIterator : public blIterator<blContainerType,blAdvanceLinearly,blrBeginEnd>{using blIterator<blContainerType,blAdvanceLinearly,blrBeginEnd>::blIterator;};

    template<typename blContainerType>
    class blLinearConstReverseIterator : public blIterator<blContainerType,blAdvanceLinearly,blcrBeginEnd>{using blIterator<blContainerType,blAdvanceLinearly,blcrBeginEnd>::blIterator;};

    // Define some useful circular iterators

    template<typename blContainerType>
    class blCircularIterator : public blIterator<blContainerType,blAdvanceCircularly,blBeginEnd>{using blIterator<blContainerType,blAdvanceCircularly,blBeginEnd>::blIterator;};

    template<typename blContainerType>
    class blCircularConstIterator : public blIterator<blContainerType,blAdvanceCircularly,blcBeginEnd>{using blIterator<blContainerType,blAdvanceCircularly,blcBeginEnd>::blIterator;};

    template<typename blContainerType>
    class blCircularReverseIterator : public blIterator<blContainerType,blAdvanceCircularly,blrBeginEnd>{using blIterator<blContainerType,blAdvanceCircularly,blrBeginEnd>::blIterator;};

    template<typename blContainerType>
    class blCircularConstReverseIterator : public blIterator<blContainerType,blAdvanceCircularly,blcrBeginEnd>{using blIterator<blContainerType,blAdvanceCircularly,blcrBeginEnd>::blIterator;};
}
//-------------------------------------------------------------------


#endif // BL_IteratorAPI_HPP
