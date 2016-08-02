#ifndef BL_SMARTPOINTERFUNCTIONS_HPP
#define BL_SMARTPOINTERFUNCTIONS_HPP


//-------------------------------------------------------------------
// FILE:            blSmartPointerFunctions.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         A collection of simple functions used to
//                  get smart pointers of resources.
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    - std::shared_ptr
//
// NOTES:
//
// DATE CREATED:    Oct/04/2013
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:                null_deleter
//
// PURPOSE:                 Used when creating std::shared_ptr
//                          smart pointers so the shared pointer
//                          doesn't try to release the resource
//                          being pointed to.
//-------------------------------------------------------------------
template<typename blResourceType>
class null_deleter
{
public:

    void operator()(blResourceType const*)const
    {
    }
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to get shared pointers of resources
//
// NOTE:    The resources can be passed as references
//          or pointers, and if passed by pointer, the
//          returned shared pointer can be set in charge
//          of deleting the pointer or not.
//-------------------------------------------------------------------
template<typename blResourceType>
inline std::shared_ptr<blResourceType> get_shared_ptr(blResourceType& theResource)
{
    return std::shared_ptr<blResourceType>(&theResource,null_deleter<blResourceType>());
}

template<typename blResourceType>
inline std::shared_ptr<blResourceType const> get_const_shared_ptr(const blResourceType& theResource)
{
    return std::shared_ptr<blResourceType const>(&theResource,null_deleter<const blResourceType>());
}

template<typename blResourceType>
inline std::shared_ptr<blResourceType> get_shared_ptr(blResourceType* theResource)
{
    return std::shared_ptr<blResourceType>(theResource,null_deleter<blResourceType>());
}

template<typename blResourceType>
inline std::shared_ptr<blResourceType const> get_const_shared_ptr(blResourceType const* theResource)
{
    return std::shared_ptr<blResourceType const>(theResource,null_deleter<const blResourceType>());
}

template<typename blResourceType>
inline std::shared_ptr<blResourceType> get_shared_ptr_and_delete_when_done(blResourceType* theResource)
{
    return std::shared_ptr<blResourceType>(theResource);
}

template<typename blResourceType>
inline std::shared_ptr<blResourceType const> get_const_shared_ptr_and_delete_when_done(blResourceType const* theResource)
{
    return std::shared_ptr<blResourceType const>(theResource);
}
//-------------------------------------------------------------------


#endif // BL_SMARTPOINTERFUNCTIONS_HPP
