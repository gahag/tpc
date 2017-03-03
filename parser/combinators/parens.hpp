// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_PARENS_HPP__
#define __TPC_PARSER_COMBINATORS_PARENS_HPP__

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/between.hpp>
#include <tpc/parser/combinators/lexeme.hpp>
#include <tpc/parser/combinators/input.hpp>
#include <tpc/parser/standard/char.hpp>


namespace tpc {
  // parens: Parses something between parentheses.
  // Parses an opening parenthesis, skips whitespace,
  // executes the supplied parser, skips whitespace,
  // parse a closing parenthesis.
  // If any of the parsers above fails, returns failure.
  // Otherwise, returns the result produced by the supplied parser.
  template<
    typename T, parser<T> parse
  >
  constexpr parser<T> parens = between< char, lexeme<char, openParen>
                                            , input<char, closeParen>,
                                        T,    parse                   >;
}


#endif /* __TPC_PARSER_COMBINATORS_PARENS_HPP__ */
