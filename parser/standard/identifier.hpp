// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_IDENTIFIER_HPP__
#define __TPC_PARSER_STANDARD_IDENTIFIER_HPP__

#include <string>

#include <tpc/parser/base.hpp>


namespace tpc {
  // identifier<is, ii>:
  // Parses a identifier, matching the predicates for the first and the other characters.
  template<
    bool (&isIdentStart)(char),
    bool (&isIdentifier)(char)
  >
  inline result<std::string> identifier(stream& stream);
  
  // identifier<ii>: Parses a identifier matching the predicate for allowed characeters.
  template<bool (&isIdentifier)(char)>
  inline result<std::string> identifier(stream& stream);
}


#include <tpc/parser/standard/impl/identifier.impl>

#endif /* __TPC_PARSER_STANDARD_IDENTIFIER_HPP__ */
