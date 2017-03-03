// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_STRING_HPP__
#define __TPC_PARSER_STANDARD_STRING_HPP__

#include <string>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/between.hpp>
#include <tpc/parser/standard/char.hpp>


namespace tpc {
  // rawString: Parses a string of characters.
  // Parses characters until EOS or a unescaped double quote is reached.
  // A backslash preceding a backslash or a double quote is considered a escape sequence,
  // and is appended to the result string without the preceding backslash.
  inline result<std::string> rawString(stream&);
  
  // rawString<esc>: Parses a string of characters.
  // Parses characters until EOS or a unescaped double quote is reached.
  // Additionally, a rule for escaping characters is supplied:
  // A backslash preceding a backslash, double quote or a character parsed by `esc`
  // is considered a escape sequence, and is appended to the result string without
  // the preceding backslash.
  template<parser<char> escapable>
  inline result<std::string> rawString(stream&);
  
  
  // string: Parses a string between double quotes.
  // A backslash preceding a backslash or a double quote is considered a escape sequence,
  // and is appended to the result string without the preceding backslash.
  // If EOS is reached, returns failure.
  inline result<std::string> string(stream& stream) {
    return between< char,        doubleQuote,
                    std::string, rawString    >(stream);
  }
  
  // string<esc>: Parses a string between double quotes.
  // Additionally, a rule for escaping characters is supplied:
  // A backslash preceding a backslash, double quote or a character parsed by `esc`
  // is considered a escape sequence, and is appended to the result string without
  // the preceding backslash.
  // If EOS is reached, returns failure.
  template<parser<char> escapable>
  inline result<std::string> string(stream& stream) {
    return between< char,        doubleQuote,
                    std::string, rawString<escapable> >(stream);
  }
}


#include <tpc/parser/standard/impl/string.impl>

#endif /* __TPC_PARSER_STANDARD_STRING_HPP__ */
