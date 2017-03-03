// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_UTIL_FUNCTIONAL_HPP__
#define __TPC_UTIL_FUNCTIONAL_HPP__

#include <type_traits>
#include <utility>


namespace tpc::Util::Functional {
  typedef decltype(nullptr) void_t;
  constexpr void_t unit = nullptr;
  
  
  template<typename T, typename U>
  constexpr inline void_t ignore(
    [[gnu::unused]] const T& _,
    [[gnu::unused]] const U& _1
  ) {
    return unit;
  }
  
  
  template<
    typename T,
    typename = std::is_constructible<T>
  >
  T construct() { return T(); }
  
  
  template<typename T, T value>
  constexpr inline T cons() { return value; }
  
  template<typename T, typename U, T value>
  constexpr inline T cons([[gnu::unused]] const U& _) { return value; }
  
  template<typename T, typename U, T (&gen)()>
  constexpr inline T cons([[gnu::unused]] const U& _) { return gen(); }
  
  
  template<typename T>
  constexpr inline T id(const T value) { return value; }
  
  template<typename T>
  constexpr inline T id(T&& value) { return std::forward(value); }
  
  
  template<typename T, typename U>
  constexpr inline U apply(U (* const f)(const T), T& value) { // Unsafe.
    return f(value);
  }
  
  template<typename T, typename U>
  constexpr inline U apply(U (* const f)(T), T&& value) { // Unsafe.
    return f(std::forward(value));
  }
  
  
  template<typename T>
  constexpr inline T negate(const T value) { return -value; }
  
  template<typename T>
  constexpr inline T negate(T&& value) { return -std::forward<T>(value); }
  
  
  template<typename T, typename... Ts>
  constexpr inline T fst(
    const T& val,
    const Ts&...
  ) {
    return val;
  }
  
  template<typename T, typename U, typename... Ts>
  constexpr inline U snd(
    const T&,
    const U& val,
    const Ts&...
  ) {
    return val;
  }
  
  template<typename T, typename U, typename V, typename... Ts>
  constexpr inline V trd(
    const T&,
    const U&,
    const V& val,
    const Ts&...
  ) {
    return val;
  }
}


#endif /* __TPC_UTIL_FUNCTIONAL_HPP__ */
