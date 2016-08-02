#ifndef BL_RAWARRAYWRAPPER_HPP
#define BL_RAWARRAYWRAPPER_HPP


//-------------------------------------------------------------------
// FILE:            blRawArrayWrapper.hpp
// CLASS:           blRawArrayWrapper
// BASE CLASS:      None
//
// PURPOSE:         This class is used to wrap a raw
//                  static or dynamic array with the
//                  basic functionality needed to use
//                  the array with the smart iterators
//                  in the blIteratorAPI library
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
// DATE CREATED:    Mar/20/2014
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>

class blRawArrayWrapper
{
public: // Public typedefs

    typedef blRawIterator<blDataType>                       iterator;
    typedef blRawIterator<const blDataType>                 const_iterator;

    typedef blRawReverseIterator<blDataType>                reverse_iterator;
    typedef blRawReverseIterator<const blDataType>          const_reverse_iterator;

public: // Constructors and destructors

    // Default constructor

    blRawArrayWrapper();

    // Copy constructor

    blRawArrayWrapper(const blRawArrayWrapper<blDataType>& rawArrayWrapper) = default;

    // Move constructor

    blRawArrayWrapper(blRawArrayWrapper<blDataType>&& rawArrayWrapper) = default;

    // Constructor using
    // a raw static array

    template<size_t blArraySize>
    blRawArrayWrapper(blDataType (&rawStaticArray)[blArraySize]);

    // Constructor using
    // a raw array

    blRawArrayWrapper(blDataType* rawArray,
                      const size_t& arraySize);

    // Destructor

    ~blRawArrayWrapper()
    {
    }

public: // Public functions

    // Additional operator
    // overloads

    bool                                                    operator==(const blRawArrayWrapper<blDataType>& array)const;
    bool                                                    operator!=(const blRawArrayWrapper<blDataType>& array)const;

    // Element access
    // functions

    blDataType&                                             operator[](const size_t elementIndex);
    const blDataType&                                       operator[](const size_t elementIndex)const;

    // Functions used
    // to return the
    // array size

    size_t                                                  length()const;
    size_t                                                  size()const;
    size_t                                                  max_size()const;
    bool                                                    empty()const;

    // Function used to
    // get the container
    // iterator

    const iterator&                                         getContainerIter()const;
    const_iterator                                          getContainerConstIter()const;

    // Functions used to
    // get iterators to
    // this container

    iterator                                                begin();
    iterator                                                end();
    const_iterator                                          cbegin()const;
    const_iterator                                          cend()const;

    reverse_iterator                                        rbegin();
    reverse_iterator                                        rend();
    const_reverse_iterator                                  crbegin()const;
    const_reverse_iterator                                  crend()const;

private: // Private variables

    // The pointer to the
    // raw array data

    iterator                                                m_containerIter;

    // The size/length of
    // the raw array

    size_t                                                  m_size;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRawArrayWrapper<blDataType>::blRawArrayWrapper()
{
    m_size = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<size_t blArraySize>
inline blRawArrayWrapper<blDataType>::blRawArrayWrapper(blDataType (&rawStaticArray)[blArraySize])
{
    if(blArraySize > 0)
        m_containerIter = iterator(&rawStaticArray[0]);

    m_size = blArraySize;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRawArrayWrapper<blDataType>::blRawArrayWrapper(blDataType* rawArray,
                                                        const size_t& arraySize)
{
    m_containerIter = iterator(rawArray);
    m_size = arraySize;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>

inline const typename blRawArrayWrapper<blDataType>::iterator&

blRawArrayWrapper<blDataType>::getContainerIter()const
{
    return m_containerIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>

inline typename blRawArrayWrapper<blDataType>::const_iterator

blRawArrayWrapper<blDataType>::getContainerConstIter()const
{
    return m_containerIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blRawArrayWrapper<blDataType>::operator==(const blRawArrayWrapper<blDataType>& rawArrayWrapper)const
{
    if(!m_containerIter || !rawArrayWrapper.getContainerIter())
        return false;

    if(this == &rawArrayWrapper)
        return true;

    auto iter1 = cbegin();
    auto iter2 = rawArrayWrapper.cbegin();

    for(;
        iter1 != cend(),iter2 != rawArrayWrapper.cend();
        ++iter1,++iter2)
    {
        if((*iter1) != (*iter2))
            return false;
    }

    return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blRawArrayWrapper<blDataType>::operator!=(const blRawArrayWrapper<blDataType>& array)const
{
    return !( (*this) == array );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blRawArrayWrapper<blDataType>::operator[](const size_t elementIndex)
{
    return m_containerIter[elementIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blRawArrayWrapper<blDataType>::operator[](const size_t elementIndex)const
{
    return m_containerIter[elementIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline size_t blRawArrayWrapper<blDataType>::length()const
{
    return m_size;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline size_t blRawArrayWrapper<blDataType>::size()const
{
    return m_size;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline size_t blRawArrayWrapper<blDataType>::max_size()const
{
    return m_size;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blRawArrayWrapper<blDataType>::empty()const
{
    return (m_size != 0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The iterators
//-------------------------------------------------------------------
template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::iterator blRawArrayWrapper<blDataType>::begin()
{
    return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::iterator blRawArrayWrapper<blDataType>::end()
{
    if(m_containerIter)
        return (m_containerIter + size());
    else
        return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::const_iterator blRawArrayWrapper<blDataType>::cbegin()const
{
    return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::const_iterator blRawArrayWrapper<blDataType>::cend()const
{
    if(m_containerIter)
        return (m_containerIter + size());
    else
        return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::reverse_iterator blRawArrayWrapper<blDataType>::rbegin()
{
    if(m_containerIter && (size() > 0))
        return reverse_iterator(m_containerIter + size() - 1);
    else
        return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::reverse_iterator blRawArrayWrapper<blDataType>::rend()
{
    if(m_containerIter && (size() > 0))
        return (m_containerIter - 1);
    else
        return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::const_reverse_iterator blRawArrayWrapper<blDataType>::crbegin()const
{
    if(m_containerIter && (size() > 0))
        return (m_containerIter + size() - 1);
    else
        return m_containerIter;
}

template<typename blDataType>
inline typename blRawArrayWrapper<blDataType>::const_reverse_iterator blRawArrayWrapper<blDataType>::crend()const
{
    if(m_containerIter && (size() > 0))
        return (m_containerIter - 1);
    else
        return m_containerIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to easily initialize
// a raw array wrapper
//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
blRawArrayWrapper<blDataType> getRawArrayWrapper(blDataType (&rawStaticArray)[blArraySize])
{
    return blRawArrayWrapper<blDataType>(rawStaticArray);
}

template<typename blDataType>
blRawArrayWrapper<blDataType> getRawArrayWrapper(blDataType* rawArray,
                                                 const size_t& arraySize)
{
    return blRawArrayWrapper<blDataType>(rawArray,
                                         arraySize);
}
//-------------------------------------------------------------------


#endif // BL_RAWARRAYWRAPPER_HPP
