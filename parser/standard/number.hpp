// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_NUMBER_HPP__
#define __TPC_PARSER_STANDARD_NUMBER_HPP__

#include <tpc/util/traits.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/standard/integral.hpp>
#include <tpc/parser/standard/floating.hpp>


namespace tpc {
  // number<N>, integral N:
  // Parses a valid base 10 representation of the N integral type.
  // If the representation is out of the range supported by N, returns failure.
  template<
    typename N,
    Util::Traits::is_integral<N> = true
  >
  inline result<N> number(stream& stream) {
    return integral<N>(stream);
  }
  
  // number<N>, floating N:
  // Parses a valid representation of the N floating point type, according to the reference:
  // http://en.cppreference.com/w/cpp/string/basic_string/stof
  // In fact, if stof/stod/stold throws when applied to the consumed floating literal,
  // then number<N> will return failure.
  template<
    typename N,
    Util::Traits::is_floating<N> = true
  >
  inline result<N> number(stream& stream) {
    return floating<N>(stream);
  }
}


#endif /* __TPC_PARSER_STANDARD_NUMBER_HPP__ */
