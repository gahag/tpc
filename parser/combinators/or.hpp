// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_OR_HPP__
#define __TPC_PARSER_COMBINATORS_OR_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // orP<T, p1, p2>: Disjunction of parsers.
  // Attempts to execute p1. If it succeeds, returns the produced result.
  // If it fails, backtracks and executes p2. If it succeeds, returns the produced result.
  // If it fails, backtracks and returns failure.
  template<
    typename T, parser<T> p1
              , parser<T> p2
  >
  inline result<T> orP(stream&);
  
  // orP<T, p1, p2, p3, ps...>: Disjunction of parsers.
  // Similar to the first, but with more arguments.
  template<
    typename T, parser<T> p1
              , parser<T> p2
              , parser<T> p3
              , parser<T>... ps
  >
  inline result<T> orP(stream&);
}


#include <tpc/parser/combinators/impl/or.impl>

#endif /* __TPC_PARSER_COMBINATORS_OR_HPP__ */
