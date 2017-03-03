// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_LEXEME_HPP__
#define __TPC_PARSER_COMBINATORS_LEXEME_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/maybe.hpp>
#include <tpc/parser/standard/char.hpp>


namespace tpc {
  using Util::Functional::void_t;
  
  // lexeme<T, parse>: Executes the supplied parser, and skips following whitespace.
  // Returns the result produced by the parser.
  // The following characters are considered whitespace:
  // space, horizontal tab, vertical tab, form feed.
  template<
    typename T, parser<T> parse
  >
  constexpr parser<T> lexeme =
    first< T,      parse,
           void_t, maybe<void_t, Util::Functional::unit, whitespace> >;
}


#endif /* __TPC_PARSER_COMBINATORS_LEXEME_HPP__ */
