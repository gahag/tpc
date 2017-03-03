// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_SIGN_HPP__
#define __TPC_PARSER_STANDARD_SIGN_HPP__

#include <functional>

#include <tpc/util/functional.hpp>
#include <tpc/util/traits.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/discard.hpp>
#include <tpc/parser/combinators/replace.hpp>
#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/standard/char.hpp>


namespace tpc {
  using void_t = Util::Functional::void_t;
  
  // Sign::fn<N>:
  // The type of a function that applies a signal to a number of the numeric type `N`.
  namespace Sign {
    template<
      typename N,
      typename = Util::Traits::is_numeric<N>
    >
    using fn = N (*)(N);
  }
  
  
  // negative<N>: Parses a minus character.
  // If it succeeds, returns a function that inverts the provided
  // argument of the numeric type `N`.
  // The function prototype is defined by `Sign::fn<N>`.
  template<
    typename N,
    typename = Util::Traits::is_signed<N>
  >
  constexpr parser< Sign::fn<N> > negative =
    replace< char,        minus,
             Sign::fn<N>, Util::Functional::negate<N> >;
  
  // positive<N>: Parses a plus character.
  // If it succeeds, returns an identity function for the numeric type `N`.
  // The function prototype is defined by `Sign::fn<N>`.
  template<
    typename N,
    typename = Util::Traits::is_numeric<N>
  >
  constexpr parser< Sign::fn<N> > positive =
    replace< char,        plus,
             Sign::fn<N>, Util::Functional::id<N> >;
  
  // noSign<N>: Does not consume.
  // If it succeeds, returns an identity function for the numeric type `N`.
  // The function prototype is defined by `Sign::fn<N>`.
  template<
    typename N,
    typename = Util::Traits::is_numeric<N>
  >
  constexpr parser< Sign::fn<N> > noSign = // No signal = positive
    succeed< Sign::fn<N>, Util::Functional::id<N> >;
  
  
  // sign<N>, signed N: Parses a optional sign character.
  // Always succeeds, returning the correspondent signal function for the signed type `N`.
  // The function prototype is defined by `Sign::fn<N>`.
  template<
    typename N,
    Util::Traits::is_signed<N> = true
  >
  inline result< Sign::fn<N> > sign(stream& stream) {
    return orP< Sign::fn<N>, negative<N>
                           , positive<N>
                           , noSign<N>   >(stream);
  }
  
  // sign<N>, unsigned N: Parses a optional positive sign character.
  // Always succeeds, returning a identity function for the unsigned type `N`.
  // The function prototype is defined by `Sign::fn<N>`.
  template<
    typename N,
    Util::Traits::is_unsigned<N> = true
  >
  inline result< Sign::fn<N> > sign(stream& stream) {
    return orP< Sign::fn<N>, positive<N>
                           , noSign<N>   >(stream);
  }
  
  
  // skipSign: Skips a optional signal character. Always succeeds.
  constexpr parser<void_t> skipSign = orP< void_t, discard<char, plus>,
                                                   discard<char, minus>,
                                                   succeed<void_t, Util::Functional::unit> >;
}


#endif /* __TPC_PARSER_STANDARD_SIGN_HPP__ */
