#ifndef BL_ITERATORFUNCTORS_HPP
#define BL_ITERATORFUNCTORS_HPP


//-------------------------------------------------------------------
// FILE:            blIteratorFunctors.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Functors defined in this file are used
//                  by iterators in the blIteratorAPI library
//                  to "advance" and to get "begin" and "end"
//                  iterators.
//
//                  - The iterator itself
//                  - The container's "begin" and "end" iterators
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    - std::distance -- Used to calculate the
//                                     distance from the beginning
//                                     to the iterator and from the
//                                     iterator to the end if needed
//
//                  - std::advance -- Used to actually advance
//                                    the specified iterator
//                                    once the algorithm has
//                                    decided how much to advance
//                                    it by.
//
// NOTES:
//
// DATE CREATED:    Jan/08/2014
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Define "begin" and "end" functors
// to use with smart iterators
//-------------------------------------------------------------------
struct blBeginEnd
{
    template<typename blContainerType>
    static auto                         begin(blContainerType& container)->decltype(container.begin()){return container.begin();}

    template<typename blContainerType>
    static auto                         end(blContainerType& container)->decltype(container.end()){return container.end();}
};


struct blcBeginEnd
{
    template<typename blContainerType>
    static auto                         begin(const blContainerType& container)->decltype(container.cbegin()){return container.cbegin();}

    template<typename blContainerType>
    static auto                         end(const blContainerType& container)->decltype(container.cend()){return container.cend();}
};


struct blrBeginEnd
{
    template<typename blContainerType>
    static auto                         begin(blContainerType& container)->decltype(container.rbegin()){return container.rbegin();}

    template<typename blContainerType>
    static auto                         end(blContainerType& container)->decltype(container.rend()){return container.rend();}
};


struct blcrBeginEnd
{
    template<typename blContainerType>
    static auto                         begin(const blContainerType& container)->decltype(container.crbegin()){return container.crbegin();}

    template<typename blContainerType>
    static auto                         end(const blContainerType& container)->decltype(container.crend()){return container.crend();}
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functor:            - blAdvanceLinearly
//
// PURPOSE:             - This functor advances an iterator
//                        forward or in reverse but stopping
//                        if it reaches the specified "end" or
//                        "begin" iterators.
//
// DEPENDENCIES:        - blAdvance
//-------------------------------------------------------------------
struct blAdvanceLinearly
{
    template<typename blIteratorType>
    static void         advance(blIteratorType& iter,
                                const ptrdiff_t& howManyStepsToAdvanceIter,
                                const blIteratorType& beginIter,
                                const blIteratorType& endIter,
                                const ptrdiff_t& distanceFromBeginToIter,
                                const ptrdiff_t& distanceFromIterToEnd)
    {
        if(howManyStepsToAdvanceIter > 0)
        {
            if(howManyStepsToAdvanceIter > distanceFromIterToEnd)
                iter = endIter;
            else
                std::advance(iter,howManyStepsToAdvanceIter);
        }
        else if(howManyStepsToAdvanceIter < 0)
        {
            if((-howManyStepsToAdvanceIter) > distanceFromBeginToIter)
                iter = beginIter;
            else
                std::advance(iter,howManyStepsToAdvanceIter);
        }
    }

    template<typename blIteratorType>
    static ptrdiff_t    distance(const blIteratorType& iter1,
                                 const blIteratorType& iter2,
                                 const ptrdiff_t& distanceFromBeginToIter1,
                                 const ptrdiff_t& distanceFromBeginToIter2,
                                 const ptrdiff_t& distanceFromIterToEnd1,
                                 const ptrdiff_t& distanceFromIterToEnd2)
    {
        return ( distanceFromBeginToIter2 - distanceFromBeginToIter1 );
    }
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functor:            - blAdvanceCircularly
//
// PURPOSE:             - This functor advances an iterator
//                        forward or in reverse in a circular
//                        way, simulating a "ring buffer".
//                      - If the iterator is equal to the
//                        "end" iterator, then it is not advanced.
//
// DEPENDENCIES:        - blAdvance
//-------------------------------------------------------------------
struct blAdvanceCircularly
{
    template<typename blIteratorType>
    static void         advance(blIteratorType& iter,
                                const ptrdiff_t& howManyStepsToAdvanceIter,
                                const blIteratorType& beginIter,
                                const blIteratorType& endIter,
                                const ptrdiff_t& distanceFromBeginToIter,
                                const ptrdiff_t& distanceFromIterToEnd)
    {
        if(howManyStepsToAdvanceIter > 0)
        {
            if(howManyStepsToAdvanceIter < distanceFromIterToEnd)
                std::advance(iter,howManyStepsToAdvanceIter);
            else
            {
                iter = beginIter;

                std::advance(
                             iter,
                             (howManyStepsToAdvanceIter - distanceFromIterToEnd) %
                             (distanceFromBeginToIter + distanceFromIterToEnd)
                            );
            }
        }
        else if(howManyStepsToAdvanceIter < 0)
        {
            if((-howManyStepsToAdvanceIter) < distanceFromBeginToIter)
                std::advance(iter,howManyStepsToAdvanceIter);
            else
            {
                iter = beginIter;

                std::advance(
                             iter,
                             (distanceFromBeginToIter + distanceFromIterToEnd) +
                             (howManyStepsToAdvanceIter - distanceFromIterToEnd) %
                             (distanceFromBeginToIter + distanceFromIterToEnd)
                            );
            }
        }
    }

    template<typename blIteratorType>
    static ptrdiff_t    distance(const blIteratorType& iter1,
                                 const blIteratorType& iter2,
                                 const ptrdiff_t& distanceFromBeginToIter1,
                                 const ptrdiff_t& distanceFromBeginToIter2,
                                 const ptrdiff_t& distanceFromIterToEnd1,
                                 const ptrdiff_t& distanceFromIterToEnd2)
    {
        if(distanceFromIterToEnd1 >= distanceFromIterToEnd2)
            return ( std::distance(iter1,iter2) );
        else
        {
            return ( distanceFromIterToEnd1 + distanceFromBeginToIter2);
        }
    }
};
//-------------------------------------------------------------------


#endif // BL_ITERATORFUNCTORS_HPP
