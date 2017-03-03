// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_DIGIT_HPP__
#define __TPC_PARSER_STANDARD_DIGIT_HPP__

#include <tpc/util/char.hpp>
#include <tpc/util/traits.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/container.hpp>
#include <tpc/parser/combinators/map.hpp>
#include <tpc/parser/combinators/many.hpp>
#include <tpc/parser/standard/char.hpp>


namespace tpc {
  // digit<N>: parse a single digit as a value of the numeric N type.
  // N can be any primitive numeric type, such as float, int or unsigned long long.
  template<
    typename N,
    typename = Util::Traits::is_numeric<N>
  >
  constexpr parser<N> digit = map< char, digitc,
                                      N, Util::Char::parseDigit<N> >;
  
  // digits<Container>:
  // Parse one or more digits, storing Container as the storage type.
  // The Container::value_type must be a numeric type, such as float or unsigned long.
  // For more information at which types can be used on Container, see the
  // container trait (tpc/container.hpp).
  // Example:
  // `digits< std::vector<long double> >` on a stream containing "1234" will produce
  // a vector of long doubles with the values 1.0, 2.0, 3.0 and 4.0.
  template<
    typename Container,
    typename = is_container<Container>,
    typename = Util::Traits::is_numeric< value_type<Container> >
  >
  constexpr parser<Container> digits =
    many1< Container, digit< value_type<Container> > >;
}


#endif /* __TPC_PARSER_STANDARD_DIGIT_HPP__ */
