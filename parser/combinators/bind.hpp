// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_BIND_HPP__
#define __TPC_PARSER_COMBINATORS_BIND_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // bind: Attach a function returning a result to a parser.
  // If the parser succeeds, the result is passed to the function,
  // and the final result produced is returned.
  // If the parser fails, failure is returned.
  // This variant passes the result as const reference.
  template<
    typename From, parser<From> parse,
    typename To,   result<To> (&f)(const From&)
  >
  inline result<To> bind(stream&);
  
  // bind: Variant for passing the result as a rvalue.
  template<
    typename From, parser<From> parse,
    typename To,   result<To> (&f)(From&&)
  >
  inline result<To> bind(stream&);
  
  
  // bind: Similar to bind<From, parse, To, fn>, but attaching two
  // parsers instead. The parsers are executed in order.
  // If the first fails, the second parser is not executed.
  // This variant passes the results as const references.
  template<
    typename From1, parser<From1> parse1,
    typename From2, parser<From2> parse2,
    typename To,    result<To> (&f)(const From1&, const From2&)
  >
  inline result<To> bind(stream&);
  
  // bind: Variant for passing the results as rvalues.
  template<
    typename From1, parser<From1> parse1,
    typename From2, parser<From2> parse2,
    typename To,    result<To> (&f)(From1&&, From2&&)
  >
  inline result<To> bind(stream&);
}


#include <tpc/parser/combinators/impl/bind.impl>

#endif /* __TPC_PARSER_COMBINATORS_BIND_HPP__ */
