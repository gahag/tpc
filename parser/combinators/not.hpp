// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_NOT_HPP__
#define __TPC_PARSER_COMBINATORS_NOT_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // notP<T, parse, any>: Executes `any` if tryP<T, parse> fails.
  // if tryP<T, parse> succeeds, returns failure.
  // Otherwise, returns the result produced by executing `any`.
  template<
    typename T, parser<T> parse
              , parser<T> any
  >
  inline result<T> notP(stream&);
}


#include <tpc/parser/combinators/impl/not.impl>

#endif /* __TPC_PARSER_COMBINATORS_NOT_HPP__ */
