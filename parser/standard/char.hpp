// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_CHAR_HPP__
#define __TPC_PARSER_STANDARD_CHAR_HPP__


#include <tpc/util/char.hpp>
#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/many.hpp>
#include <tpc/parser/combinators/maybe.hpp>
#include <tpc/parser/combinators/not.hpp>
#include <tpc/parser/combinators/or.hpp>


// The standard parsers for characters.

namespace tpc {
  namespace Char = Util::Char;  // Character utilities imported as tpc::Char
  using Util::Functional::void_t;
  
  
  // character<P>: Parses a character that satisfies a predicate.
  template<typename Predicate>
  inline result<char> character(stream&, Predicate);
  
  // character<p>: Parses a character that satisfies a predicate.
  template<bool (&predicate)(char)>
  inline result<char> character(stream&);
  

  // charp: Parses a specific character.
  template<char c>
  constexpr parser<char> charp = character< Char::is<c> >;

  // any: Any character that is not the end of stream token.
  constexpr parser<char> any = character< Char::isnt<EOS> >;
  
  // except<p> Any character, except those that are successfully parsed by `p`.
  template<parser<char> parse>
  constexpr parser<char> except = notP<char, parse, any>;
  
  // insensitive<c>: Parses a specific character, case insensitive.
  template<char expected> // Case insensitive char.
  constexpr parser<char> insensitive = character< Char::insensitive<expected> >;
  
  
  // eos: Parses the end of stream token.
  constexpr parser<char> eos = character< Char::is<EOS> >;
  
  
  // carriage: Parses the carriage return character.
  constexpr parser<char> carriage = character< Char::is<Char::Carriage> >;
  
  // linefeed: Parses the linefeed character.
  constexpr parser<char> linefeed = character< Char::is<Char::LineFeed> >;
  
  // newline: Parses a linefeed character, optionally preceded by a carriage return.
  constexpr parser<void_t> newline = join<void_t, maybe<char, carriage>,
                                          char,   linefeed,
                                          void_t, Util::Functional::ignore>;
  
  
  // openParen: Parses an opening parenthesis character.
  constexpr parser<char> openParen = character< Char::is<Char::OpenParen> >;
  
  // closeParen: Parses a closing parenthesis character.
  constexpr parser<char> closeParen = character< Char::is<Char::CloseParen> >;
  
  
  // quote: Parses a single quote character.
  constexpr parser<char> quote = character< Char::is<Char::Quote> >;
  
  // doubleQuote: Parses a double quote character.
  constexpr parser<char> doubleQuote = character< Char::is<Char::DoubleQuote> >;
  
  
  // comma: Parses a comma character.
  constexpr parser<char> comma = character< Char::is<Char::Comma> >;
  
  // colon: Parses a collon character.
  constexpr parser<char> colon = character< Char::is<Char::Colon> >;
  
  // semicolon: Parses a semicolon character.
  constexpr parser<char> semicolon = character< Char::is<Char::SemiColon> >;
  
  
  // minus: Parses a minus character.
  constexpr parser<char> minus = character< Char::is<Char::Minus> >;
  
  // plus: Parses a plus character.
  constexpr parser<char> plus = character< Char::is<Char::Plus> >;
  
  
  // slash: Parses a slash character.
  constexpr parser<char> slash = character< Char::is<Char::Slash> >;
  
  // backslas: Parses a backslash character.
  constexpr parser<char> backslash = character< Char::is<Char::Backslash> >;
  
  
  // digitc: Parses a digit character. 
  constexpr parser<char> digitc = character<Char::isDigit>;
  
  // alpha: Parses an alphabetic character.
  constexpr parser<char> alpha = character<Char::isAlpha>;
  
  // alphaNum: Parses an alphanumeric character.
  constexpr parser<char> alphaNum = character<Char::isAlphaNum>;
  
  
  // numpunct: Parses a numeric punctuation character.
  // This character is defined by the stream's locale.
  inline result<char> numpunct(stream&);
  
  
  // whitespace: Parses one or more spaces:
  constexpr parser<void_t> whitespace = ignoreMany1< char, character<Char::isSpace> >;
  
  
  // escaped<p>: Parses a backslash, and then attempts to parse another backslash or `p`.
  template<parser<char> escapable>
  constexpr parser<char> escaped = second< char, backslash,
                                           char, orP< char, backslash,
                                                            escapable > >;
}


#include <tpc/parser/standard/impl/char.impl>

#endif /* __TPC_PARSER_STANDARD_CHAR_HPP__ */
