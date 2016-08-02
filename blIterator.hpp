#ifndef BL_ITERATOR_HPP
#define BL_ITERATOR_HPP


//-------------------------------------------------------------------
// FILE:            blIterator.hpp
// CLASS:           blIterator
// BASE CLASS:      None
//
// PURPOSE:         This class provides a generic iterator which
//                  wraps a user specified container.
//                  The iterator is customizable through user-provided
//                  begin, end, advance and distance functors.
//                  Through the user-provided functors, the iterator
//                  can for example be made circular, be made to never
//                  go pass its end, be made to skip every other place
//                  while moving forward, be made into a reverse iterator
//                  or much more.
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
// DATE CREATED:    Dec/02/2013
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blContainerType,
         typename blAdvanceDistanceFunctorType,
         typename blBeginEndFunctorType>

class blIterator : public std::iterator< std::random_access_iterator_tag,
                                         typename std::iterator_traits<decltype(blBeginEndFunctorType::begin(std::declval<blContainerType&>()))>::value_type,
                                         typename std::iterator_traits<decltype(blBeginEndFunctorType::begin(std::declval<blContainerType&>()))>::difference_type,
                                         typename std::iterator_traits<decltype(blBeginEndFunctorType::begin(std::declval<blContainerType&>()))>::pointer,
                                         typename std::iterator_traits<decltype(blBeginEndFunctorType::begin(std::declval<blContainerType&>()))>::reference >
{
public: // Public typedefs

    typedef typename std::shared_ptr<blContainerType>                                           blContainerPtr;

    typedef typename std::iterator_traits<typename blContainerType::iterator>::value_type       blDataType;
    typedef typename std::iterator_traits<typename blContainerType::iterator>::pointer          blDataTypePtr;
    typedef typename std::iterator_traits<typename blContainerType::iterator>::reference        blDataTypeRef;

    typedef decltype(blBeginEndFunctorType::begin(std::declval<blContainerType&>()))            iterator;

private: // Private variables

    // The iterator
    // to the data
    // point

    iterator                                                        m_ptr;

    // The raw pointer
    // to the dat Container

    blContainerPtr                                                  m_containerPtr;

public: // Constructors and destructors

    // Default constructors

    blIterator() = default;

    // Construct from container

    blIterator(blContainerType& container)
    {
        m_containerPtr = get_shared_ptr(container);

        if(m_containerPtr)
            m_ptr = blBeginEndFunctorType::begin(*m_containerPtr);
    }

    // Construct from container
    // pointer

    blIterator(blContainerType* containerPtr)
    {
        m_containerPtr = get_shared_ptr(containerPtr);

        if(m_containerPtr)
            m_ptr = blBeginEndFunctorType::begin(*m_containerPtr);
    }

    // Construct from container
    // shared pointer

    blIterator(const blContainerPtr& containerPtr)
    {
        m_containerPtr = containerPtr;

        if(m_containerPtr)
            m_ptr = blBeginEndFunctorType::begin(*m_containerPtr);
    }

    // Construct from iterator
    // and container shared pointer

    blIterator(const iterator& ptr,
               const blContainerPtr& containerPtr)
    {
        m_ptr = ptr;
        m_containerPtr = containerPtr;
    }

    // Copy constructor

    blIterator(const blIterator<blContainerType,blAdvanceDistanceFunctorType,blBeginEndFunctorType>&) = default;

    // Move constructor

    blIterator(blIterator<blContainerType,blAdvanceDistanceFunctorType,blBeginEndFunctorType>&&) = default;

    // Destructor

    ~blIterator()
    {
    }

public: // Assignment operator

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>&                              operator=(const blIterator<blContainerType,blAdvanceDistanceFunctorType,blBeginEndFunctorType>& iterator) = default;

public: // Dereferencing operators

    blDataTypeRef                                                   operator*(){return (*m_ptr);}
    const blDataTypeRef                                             operator*()const{return (*m_ptr);}
    iterator                                                        operator->(){return m_ptr;}

public: // Overloaded operators

    // Equality and
    // inequality
    // operators

    bool                                                            operator==(const blIterator<blContainerType,blAdvanceDistanceFunctorType,blBeginEndFunctorType>& iterator)const
    {
        return ( (m_ptr == iterator.getPtr()) &&
                 (m_containerPtr == iterator.getContainerPtr()) );
    }

    bool                                                            operator!=(const blIterator<blContainerType,blAdvanceDistanceFunctorType,blBeginEndFunctorType>& iterator)const
    {
        return ( (m_ptr != iterator.getPtr()) ||
                 (m_containerPtr != iterator.getContainerPtr()) );
    }

    // Bool operator
    // so that this
    // iterator can be
    // used in if statements

    explicit operator                                               bool()const
    {
        if(this->m_containerPtr)
            return true;
        else
            return false;
    }

    // Increment/decrement
    // operators

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>&                              operator++()
    {
        this->advance(1);
        return (*this);
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>                               operator++(int)
    {
        auto TempIter(*this);

        this->advance(1);

        return TempIter;
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>&                              operator--()
    {
        this->advance(-1);
        return (*this);
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>                               operator--(int)
    {
        auto TempIter(*this);

        this->advance(-1);

        return TempIter;
    }

    // Operators used to
    // advance a random
    // access iterator

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>&                              operator+=(const ptrdiff_t& Offset)
    {
        this->advance(Offset);
        return (*this);
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>&                              operator-=(const ptrdiff_t& Offset)
    {
        this->advance(-Offset);
        return (*this);
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>                               operator+(const ptrdiff_t& Offset)const
    {
        auto NewIter = (*this);
        NewIter.advance(Offset);
        return NewIter;
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>                               operator-(const ptrdiff_t& Offset)const
    {
        auto NewIter = (*this);
        NewIter.advance(-Offset);
        return NewIter;
    }

    // Operator used
    // to calculate
    // the distance
    // between two
    // iterators

    ptrdiff_t                                                       operator-(const blIterator<blContainerType,blAdvanceDistanceFunctorType,blBeginEndFunctorType>& iterator)const
    {
        return blAdvanceDistanceFunctorType::distance(this->getDistanceFromBeginToIter(),
                                                      iterator.getDistanceFromBeginToIter(),
                                                      this->getDistanceFromIterToEnd(),
                                                      iterator.getDistanceFromIterToEnd());
    }

public: // Public functions

    // Functions used to
    // set the Container pointer

    void                                                            setContainerPtr(blContainerType& container)
    {
        auto containerPtr = get_shared_ptr(container);

        if(containerPtr != m_containerPtr)
        {
            m_containerPtr = containerPtr;

            if(m_containerPtr)
            {
                (*this) = this->begin();
            }
        }
    }

    void                                                            setContainerPtr(const blContainerType& container)
    {
        auto containerPtr = get_shared_ptr(container);

        if(containerPtr != m_containerPtr)
        {
            m_containerPtr = containerPtr;

            if(m_containerPtr)
            {
                (*this) = this->begin();
            }
        }
    }

    void                                                            setContainerPtr(blContainerType* rawContainerPtr)
    {
        auto containerPtr = get_shared_ptr(rawContainerPtr);

        if(containerPtr != m_containerPtr)
        {
            m_containerPtr = containerPtr;

            if(m_containerPtr)
            {
                (*this) = this->begin();
            }
        }
    }

    // Functions used to
    // get the raw pointer
    // and iterator

    const iterator&                                                 getPtr()const{return m_ptr;}
    const blContainerPtr&                                           getContainerPtr()const{return m_containerPtr;}

    // Functions used to
    // get the distance
    // from the begin
    // to the iterator
    // and from the iterator
    // to the end

    ptrdiff_t                                                       getDistanceFromBeginToIter()const
    {
        if(m_containerPtr)
            return std::distance(blBeginEndFunctorType::begin(*m_containerPtr),this->m_ptr);
        else
            return 0;
    }

    ptrdiff_t                                                       getDistanceFromIterToEnd()const
    {
        if(m_containerPtr)
            return std::distance(this->m_ptr,blBeginEndFunctorType::end(*m_containerPtr));
        else
            return 0;
    }

    // Functions used to
    // return iterators
    // to the "begin" and
    // "end" data points
    // of the Container

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>                               begin()const
    {
        if(m_containerPtr)
        {
            return blIterator<blContainerType,
                              blAdvanceDistanceFunctorType,
                              blBeginEndFunctorType>(blBeginEndFunctorType::begin(*m_containerPtr),
                                                     m_containerPtr);
        }
        else
            return blIterator<blContainerType,
                              blAdvanceDistanceFunctorType,
                              blBeginEndFunctorType>(m_containerPtr);
    }

    blIterator<blContainerType,
               blAdvanceDistanceFunctorType,
               blBeginEndFunctorType>                               end()const
    {
        if(m_containerPtr)
        {
            return blIterator<blContainerType,
                              blAdvanceDistanceFunctorType,
                              blBeginEndFunctorType>(blBeginEndFunctorType::end(*m_containerPtr),
                                                     m_containerPtr);
        }
        else
            return blIterator<blContainerType,
                              blAdvanceDistanceFunctorType,
                              blBeginEndFunctorType>(m_containerPtr);
    }

    // Operators used to
    // access data elements
    // from the container
    // directly
    //
    // NOTE:    These operators do
    //          not check for out of
    //          bound indices

    blDataTypeRef                                                   operator[](const size_t& index){return (*(this->begin() + index));}
    const blDataTypeRef                                             operator[](const size_t& index)const{return (*(this->begin() + index));}



    // Functions used
    // to return the
    // container's size

    size_t                                                          size()const
    {
        if(m_containerPtr)
            return m_containerPtr->size();
        else
            return 0;
    }

    size_t                                                          length()const{return this->size();}
    size_t                                                          max_size()const{return this->size();}
    bool                                                            empty()const{return (this->size() == 0);}

private: // Special functions
    
    // Function used
    // to advance the
    // iterator
    
    void                                                            advance(const ptrdiff_t& HowManyStepsToAdvanceIter)
    {
        if(m_containerPtr)
        {
            blAdvanceDistanceFunctorType::advance(m_ptr,
                                                  HowManyStepsToAdvanceIter,
                                                  this->begin().m_ptr,
                                                  this->end().m_ptr,
                                                  this->getDistanceFromBeginToIter(),
                                                  this->getDistanceFromIterToEnd());
        }
    }
};
//-------------------------------------------------------------------


#endif // BL_ITERATOR_HPP
