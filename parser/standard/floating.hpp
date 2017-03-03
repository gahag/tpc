// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_FLOATING_HPP__
#define __TPC_PARSER_STANDARD_FLOATING_HPP__

#include <exception>
#include <string>

#include <tpc/util/traits.hpp>
#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/many.hpp>
#include <tpc/parser/combinators/maybe.hpp>
#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/combinators/reserved.hpp>
#include <tpc/parser/standard/digit.hpp>
#include <tpc/parser/standard/integral.hpp>
#include <tpc/parser/standard/sign.hpp>


namespace tpc {
  using void_t = Util::Functional::void_t;
  
  // Paser::Floating::infinity, Paser::Floating::nan:
  // Standard character representation of floating point infinity and NaN,
  // according to the reference: http://en.cppreference.com/w/cpp/string/basic_string/stof
  namespace Floating {
    constexpr char infinity[] = "INFINITY";
    constexpr char nan[] = "NAN";
  }
  
  
  // skipFractional: Skips a punctuation mark, optionally followed by many digits.
  // The punctuation mark character is determined by the stream's locale.
  constexpr parser<void_t> skipFractional =
    first< void_t, discard<char, numpunct>,
           void_t, ignoreMany< char, digit<char> > >;
  
  // skipExponent: Skips a 'e' character, followed by a optionally signed integral number.
  constexpr parser<void_t> skipExponent =
    first< void_t, discard< char, insensitive<'e'> >,
           void_t, skipIntegral                       >;
  
  // skipInfinity, skipNaN:
  // Skips the correspondent standard character representation
  // of floating point infinity/NaN, case insensitive.
  constexpr parser<void_t> skipInfinity = skipIReserved<Floating::infinity>;
  constexpr parser<void_t> skipNaN      = skipIReserved<Floating::nan>;
  
  // skipFloating: Skips a floating point number, according to the reference:
  // http://en.cppreference.com/w/cpp/string/basic_string/stof
  constexpr parser<void_t> skipFloating =
    first< void_t, skipSign,
           void_t, orP< void_t, first< void_t, skipUIntegral,
                                       void_t, maybe<void_t, skipFractional>,
                                       void_t, maybe<void_t, skipExponent>   >,
                                skipInfinity,
                                skipNaN                                         > >;
  
  
  // ffloating<N, stoN>: Consumes a floating point number, and then feeds the consumed
  // string to the standard parsing function `stoN`.
  // If `stoN` throws, returns failure.
  // Otherwise, returns success containing the parsed value of floating point type `N`.
  // `N` must be a floating point type: float, double or long double.
  // As parsing floating point numbers correctly and efficiently is extremely hard,
  // we capture the number as a string, and then use the stdlib's parsing function.
  template<
    typename N,
    N (&stoN)(const std::string&, std::size_t*),
    typename = Util::Traits::is_floating<N>
  >
  result<N> ffloating(stream&);
  
  
  // floating<N>: Parses a number of the floating point type `N`.
  // The floating point representation is parsed according to the standard reference:
  // http://en.cppreference.com/w/cpp/string/basic_string/stof
  template<
    typename N,
    typename = Util::Traits::is_floating<N>
  >
  constexpr parser<N> floating = undefined<N>;
  
  // Specialization o floating for `float`.
  template<>
  constexpr parser<float> floating<float> = ffloating<float, std::stof>;
  
  // Specialization o floating for `double`.
  template<>
  constexpr parser<double> floating<double> = ffloating<double, std::stod>;
  
  // Specialization o floating for `long double`.
  template<>
  constexpr parser<long double> floating<long double> = ffloating<long double, std::stold>;
}


#include <tpc/parser/standard/impl/floating.impl>

#endif /* __TPC_PARSER_STANDARD_FLOATING_HPP__ */
