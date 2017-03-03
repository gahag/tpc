// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_LINE_HPP__
#define __TPC_PARSER_COMBINATORS_LINE_HPP__

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/standard/char.hpp>


namespace tpc {
  // line<T, parse>: Executes the supplied parser, followed by a linefeed character.
  // If the linefeed parser fails, returns failure.
  // Otherwise, returns the result produced by the supplied parser.
  template<
    typename T, parser<T> parse
  >
  constexpr parser<T> line = first< T,    parse,
                                    char, linefeed >;
}


#endif /* __TPC_PARSER_COMBINATORS_LINE_HPP__ */
