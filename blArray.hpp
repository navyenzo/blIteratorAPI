#ifndef BL_ARRAY_HPP
#define BL_ARRAY_HPP


//-------------------------------------------------------------------
// FILE:            blArray.hpp
// CLASS:           blArray
// BASE CLASS:      None
//
// PURPOSE:         A simple static templated array
//                  with some helper functions such
//                  as begin, end, size that makes
//                  it easy to work with iterators
//                  defined in this library
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
// DATE CREATED:    Mar/17/2014
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>

class blArray
{
public: // Public typedefs

    typedef blRawIterator<blDataType>                       iterator;
    typedef blRawIterator<const blDataType>                 const_iterator;

    typedef blRawReverseIterator<blDataType>                reverse_iterator;
    typedef blRawReverseIterator<const blDataType>          const_reverse_iterator;

public: // Constructors and destructors

    // Default constructor

    blArray();

    // Copy constructor

    blArray(const blArray<blDataType,blArraySize>& array) = default;

    // Move constructor

    blArray(blArray<blDataType,blArraySize>&& array) = default;

    // Copy constructor
    // from a different
    // size and/or different
    // data type array

    template<typename blDataType2,size_t blArraySize2>
    blArray(const blArray<blDataType2,blArraySize2>& array);

    // Constructor using
    // a raw array

    template<typename blDataType2,size_t blArraySize2>
    blArray(const blDataType2 (&staticArray)[blArraySize2]);

    // Constructor using
    // iterators

    template<typename blIteratorType>
    blArray(blIteratorType sourceBegin,
            const blIteratorType& sourceEnd);

    // Destructor

    ~blArray()
    {
    }

public: // Assignment operators

    blArray<blDataType,blArraySize>&                        operator=(const blArray<blDataType,blArraySize>& array);

    template<typename blDataType2,size_t blArraySize2>
    blArray<blDataType,blArraySize>&                        operator=(const blArray<blDataType2,blArraySize2>& array);

public: // Public functions

    // Additional operator
    // overloads

    bool                                                    operator==(const blArray<blDataType,blArraySize>& array)const;
    bool                                                    operator!=(const blArray<blDataType,blArraySize>& array)const;

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
    // swap values between
    // two arrays of
    // equal length

    void                                                    swap(const blArray<blDataType,blArraySize>& Array);

    // Function used to
    // fill the array
    // with a specified
    // value

    void                                                    fill(const blDataType& value);

    // Function used to
    // return a reference
    // to the front and
    // back elements

    blDataType&                                             front();
    const blDataType&                                       front()const;

    blDataType&                                             back();
    const blDataType&                                       back()const;

    // Functions used to
    // get a raw pointer
    // to the first element

    blDataType*                                             data();
    const blDataType*                                       data()const;
    const blDataType*                                       c_str()const;

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

private: // Private data

    // The raw array

    blDataType                                              m_container[blArraySize];

    // The null end
    // element useful
    // when using this
    // array as a constant
    // character string

    blDataType                                              m_nullChar;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline blArray<blDataType,blArraySize>::blArray() : m_nullChar(0)
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
template<typename blDataType2,size_t blArraySize2>
inline blArray<blDataType,blArraySize>::blArray(const blArray<blDataType2,blArraySize2>& array) : m_nullChar(0)
{
    auto Iter1 = this->begin();
    auto Iter2 = array.begin();

    for(;
        Iter1 != this->end(),Iter2 != array.end();
        ++Iter1,++Iter2)
    {
        (*Iter1) = (*Iter2);
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
template<typename blDataType2,size_t blArraySize2>
inline blArray<blDataType,blArraySize>::blArray(const blDataType2 (&staticArray)[blArraySize2]) : m_nullChar(0)
{
    auto Iter1 = this->begin();

    for(size_t i = 0;
        Iter1 != this->end(),i < blArraySize2;
        ++Iter1,++i)
    {
        (*Iter1) = staticArray[i];
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
template<typename blIteratorType>
inline blArray<blDataType,blArraySize>::blArray(blIteratorType sourceBegin,
                                                const blIteratorType& sourceEnd) : m_nullChar(0)
{
    auto Iter1 = this->begin();

    for(size_t i = 0;
        Iter1 != this->end(),sourceBegin != sourceEnd;
        ++Iter1,sourceBegin)
    {
        (*Iter1) = (*sourceBegin);
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline blArray<blDataType,blArraySize>& blArray<blDataType,blArraySize>::operator=(const blArray<blDataType,blArraySize>& array)
{
    if(this != &array)
    {
        for(size_t i = 0; i < blArraySize; ++i)
            m_container[i] = array[i];
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
template<typename blDataType2,size_t blArraySize2>
inline blArray<blDataType,blArraySize>& blArray<blDataType,blArraySize>::operator=(const blArray<blDataType2,blArraySize2>& array)
{
    if(this != &array)
    {
        auto iter1 = this->begin();
        auto iter2 = array.begin();

        for(;
            iter1 != this->end(),iter2 != array.end();
            ++iter1,++iter2)
        {
            (*iter1) = (*iter2);
        }
    }

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline bool blArray<blDataType,blArraySize>::operator==(const blArray<blDataType,blArraySize>& array)const
{
    if(this == &array)
        return true;

    auto iter1 = cbegin();
    auto iter2 = array.cbegin();

    for(;
        iter1 != cend(),iter2 != array.cend();
        ++iter1,++iter2)
    {
        if((*iter1) != (*iter2))
            return false;
    }

    return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline bool blArray<blDataType,blArraySize>::operator!=(const blArray<blDataType,blArraySize>& array)const
{
    return !( (*this) == array );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline blDataType& blArray<blDataType,blArraySize>::operator[](const size_t elementIndex)
{
    return m_container[elementIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline const blDataType& blArray<blDataType,blArraySize>::operator[](const size_t elementIndex)const
{
    return m_container[elementIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline size_t blArray<blDataType,blArraySize>::length()const
{
    return blArraySize;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline size_t blArray<blDataType,blArraySize>::size()const
{
    return blArraySize;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline size_t blArray<blDataType,blArraySize>::max_size()const
{
    return blArraySize;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline bool blArray<blDataType,blArraySize>::empty()const
{
    return (blArraySize != 0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline void blArray<blDataType,blArraySize>::swap(const blArray<blDataType, blArraySize>& Array)
{
    blDataType TempValue;

    for(size_t i = 0; i < blArraySize; ++i)
    {
        TempValue = m_container[i];
        m_container[i] = Array[i];
        Array[i] = TempValue;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline void blArray<blDataType,blArraySize>::fill(const blDataType& value)
{
    for(size_t i = 0; i < blArraySize; ++i)
        m_container[i] = value;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline blDataType& blArray<blDataType,blArraySize>::front()
{
    return m_container[0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline const blDataType& blArray<blDataType,blArraySize>::front()const
{
    return m_container[0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline blDataType& blArray<blDataType,blArraySize>::back()
{
    return m_container[blArraySize - 1];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline const blDataType& blArray<blDataType,blArraySize>::back()const
{
    return m_container[blArraySize - 1];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline blDataType* blArray<blDataType,blArraySize>::data()
{
    return &m_container[0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline const blDataType* blArray<blDataType,blArraySize>::data()const
{
    return &m_container[0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline const blDataType* blArray<blDataType,blArraySize>::c_str()const
{
    return &m_container[0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The iterators
//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::iterator blArray<blDataType,blArraySize>::begin()
{
    return &(m_container[0]);
}

template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::iterator blArray<blDataType,blArraySize>::end()
{
    return &(m_container[blArraySize]);
}
template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::const_iterator blArray<blDataType,blArraySize>::cbegin()const
{
    return &(m_container[0]);
}

template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::const_iterator blArray<blDataType,blArraySize>::cend()const
{
    return &(m_container[blArraySize]);
}
template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::reverse_iterator blArray<blDataType,blArraySize>::rbegin()
{
    return &(m_container[blArraySize - 1]);
}

template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::reverse_iterator blArray<blDataType,blArraySize>::rend()
{
    return &(m_container[-1]);
}
template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::const_reverse_iterator blArray<blDataType,blArraySize>::crbegin()const
{
    return &(m_container[blArraySize - 1]);
}

template<typename blDataType,size_t blArraySize>
inline typename blArray<blDataType,blArraySize>::const_reverse_iterator blArray<blDataType,blArraySize>::crend()const
{
    return &(m_container[-1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to automatically deduct
// the type and size of array from a raw
// array
//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
blArray<blDataType,blArraySize> getArray(const blDataType (&staticArray)[blArraySize])
{
    return blArray<blDataType,blArraySize>(staticArray);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to automatically deduct
// the type and size of array from a NULL
// terminated array
//-------------------------------------------------------------------
template<typename blDataType,size_t blArraySize>
blArray<blDataType,blArraySize - 1> getArrayFromNullTerminated(const blDataType (&staticArray)[blArraySize])
{
    return blArray<blDataType,blArraySize - 1>(staticArray);
}
//-------------------------------------------------------------------


#endif // BL_ARRAY_HPP
