// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_TRY_HPP__
#define __TPC_PARSER_COMBINATORS_TRY_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // tryP<T, parse>: Attempts to execute the supplied parser. If it fails, backtracks.
  // Executes the parser.
  // If it succeeds, returns the produced result.
  // If it fails, backtracks to where it started, and returns failure.
  template<
    typename T, parser<T> parse
  >
  inline result<T> tryP(stream&);
}


#include <tpc/parser/combinators/impl/try.impl>

#endif /* __TPC_PARSER_COMBINATORS_TRY_HPP__ */
