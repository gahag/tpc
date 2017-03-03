// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_EXPECT_HPP__
#define __TPC_PARSER_COMBINATORS_EXPECT_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // expected<Keyword, kw>: Returns success containing `kw` if the supplied
  // Keyword equals to `kw`, using the == operator. Otherwise, returns failure.
  template<
    typename Keyword, Keyword keyword
  >
  constexpr inline result<Keyword> expected(const Keyword&);
  
  // expected<T, Keyword, kw>: Similar to expected<Keyword, kw>, but performs
  // a static_cast<T> on `kw` before comparing. If the comparison evaluates to
  // true, returns success containing the statically casted value. Otherwise,
  // returns failure.
  template<
    typename T, typename Keyword, Keyword keyword
  >
  constexpr inline result<T> expected(const T&);
  
  
  // expect<Keyword, kw, parse>: Expects a specific value from the parser.
  // If the parser succeeds, containing a value that equals using the == operator
  // to `kw`, returns success containing `kw`.
  // If the values don't match, or the parser fails, returns failure.
  template<
    typename Keyword, Keyword keyword
                    , parser<Keyword> parse
  >
  constexpr inline result<Keyword> expect(stream&);
  
  // expect<Keyword, kw, T, parse>: Similar to expect<Keyword, kw, parse>, but performs
  // a static_cast<T> on `kw` before comparing. If the comparison evaluates to true,
  // returns success containing the statically casted value.
  // If the values don't match, or the parser fails, returns failure.
  template<
    typename Keyword, Keyword keyword,
    typename T, parser<T> parse
  >
  constexpr inline result<T> expect(stream&);
}


#include <tpc/parser/combinators/impl/expect.impl>

#endif /* __TPC_PARSER_COMBINATORS_EXPECT_HPP__ */
