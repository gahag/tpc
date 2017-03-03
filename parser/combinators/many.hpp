// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_MANY_HPP__
#define __TPC_PARSER_COMBINATORS_MANY_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/container.hpp>
#include <tpc/parser/combinators/maybe.hpp>


namespace tpc {
  using Util::Functional::void_t;
  
  // many1<Container, parse>:
  // Parses one or more occurrences of the given parser, using Container as the
  // storage type. For more information at which types can be used on Container,
  // see the container trait (tpc/container.hpp).
  // `parse` must be of type `parser<Container::value_type>`.
  template<
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  inline result<Container> many1(stream&);
  
  // many<Container, parse>(stream&):
  // Parses zero or more occurrences of the given parser, using Container as the
  // storage type. For more information at which types can be used on Container,
  // see the container trait (tpc/container.hpp).
  // `parse` must be of type `parser<Container::value_type>`.
  template<
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  inline result<Container> many(stream&);
  
  // many<Container, parse>(Container&&, stream&):
  // Parses zero or more occurrences of the given parser, using Container as the
  // storage type. For more information at which types can be used on Container,
  // see the container trait (tpc/container.hpp).
  // This overload takes a rvalue Container to use, instead of creating a new empty
  // Container. It appends the parsed values to the supplied container, and then
  // moves it to the result value.
  template<
    typename Container, parser< value_type<Container> > parse,
    typename = is_container<Container>
  >
  inline result<Container> many(Container&&, stream&);
  
  
  // ignoreMany1<T, parse>:
  // Parses one or more occurrences of the given parser, discarding the results.
  // Equivalent to many1, but discarding the results instead of storing them.
  // The type template parameter here is the type of the value parsed by `parse`,
  // instead of a container type as in many1.
  template<
    typename T, parser<T> parse
  >
  inline result<void_t> ignoreMany1(stream&);
  
  // ignoreMany<T, parse>:
  // Parses zero or more occurrences of the given parser, discarding the results.
  // Equivalent to many, but discarding the results instead of storing them.
  // The type template parameter here is the type of the value parsed by `parse`,
  // instead of a container type as in many.
  template<
    typename T, parser<T> parse
  >
  constexpr parser<void_t> ignoreMany = maybe< void_t, ignoreMany1<T, parse> >;
}


#include <tpc/parser/combinators/impl/many.impl>

#endif /* __TPC_PARSER_COMBINATORS_MANY_HPP__ */
