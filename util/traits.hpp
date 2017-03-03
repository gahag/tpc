// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_UTIL_TRAITS_HPP__
#define __TPC_UTIL_TRAITS_HPP__

#include <type_traits>


namespace tpc::Util::Traits {
  template<typename T, typename U>
  using is_same = typename std::enable_if<std::is_same<T, U>::value, bool>::type;
  
  
  template<typename T>
  using isnt_cvref = typename std::enable_if<
                                std::negation<
                                  std::disjunction<std::is_const<T>,
                                                   std::is_volatile<T>,
                                                   std::is_reference<T>>
                                >::value,
                                bool
                              >::type;
  
  
  template<typename T, typename... Args>
  using is_constructible = typename std::enable_if<
                                      std::is_constructible<T, Args...>::value,
                                      bool
                                    >::type;
  
  template<typename T>
  using is_move_constructible = typename std::enable_if<
                                          std::is_move_constructible<T>::value,
                                          bool
                                         >::type;
  
  
  template<typename N>
  using is_numeric = typename std::enable_if<std::is_arithmetic<N>::value, bool>::type;
  
  template<typename N>
  using is_integral = typename std::enable_if<std::is_integral<N>::value, bool>::type;
  
  template<typename N>
  using is_floating = typename std::enable_if<std::is_floating_point<N>::value, bool>::type;
  
  template<typename N>
  using is_signed = typename std::enable_if<std::is_signed<N>::value, bool>::type;
  
  template<typename N>
  using is_unsigned = typename std::enable_if<std::is_unsigned<N>::value, bool>::type;
}


#endif /* __TPC_UTIL_TRAITS_HPP__ */
