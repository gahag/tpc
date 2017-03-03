// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_BETWEEN_HPP__
#define __TPC_PARSER_COMBINATORS_BETWEEN_HPP__

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/join.hpp>


namespace tpc {
  // between<T, open, close, U, parse>: Parsers something between two delimiters.
  // The parsers are executed in the following order: open, parse, close.
  // Fails if `open`, `parse` or `close` fails.
  // Example: Parse a digit between parentheses.
  // between<char, openParen, closeParen
  //         char, digit                 >
  template<
    typename T, parser<T> open
              , parser<T> close,
    
    typename U, parser<U> parse
  >
  inline result<U> between(stream& stream) {
    return second< T, open,
                   U, parse,
                   T, close >(stream);
  }
  
  // between<T, delimiter, U, parse>: Parses something between two delimiters.
  // Equivalent to between<T, delimiter, delimiter, U, parse>.
  template<
    typename T, parser<T> delimiter,
    typename U, parser<U> parse
  >
  inline result<U> between(stream& stream) {
    return between< T, delimiter,
                       delimiter,
                    U, parse      >(stream);
  }
}


#endif /* __TPC_PARSER_COMBINATORS_BETWEEN_HPP__ */
