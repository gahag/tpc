// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_SEPENDBY_HPP__
#define __TPC_PARSER_COMBINATORS_SEPENDBY_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/container.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/maybe.hpp>
#include <tpc/parser/combinators/sepby.hpp>


namespace tpc {
  // sepEndBy<T, sep, Container, parse>:
  // Parses zero or more occurrences of `parse`, separated and optionally ended by `sep`,
  // using Container as the storage type. For more information at which types can be used
  // on Container, see the container trait (tpc/container.hpp).
  // `sep` must be of type `parser<T>`
  // `parse` must be of type `parser<Container::value_type>`.
  template<
    typename T, parser<T> sep,
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  constexpr parser<Container> sepEndBy = first< Container, sepBy<T,         sep,
                                                                 Container, parse>,
                                                void_t,    maybe<T, sep>            >;
  
  // sepEndBy1<T, sep, Container, parse>:
  // Parses one or more occurrences of `parse`, separated and optionally ended by `sep`,
  // using Container as the storage type. For more information at which types can be used
  // on Container, see the container trait (tpc/container.hpp).
  // `sep` must be of type `parser<T>`
  // `parse` must be of type `parser<Container::value_type>`.
  template<
    typename T, parser<T> sep,
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  constexpr parser<Container> sepEndBy1 = first< Container, sepBy1<T,         sep,
                                                                   Container, parse>,
                                                 void_t,    maybe<T, sep>             >;
}


#endif /* __TPC_PARSER_COMBINATORS_SEPENDBY_HPP__ */
