// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_COMBINATORS_CONSUMPTION_HPP__
#define __TPC_PARSER_COMBINATORS_CONSUMPTION_HPP__

#include <tpc/parser/base.hpp>


namespace tpc {
  // consumption<T, parse>: Returns a string containing the part of the stream
  // that was consumed by the parser.
  // If the parser fails, returns failure.
  // If the parser succeeds without consuming, returns an empty string.
  // If the parser succeeds consuming, returns the consumed text.
  template<
    typename T, parser<T> parse
  >
  result<std::string> consumption(stream& stream);
}


#include <tpc/parser/combinators/impl/consumption.impl>

#endif /* __TPC_PARSER_COMBINATORS_CONSUMPTION_HPP__ */
