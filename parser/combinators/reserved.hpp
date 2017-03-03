// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_RESERVED_HPP__
#define __TPC_PARSER_STANDARD_RESERVED_HPP__

#include <tpc/util/char.hpp>
#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>


namespace tpc {
  using void_t = Util::Functional::void_t;
  
  // reserved<kw, cmp>: Parses a string that matches `kw` via the `cmp` function.
  // Reads characters while `cmp(kw[i], c) && kw[i]` evaluates to true.
  // If one character doesn't match, the parser immediately fails.
  // If the end of the string `kw` is reached, the parser succeeds with `std::string(kw)`.
  template<
    const char* keyword,
    bool (&compare)(char, char)
  >
  inline result<std::string> reserved(stream& stream);
  
  // reserved<kw>: Parses a string that matches `kw` character-wise via the `==` operator.
  // Equivalent to `reserved<kw, [](char c1, char c2) { return c1 == c2; }>`.
  template<const char* keyword>
  inline result<std::string> reserved(stream& stream);
  
  // ireserved<kw>: Parses a string that matches `kw` character-wise, case insensitive.
  // Equivalent to
  // `reserved<kw, [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); }>`.
  template<const char* keyword>
  constexpr parser<std::string> ireserved =
    reserved<keyword, Util::Char::equalsInsensitive>;
  
  
  // skipReserved<kw, cmp>: Parses a string that matches `kw` via the `cmp` function.
  // Equivalent to `reserved<kw, cmp>`, except it does not create a std::string object
  // equivalent to the parsed keyword on success.
  template<
    const char* keyword,
    bool (&compare)(char, char)
  >
  result<void_t> skipReserved(stream& stream);
  
  // skipReserved<kw>:
  // Parses a string that matches `kw` character-wise via the `==` operator.
  // Equivalent to `skipReserved<kw>`, except it does not create a std::string object
  // equivalent to the parsed keyword on success.
  template<const char* keyword>
  inline result<void_t> skipReserved(stream& stream);
  
  // skipIReserved<kw>: Parses a string that matches `kw` character-wise, case insensitive.
  // Equivalent to `ireserved<kw>`, except it does not create a std::string object
  // equivalent to the parsed keyword on success.
  template<const char* keyword>
  constexpr parser<void_t> skipIReserved =
    skipReserved<keyword, Util::Char::equalsInsensitive>;
}


#include <tpc/parser/combinators/impl/reserved.impl>

#endif /* __TPC_PARSER_STANDARD_RESERVED_HPP__ */
