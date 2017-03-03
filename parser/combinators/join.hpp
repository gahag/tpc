// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_JOIN_HPP__
#define __TPC_PARSER_COMBINATORS_JOIN_HPP__

#include <tpc/parser/base.hpp>


// The join combinators:
// 
// The join combinators join the results of two or more parsers to produce a single result.
// The parsers are applied in the supplied order.
// If one of the parsers fails to produce a result, then join will immediately fail.
// Overloads are supplied for combining 2 to 7 parsers, passing the results either by
// const reference or rvalue to the combining function.
// 
// Also, combinators for selecting the result of one of the supplied parsers are available.
// Those are the first, second and third combinators.
// For example, `first<T1, p1, T2, p2>` is equivalent to
// `join<T1, p1, T2, p2, [](const T1& r1, const T2& r2) { return r1; }>`.

namespace tpc {
  // join<T1, p1, T2, p2, f>: join the result of two parsers via the supplied function.
  // First, `p1` is executed. If it fails, returns failure.
  // If it succeeds, then `p2` is executed. If it fails, returns failure.
  // If it succeeds, returns success containing the result of `f` applied to the result
  // of `p1` and `p2`, in this respective order.
  // This overload passes the results to the combining function by const reference.
  template< // By const reference.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    
    typename R, R (&f)(const _1&, const _2&)
  >
  result<R> join(stream&);
  
  // join<T1, p1, T2, p2, f>: join the result of two parsers via the supplied function.
  // First, `p1` is executed. If it fails, returns failure.
  // If it succeeds, then `p2` is executed. If it fails, returns failure.
  // If it succeeds, returns success containing the result of `f` applied to the result
  // of `p1` and `p2`, in this respective order.
  // This overload passes the results to the combining function by rvalue.
  template< // By rvalue.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    
    typename R, R (&f)(_1&&, _2&&)
  >
  result<R> join(stream&);
  
  
  // first<T1, p1, T2, p2>: select the result of the first of two parsers.
  // First, `p1` is executed. If it fails, returns failure.
  // If it succeeds, then `p2` is executed. If it fails, returns failure.
  // If it succeeds, returns success containing the result produced by `p1`.
  template<
    typename T, parser<T> parse1,
    typename U, parser<U> parse2
  >
  inline result<T> first(stream&);
  
  // second<T1, p1, T2, p2>: select the result of the second of two parsers.
  // First, `p1` is executed. If it fails, returns failure.
  // If it succeeds, then `p2` is executed. If it fails, returns failure.
  // If it succeeds, returns success containing the result produced by `p2`.
  template<
    typename T, parser<T> parse1,
    typename U, parser<U> parse2
  >
  inline result<U> second(stream&);
  
  // first<T1, p1, T2, p2, T3, p3>: select the result of the first of three parsers.
  // Analogous to first<T1, p1, T2, p2>.
  template<
    typename T, parser<T> parse1,
    typename U, parser<U> parse2,
    typename V, parser<V> parse3
  >
  inline result<T> first(stream&);
  
  // second<T1, p1, T2, p2, T3, p3>: select the result of the second of three parsers.
  // Analogous to second<T1, p1, T2, p2>.
  template<
    typename T, parser<T> parse1,
    typename U, parser<U> parse2,
    typename V, parser<V> parse3
  >
  inline result<U> second(stream&);
  
  // third<T1, p1, T2, p2, T3, p3>: select the result of the third of three parsers.
  // Analogous to first<T1, p1, T2, p2>, but selecting the result of the third parser.
  template<
    typename T, parser<T> parse1,
    typename U, parser<U> parse2,
    typename V, parser<V> parse3
  >
  inline result<V> third(stream&);
  
  
  // The overloads of join: From 3 to 7 parsers, both const reference and rvalue:
  
  // 3 -------------------------------------------
  template< // By const reference.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    
    typename R, R (&f)(const _1&, const _2&, const _3&)
  >
  result<R> join(stream&);
  
  template< // By rvalue.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    
    typename R, R (&f)(_1&&, _2&&, _3&&)
  >
  result<R> join(stream&);
  
  // 4 -------------------------------------------
  template< // By const reference.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    
    typename R, R (&f)(const _1&, const _2&, const _3&, const _4&)
  >
  result<R> join(stream&);
  
  template< // By rvalue.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    
    typename R, R (&f)(_1&&, _2&&, _3&&, _4&&)
  >
  result<R> join(stream&);
  
  // 5 -------------------------------------------
  template< // By const reference.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    typename _5, parser<_5> parse5,
    
    typename R, R (&f)(const _1&, const _2&, const _3&, const _4&, const _5&)
  >
  result<R> join(stream&);
  
  template< // By rvalue.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    typename _5, parser<_5> parse5,
    
    typename R, R (&f)(_1&&, _2&&, _3&&, _4&&, _5&&)
  >
  result<R> join(stream&);
  
  // 6 -------------------------------------------
  template< // By const reference.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    typename _5, parser<_5> parse5,
    typename _6, parser<_6> parse6,
    
    typename R, R (&f)(const _1&, const _2&, const _3&, const _4&, const _5&, const _6&)
  >
  result<R> join(stream&);
  
  template< // By rvalue.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    typename _5, parser<_5> parse5,
    typename _6, parser<_6> parse6,
    
    typename R, R (&f)(_1&&, _2&&, _3&&, _4&&, _5&&, _6&&)
  >
  result<R> join(stream&);
  
  // 7 -------------------------------------------
  template< // By const reference.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    typename _5, parser<_5> parse5,
    typename _6, parser<_6> parse6,
    typename _7, parser<_7> parse7,
    
    typename R, R (&f)(
      const _1&, const _2&, const _3&,
      const _4&, const _5&, const _6&, const _7&
    )
  >
  result<R> join(stream&);
  
  template< // By rvalue.
    typename _1, parser<_1> parse1,
    typename _2, parser<_2> parse2,
    typename _3, parser<_3> parse3,
    typename _4, parser<_4> parse4,
    typename _5, parser<_5> parse5,
    typename _6, parser<_6> parse6,
    typename _7, parser<_7> parse7,
    
    typename R, R (&f)(_1&&, _2&&, _3&&, _4&&, _5&&, _6&&, _7&&)
  >
  result<R> join(stream&);
  // ---------------------------------------------
}


#include <tpc/parser/combinators/impl/join.impl>

#endif /* __TPC_PARSER_COMBINATORS_JOIN_HPP__ */
