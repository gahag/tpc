// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_ENDBY_HPP__
#define __TPC_PARSER_COMBINATORS_ENDBY_HPP__

#include <tpc/parser/base.hpp>
#include <tpc/parser/container.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/lexeme.hpp>
#include <tpc/parser/combinators/many.hpp>
#include <tpc/parser/combinators/or.hpp>


namespace tpc {
  // endBy<T, sep, Container, parse>:
  // Parses zero or more occurrences of `parse`, separated and ended by `sep`, using
  // Container as the storage type. For more information at which types can be used
  // on Container, see the container trait (tpc/container.hpp).
  // `sep` must be of type `parser<T>`
  // `parse` must be of type `parser<Container::value_type>`.
  template<
    typename T, parser<T> sep,
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  constexpr parser<Container> endBy =
    many< Container, first< value_type<Container>, lexeme<value_type<Container>, parse>,
                            T,                     lexeme<T, sep>                        > >;
  
  // endBy1<T, sep, Container, parse>:
  // Parses one or more occurrences of `parse`, separated and ended by `sep`, using
  // Container as the storage type. For more information at which types can be used
  // on Container, see the container trait (tpc/container.hpp).
  // `sep` must be of type `parser<T>`
  // `parse` must be of type `parser<Container::value_type>`.
  template<
    typename T, parser<T> sep,
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  constexpr parser<Container> endBy1 =
    many1< Container, first< value_type<Container>, lexeme<value_type<Container>, parse>,
                             T,                     lexeme<T, sep>                        > >;
}


#endif /* __TPC_PARSER_COMBINATORS_ENDBY_HPP__ */
