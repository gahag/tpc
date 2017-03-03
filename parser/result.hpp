// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_RESULT_HPP__
#define __TPC_PARSER_RESULT_HPP__

// TODO: Change `<experimental/optional>` with `<optional>` when c++17 is available.
#include <experimental/optional>

#include <tpc/util/traits.hpp>

#include <tpc/parser/position.hpp>


namespace tpc {
  // result: The result of a parser. Indicates either failure or success.
  // 
  // The parameter type T cannot be cv-qualified.
  // 
  // On failure: The member `value` is disengaged, and `checkpoint` indicates
  // where the last succeeded parser stopped. If it was not informed about
  // the last parser, 0 is the default.
  // 
  // On success: The member `value` is engaged with the value produced by the
  // parser, and `checkpoint` indicates where the parser stopped.
  //
  // The member `pos` always indicates a (line, column) position, corresponding
  // to where the parser stopped, relatively to where it started. Parser combinators
  // shall sum the positions produced by the parsers in the correct order to obtain
  // a correct position relating to the begin of the stream.
  // 
  template<
    typename T,
    typename = Util::Traits::isnt_cvref<T>
  > class result;
  
  template<typename T>
  class result<T> {
  public:
    std::experimental::optional<T> value; // Potentially parsed value.
    
    position pos; // Position (line, column) where the parser stopped.
    
    std::streampos checkpoint;  // Last stream position where a parser succeeded.
                                // If the parser that generated this result succeeded,
                                // it must be the position where that parser stopped.
    
    
    
    result(const position& = { 1, 1 }, const std::streampos& = 0);           // Failure.
    result(const T&, const position& = { 1, 1 }, const std::streampos& = 0); // Success.
    result(T&&, const position& = { 1, 1 }, const std::streampos& = 0);      // Success.
    
    
    // from(const result<U>&): Sums `pos` from the supplied result, indicating
    // it was the result produced by the previous parser.
    // Also assigns `checkpoint` to max(this, last), to ensure it indicates
    // the stream position of the last succeeded parser.
    template<typename U>
    inline result<T>& from(const result<U>&);
    
    // from(const position&): Sums `pos` from the supplied position, indicating
    // it was the position produced by the previous parser.
    inline result<T>& from(const position&);
    
    // advance: Sums `pos` to the supplied position, indicating it was the position
    // produced by the next parser.
    inline result<T>& advance(const position&);
    
    
    // fail(const position& p = { 1, 1 }, const std::streampos& c = 0):
    // Returns a result indicating failure, relative to the supplied position
    // and checkpoint. Equivalent to `result<T>(p, c)`.
    static inline result<T> fail(const position& p = { 1, 1 }, const std::streampos& c = 0);
    
    // fail(const result<U>& r): Returns a result indicating failure, relative to the
    // supplied result. Equivalent to `result<T>::fail(r.pos, r.checkpoint)`.
    template<typename U> static inline result<T> fail(const result<U>& r);
    
    
    // operator bool() const: Returns wether this result indicates success (true)
    // or failure (false).
    constexpr inline operator bool() const;
    
    // operator->(): Access to the contained value.
    // Precondition: this result indicates success.
    // Use of this operator in a result indicating failure is undefined behavior.
    // const overload: Const access.
    // Equivalent to `&(*value)`.
    constexpr inline const T* operator->() const;
    constexpr inline T* operator->();
    
    // operator*(): Access to the contained value.
    // Precondition: this result indicates success.
    // Use of this operator in a result indicating failure is undefined behavior.
    // const overloads: Const access.
    // && overloads: rvalue access.
    // Equivalent to `*value`.
    constexpr inline const T&  operator*() const &;
    constexpr inline       T&  operator*()       &;
    constexpr inline const T&& operator*() const &&;
    constexpr inline       T&& operator*()       &&;
  };
}


#include <tpc/parser/impl/result.impl>

#endif /* __TPC_PARSER_RESULT_HPP__ */
