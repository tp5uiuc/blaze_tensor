//=================================================================================================
/*!
//  \file blaze_tensor/math/traits/RowSliceTrait.h
//  \brief Header file for the page trait
//
//  Copyright (C) 2012-2018 Klaus Iglberger - All Rights Reserved
//  Copyright (C) 2018 Hartmut Kaiser - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_TENSOR_MATH_TRAITS_ROWSLICETRAIT_H_
#define _BLAZE_TENSOR_MATH_TRAITS_ROWSLICETRAIT_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <utility>
#include <blaze/math/Infinity.h>
#include <blaze/util/InvalidType.h>
#include <blaze/util/Types.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename, size_t... > struct RowSliceTrait;
template< typename, size_t, typename = void > struct RowSliceTraitEval1;
template< typename, size_t, typename = void > struct RowSliceTraitEval2;
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< size_t I, typename T >
auto evalRowSliceTrait( T& )
   -> typename RowSliceTraitEval1<T,I>::Type;

template< typename T >
auto evalRowSliceTrait( T& )
   -> typename RowSliceTraitEval2<T,inf>::Type;

template< size_t I, typename T >
auto evalRowSliceTrait( const T& )
   -> typename RowSliceTrait<T,I>::Type;

template< typename T >
auto evalRowSliceTrait( const T& )
   -> typename RowSliceTrait<T>::Type;

template< size_t I, typename T >
auto evalRowSliceTrait( const volatile T& )
   -> typename RowSliceTrait<T,I>::Type;

template< typename T >
auto evalRowSliceTrait( const volatile T& )
   -> typename RowSliceTrait<T>::Type;
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Base template for the RowSliceTrait class.
// \ingroup math_traits
//
// \section pagetrait_general General
//
// The RowSliceTrait class template offers the possibility to select the resulting data type when
// creating a view on a specific page of a dense or sparse tensor. RowSliceTrait defines the nested
// type \a Type, which represents the resulting data type of the page operation. In case the
// given data type is not a dense or sparse tensor type, the resulting data type \a Type is
// set to \a INVALID_TYPE. Note that \a const and \a volatile qualifiers and reference modifiers
// are generally ignored.
//
//
// \section pagetrait_specializations Creating custom specializations
//
// Per default, RowSliceTrait supports all tensor types of the Blaze library (including views and
// adaptors). For all other data types it is possible to specialize the RowSliceTrait template. The
// following example shows the according specialization for the DynamicTensor class template:

   \code
   template< typename T1, size_t... CRAs >
   struct RowSliceTrait< DynamicTensor<T1>, CRAs... >
   {
      using Type = DynamicMatrix<T1,false>;
   };
   \endcode

// \n \section pageslicetrait_examples Examples
//
// The following example demonstrates the use of the RowSliceTrait template, where depending on
// the given tensor type the resulting page type is selected:

   \code
   // Definition of the page type of a dynamic tensor
   using TensorType1 = blaze::DynamicTensor<int>;
   using ResultType1 = typename blaze::RowSliceTrait<TensorType1>::Type;
   \endcode
*/
template< typename MT       // Type of the tensor
        , size_t... CRAs >  // Compile time page arguments
struct RowSliceTrait
{
 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   using Type = decltype( evalRowSliceTrait<CRAs...>( std::declval<MT&>() ) );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Auxiliary alias declaration for the RowSliceTrait type trait.
// \ingroup math_traits
//
// The RowSliceTrait_t alias declaration provides a convenient shortcut to access the nested
// \a Type of the RowSliceTrait class template. For instance, given the tensor type \a MT the
// following two type definitions are identical:

   \code
   using Type1 = typename blaze::RowSliceTrait<MT>::Type;
   using Type2 = blaze::RowSliceTrait_t<MT>;
   \endcode
*/
template< typename MT       // Type of the tensor
        , size_t... CRAs >  // Compile time page arguments
using RowSliceTrait_t = typename RowSliceTrait<MT,CRAs...>::Type;
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief First auxiliary helper struct for the RowSliceTrait type trait.
// \ingroup math_traits
*/
template< typename MT  // Type of the tensor
        , size_t I     // Compile time page index
        , typename >   // Restricting condition
struct RowSliceTraitEval1
{
 public:
   //**********************************************************************************************
   using Type = typename RowSliceTraitEval2<MT,I>::Type;
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Second auxiliary helper struct for the RowSliceTrait type trait.
// \ingroup math_traits
*/
template< typename MT  // Type of the tensor
        , size_t I     // Compile time page index
        , typename >   // Restricting condition
struct RowSliceTraitEval2
{
 public:
   //**********************************************************************************************
   using Type = INVALID_TYPE;
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
