// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_MAYBE_HPP__
#define __TPC_PARSER_COMBINATORS_MAYBE_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/discard.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/combinators/try.hpp>


namespace tpc {
  using Util::Functional::void_t;
  
  // maybe<T, defVal, parse>: Attempts to execute the supplied parser.
  // Maybe always succeeds.
  // If the supplied parser fails, returns success containing the
  // supplied default value, without consuming.
  // Otherwise, returns the produced result.
  // It consumes input only if the parse parameter succeeds parsing.
  // This variant uses a function to supply the default value, useful to
  // supply non constexpr default values.
  template<
    typename T, T (&defVal)()
              , parser<T> parse
  >
  inline result<T> maybe(stream& stream) {
    return orP< T, parse
                 , succeed<T, defVal> >(stream);
  }
  
  // maybe<T, defVal, parse>: Equivalent to the first, but using an
  // constexpr as default value instead of a function.
  template<
    typename T, T defVal
              , parser<T> parse
  >
  inline result<T> maybe(stream& stream) {
    return maybe< T, Util::Functional::cons<T, defVal>
                   , parse                            >(stream);
  }
  
  // maybe<T, parse>: Equivalent to the first, but using the void_t unit as
  // the default value.
  template<
    typename T, parser<T> parse
  >
  inline result<void_t> maybe(stream& stream) {
    return maybe< void_t, Util::Functional::unit
                        , discard<T, parse>     >(stream);
  }
}


#endif /* __TPC_PARSER_COMBINATORS_MAYBE_HPP__ */
