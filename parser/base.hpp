// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_BASE_HPP__
#define __TPC_PARSER_BASE_HPP__

#include <istream>
#include <iterator>
#include <string>

#include <tpc/util/traits.hpp>

#include <tpc/parser/result.hpp>


// Basic definition and tools of a parser:
namespace tpc {
  // stream: any istream that supports seeking is supported by TPC.
  // reference @ http://en.cppreference.com/w/cpp/io/basic_istream
  typedef std::istream stream;
  
  // streamIt: iterator for the stream.
  // std::istreambuf_iterator<char> is used because
  // std::istream_iterator skips whitespace.
  typedef std::istreambuf_iterator<char> streamIt;
  
  
  constexpr char EOS = stream::traits_type::eof(); // End of stream token.
  
  
  // dump: Reads the stream until the end.
  inline std::string dump(stream&);
  
  // read: Reads the stream from the streampos parameter,
  // `count` characters.
  inline std::string read(stream&, std::streampos, std::size_t count);
  
  
  // parser<T>: A parser parameterized on T.
  // T cannot be a cv-qualified type.
  // A parser is a function that takes a stream and returns a result<T>,
  // indicating failure or success.
  template<
    typename T,
    typename = Util::Traits::isnt_cvref<T>
  >
  using parser = result<T> (&)(stream&);
  
  // undefined: A parser that fails to link.
  // Used for SFINAE or to only allow specialized versions of parsers.
  template<typename T> result<T> undefined(stream&);
  
  // fail: Parser that always fails.
  // In other words, fail always returns a result<T> indicating failure.
  template<typename T> constexpr inline result<T> fail(stream&);
  
  // succeed: Parser that always succeeds based on a value.
  // In other words, success returns a result<T> indicating success,
  // containing `value`.
  template<typename T, T value> constexpr inline result<T> succeed(stream&);
  
  // succeed: Parser that always succeeds based on a generator.
  // In other words, success returns a result<T> indicating success,
  // containing the result of the calling the function `gen`.
  template<typename T, T (&gen)()> constexpr inline result<T> succeed(stream&);
  
  
  // illformed: Reads the stream between the last point where a parser
  // succeeded (indicated by result parameter), and the last position
  // read in the stream.
  // The result parameter should be a result indicating failure, although
  // no check is made to ensure.
  template<typename T>
  inline std::string illformed(const result<T>&, stream&);
  // Example:
  // 
  // std::stringstream stream("foobar\n"); // Alpha char identifier with 6 chars.
  // 
  // auto r = tpc::expect< std::size_t, 5, // Parses alpha char identifier with 5 chars.
  //                       tpc::map<std::string, tpc::identifier<tpc::Char::isAlpha>,
  //                                std::size_t, &std::string::size                  >
  //                       >(stream);
  // 
  // auto str = tpc::illformed(r, stream); // str == "foobar"
}


#include <tpc/parser/impl/base.impl>

#endif /* __TPC_PARSER_BASE_HPP__ */
