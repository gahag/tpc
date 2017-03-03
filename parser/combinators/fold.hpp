// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_FOLD_HPP__
#define __TPC_PARSER_COMBINATORS_FOLD_HPP__

#include <tpc/parser/base.hpp>


// fold<T, p, U, [val|gen], f>:
// fold<T, p, U, f>(U, stream):
// fold<T, p, U, f>(U&&, stream):
// 
// fold consists of:
// * A parser `p` for values of type `T`.
// * A initial value of type `U`.
// * A accumulating function `f`, that transforms
//   two values of types U and T into a value of type U.
// 
// The parser `p` is subsequently applied until it fails. The produced results are
// combined with the accumulated value via the accumulating function.
// If `p` fails at the first application, fold succeeds returning the initial value.
// E.g.:
// Considering `f` to be of type `U (U, T)`, let `v₀` be the initial value, and `vₙ`
// be the values produced by subsequent applications of `p` until failure, from 1 to n.
// * If `p` fails at the first application, the result of fold is equivalent to `v₀`.
// * If `p` succeeded only once, the result of fold is equivalent to `f(v₀, v₁)`.
// * If `p` succeeded twice, the result of fold is equivalent to `f(f(v₀, v₁), v₂)`.
// 
// 
// There are four forms of supplying the initial value of type `U`:
// 
//  A literal value as a template argument.
//  E.g: tpc::fold<int, tpc::digit<int>
//                 int, 5,
//                 [](int x, int y) { return x + y; }>
//  
//  A generator function as a template argument.
//  E.g: tpc::fold<char,        tpc::any,
//                 std::string, []() { return "parsed: "; },
//                 &std::string::push_back                  >
//  
//  A value as the function parameter.
//  E.g: std::string str;
//       std::getline(std::cin, str);
//       tpc::fold<char,        tpc::any,
//                 std::string, &std::string::push_back>(str, <insert stream here>);
// 
//  A rvalue as the function parameter.
//  E.g: std::string str;
//       std::getline(std::cin, str);
//       tpc::fold<char,        tpc::any,
//                 std::string, &std::string::push_back>(std::move(str),
//                                                       <insert stream here>);
// 
// 
// The following signatures are allowed for `f`:
// 
//  returning the result: U (&f)(U, T)
//                      : U (&f)(const U&, const T&)
//                      : U (&f)(U&&, T&&)
//  
//  by passing mutable reference: void (&f)(U&, T)
//                              : void (&f)(U&, T&&)
//                              : void (&f)(U&, T&&)
//  
//  non-const member function: void (U::*f)(T)
//                           : void (U::*f)(const T&)
//                           : void (U::*f)(T&&)


// fold1<T, p, f>:
// 
// fold1 consists of:
// * A parser `p` for values of type `T`.
// * A accumulating function `f`, that transforms
//   two values of type T into a value of type T.
//
// First, `p` is applied. If it fails, fold1 fails. If it succeeds, the result is set
// as the initial accumulated value. Then, `p` is subsequently applied until it fails.
// The produced results are combined with the accumulated value via the accumulating
// function.
// E.g.:
// Considering `f` to be of type `T (T, T)`, let `vₙ` be the values produced
// by subsequent applications of `p` until failure, from 0 to n.
// * If `p` succeeded only once, the result of fold1 is equivalent to `v₀`.
// * If `p` succeeded twice, the result of fold1 is equivalent to `f(v₀, v₁)`.
// * If `p` succeeded three times, the result of fold1 is equivalent to `f(f(v₀, v₁), v₂)`.
// 
// 
// The following signatures are allowed for `f`:
// 
//  returning the result: T (&f)(T, T)
//                      : T (&f)(const T&, const T&)
//                      : T (&f)(T&&, T&&)
//  
//  by passing mutable reference: void (&f)(T&, T)
//                              : void (&f)(T&, T&&)
//                              : void (&f)(T&, T&&)
//  
//  non-const member function: void (T::*f)(T)
//                           : void (T::*f)(const T&)
//                           : void (T::*f)(T&&)

namespace tpc {
  template<
    typename T, parser<T> parse,
    typename U, U val,
    U (&f)(U, T)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    U (&f)(const U&, const T&)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    U (&f)(U&&, T&&)
  >
  inline result<U> fold(stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    void (&f)(U&, T)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    void (&f)(U&, const T&)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    void (&f)(U&, T&&)
  >
  inline result<U> fold(stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    void (U::*f)(T)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    void (U::*f)(const T&)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U val,
    void (U::*f)(T&&)
  >
  inline result<U> fold(stream&);
  
  
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    U (&f)(U, T)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    U (&f)(const U&, const T&)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    U (&f)(U&&, T&&)
  >
  inline result<U> fold(stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    void (&f)(U&, T)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    void (&f)(U&, const T&)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    void (&f)(U&, T&&)
  >
  inline result<U> fold(stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    void (U::*f)(T)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    void (U::*f)(const T&)
  >
  inline result<U> fold(stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&gen)(),
    void (U::*f)(T&&)
  >
  inline result<U> fold(stream&);
  
  
  
  template<
    typename T, parser<T> parse,
    typename U, U (&f)(U, T)
  >
  inline result<U> fold(const U& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&f)(const U&, const T&)
  >
  inline result<U> fold(const U& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&f)(U&&, T&&)
  >
  inline result<U> fold(const U& seed, stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, void (&f)(U&, T)
  >
  inline result<U> fold(const U& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (&f)(U&, const T&)
  >
  inline result<U> fold(const U& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (&f)(U&, T&&)
  >
  inline result<U> fold(const U& seed, stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, void (U::*f)(T)
  >
  inline result<U> fold(const U& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (U::*f)(const T&)
  >
  inline result<U> fold(const U& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (U::*f)(T&&)
  >
  inline result<U> fold(const U& seed, stream&);
  
  
  
  template<
    typename T, parser<T> parse,
    typename U, U (&f)(U, T)
  >
  inline result<U> fold(U&& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&f)(const U&, const T&)
  >
  inline result<U> fold(U&& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, U (&f)(U&&, T&&)
  >
  inline result<U> fold(U&& seed, stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, void (&f)(U&, T)
  >
  inline result<U> fold(U&& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (&f)(U&, const T&)
  >
  inline result<U> fold(U&& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (&f)(U&, T&&)
  >
  inline result<U> fold(U&& seed, stream&);
  
  
  template<
    typename T, parser<T> parse,
    typename U, void (U::*f)(T)
  >
  inline result<U> fold(U&& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (U::*f)(const T&)
  >
  inline result<U> fold(U&& seed, stream&);
  
  template<
    typename T, parser<T> parse,
    typename U, void (U::*f)(T&&)
  >
  inline result<U> fold(U&& seed, stream&);
  
  
  // fold1:
  
  template<
    typename T, parser<T> parse,
    T (&f)(T, T)
  >
  inline result<T> fold1(stream&);
  
  template<
    typename T, parser<T> parse,
    T (&f)(const T&, const T&)
  >
  inline result<T> fold1(stream&);
  
  template<
    typename T, parser<T> parse,
    T (&f)(T&&, T&&)
  >
  inline result<T> fold1(stream&);
  
  
  template<
    typename T, parser<T> parse,
    void (&f)(T&, T)
  >
  inline result<T> fold1(stream&);
  
  template<
    typename T, parser<T> parse,
    void (&f)(T&, const T&)
  >
  inline result<T> fold1(stream&);
  
  template<
    typename T, parser<T> parse,
    void (&f)(T&, T&&)
  >
  inline result<T> fold1(stream&);
  
  
  template<
    typename T, parser<T> parse,
    void (T::*f)(T)
  >
  inline result<T> fold1(stream&);
  
  template<
    typename T, parser<T> parse,
    void (T::*f)(const T&)
  >
  inline result<T> fold1(stream&);
  
  template<
    typename T, parser<T> parse,
    void (T::*f)(T&&)
  >
  inline result<T> fold1(stream&);
}


#include <tpc/parser/combinators/impl/fold.impl>

#endif /* __TPC_PARSER_COMBINATORS_FOLD_HPP__ */
