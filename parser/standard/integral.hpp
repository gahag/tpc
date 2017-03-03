// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_INTEGRAL_HPP__
#define __TPC_PARSER_STANDARD_INTEGRAL_HPP__

#include <tpc/util/traits.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/standard/digit.hpp>
#include <tpc/parser/standard/sign.hpp>


namespace tpc {
  // integral<N>:
  // Parses a valid base 10 representation of the N integral type.
  // If the representation is out of the range supported by `N`, returns failure.
  template<
    typename N,
    typename = Util::Traits::is_integral<N>
  >
  result<N> integral(stream& stream);
  
  
  // skipIntegral:
  // Skips one or more consecutive digits, optionally preceded by a sign character.
  constexpr parser<void_t> skipIntegral =
    first< void_t, skipSign,
           void_t, ignoreMany1< char, digit<char> > >;
  
  // skipUIntegral:
  // Skips one or more consecutive digits.
  constexpr parser<void_t> skipUIntegral = ignoreMany1< char, digit<char> >;
}


#include <tpc/parser/standard/impl/integral.impl>

#endif /* __TPC_PARSER_STANDARD_INTEGRAL_HPP__ */
