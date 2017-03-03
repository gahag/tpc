// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_MAP_HPP__
#define __TPC_PARSER_COMBINATORS_MAP_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // map: Embedds a function into a parser.
  // Executes the parser. If it succeeds, feeds it's result to the
  // function, and returns success containing the produced value.
  // If it fails, returns failure.
  // Overloads are provided for different types of functions.
  
  // By value
  template<
    typename From, parser<From> parse,
    typename To,   To (&f)(From)
  >
  inline result<To> map(stream&);
  
  // By const reference.
  template<
    typename From, parser<From> parse,
    typename To,   To (&f)(const From&)
  >
  inline result<To> map(stream&);
  
  // By rvalue.
  template<
    typename From, parser<From> parse,
    typename To,   To (&f)(From&&)
  >
  inline result<To> map(stream&);
  
  
  // Map using pointer to cv/ref-unqualified member function.
  // The function pointer must point to a valid function.
  template<
    typename From, parser<From> parse,
    typename To,   To (From::*f)()
  >
  inline result<To> map(stream&);
  
  // Map using pointer to rvalue qualified member function.
  // The function pointer must point to a valid function.
  template<
    typename From, parser<From> parse,
    typename To,   To (From::*f)() &&
  >
  inline result<To> map(stream&);
  
  // Map using pointer to const qualified member function.
  // The function pointer must point to a valid function.
  template<
    typename From, parser<From> parse,
    typename To,   To (From::*f)() const
  >
  inline result<To> map(stream&);
}


#include <tpc/parser/combinators/impl/map.impl>

#endif /* __TPC_PARSER_COMBINATORS_MAP_HPP__ */
