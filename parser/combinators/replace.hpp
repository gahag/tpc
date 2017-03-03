// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_REPLACE_HPP__
#define __TPC_PARSER_COMBINATORS_REPLACE_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/map.hpp>


namespace tpc {
  // replace<T, parse, U, gen>: Replaces the value produced by the supplied parser.
  // Executes the parser. If the succeeds, replaces the result with the value supplied
  // by `gen`, then returns the produced result.
  // If it fails, returns failure.
  template<
    typename From, parser<From> parse,
    typename To,   To (&gen)()
  >
  inline result<To> replace(stream& stream) {
    return map< From, parse,
                To,   Util::Functional::cons<To, From, gen> >(stream);
  }
  
  // replace<T, parse, U, value>: Equivalent to the first, but using an
  // constexpr as the replace value instead of a function.
  template<
    typename From, parser<From> parse,
    typename To,   To value
  >
  inline result<To> replace(stream& stream) {
    return map< From, parse,
                To,   Util::Functional::cons<To, From, value> >(stream);
  }
}


#endif /* __TPC_PARSER_COMBINATORS_REPLACE_HPP__ */
