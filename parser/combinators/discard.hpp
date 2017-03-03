// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_DISCARD_HPP__
#define __TPC_PARSER_COMBINATORS_DISCARD_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/join.hpp>


namespace tpc {
  using Util::Functional::void_t;
  
  // discard<T, parse>: Discard the produced result of a parser.
  // If the parser succeeds, returns success containing no meaningful value.
  // If the parser fails, returns failure
  template<
    typename T, parser<T> parse
  >
  constexpr parser<void_t> discard =
    second< T,      parse,
            void_t, succeed<void_t, Util::Functional::unit> >;
}


#endif /* __TPC_PARSER_COMBINATORS_DISCARD_HPP__ */
