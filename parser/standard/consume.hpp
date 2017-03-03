// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_STANDARD_CONSUME_HPP__
#define __TPC_PARSER_STANDARD_CONSUME_HPP__

#include <tpc/util/functional.hpp>

#include <tpc/parser/base.hpp>


namespace tpc {
  using Util::Functional::void_t;
  
  
  // consume<n>: Consumes n characters from the stream. If EOS is reached, returns failure.
  template<std::size_t count>
  inline result<void_t> consume(stream&);
  
  // consume<T, t, n>: Consumes n characters from the stream.
  // If EOS is reached, returns failure. Otherwise, returns success containing `t`.
  template<
    typename T, T value,
    std::size_t count
  >
  inline result<T> consume(stream&);
  
  // consume<T, gen, n>: Consumes n characters from the stream.
  // If EOS is reached, returns failure. Otherwise, returns success containing `gen()`.
  template<
    typename T, T (&generator)(),
    std::size_t count
  >
  inline result<T> consume(stream&);
}


#include <tpc/parser/standard/impl/consume.impl>

#endif /* __TPC_PARSER_STANDARD_CONSUME_HPP__ */
