// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_UTIL_CHAR_HPP__
#define __TPC_UTIL_CHAR_HPP__

#include <cctype>

#include <tpc/util/traits.hpp>


namespace tpc::Util::Char {
  constexpr char Carriage    = '\r';
  constexpr char LineFeed    = '\n';
  constexpr char OpenParen   = '(';
  constexpr char CloseParen  = ')';
  constexpr char Quote       = '\'';
  constexpr char DoubleQuote = '"';
  constexpr char Comma       = ',';
  constexpr char Colon       = ':';
  constexpr char SemiColon   = ';';
  constexpr char Minus       = '-';
  constexpr char Plus        = '+';
  constexpr char Slash       = '/';
  constexpr char Backslash   = '\\';
  
  
  constexpr inline bool isDigit(const char c) {
    return c >= '0' && c <= '9';
  }
  
  constexpr inline bool isAlpha(const char c) {
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z');
  }
  
  constexpr inline bool isAlphaNum(const char c) {
    return isAlpha(c)
        || isDigit(c);
  }
  
  constexpr inline bool isSpace(const char c) {
    return (c == ' ')   // Space.
        || (c == '\t')  // Horizontal tab.
        || (c == '\v')  // Vertical tab.
        || (c == '\f'); // Form feed.
  }
  
  
  template<char expected>
  constexpr inline bool is(const char c) {
    return c == expected;
  }
  
  template<char unexpected>
  constexpr inline bool isnt(const char c) {
    return c != unexpected;
  }
  
  template<char expected>
  constexpr inline bool insensitive(const char c) {
    return std::tolower(c) == std::tolower(expected);
  }
  
  
  inline bool equals(const char c1, const char c2) {
    return c1 == c2;
  }
  
  inline bool equalsInsensitive(const char c1, const char c2) {
    return std::tolower(c1) == std::tolower(c2);
  }
  
  
  template<
    typename N,
    typename = Traits::is_numeric<N>
  >
  constexpr inline N parseDigit(const char c) {
    return c - '0';
  }
}


#endif /* __TPC_UTIL_CHAR_HPP__ */
