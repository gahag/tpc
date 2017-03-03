// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_POSITION_HPP__
#define __TPC_PARSER_POSITION_HPP__

#include <cstddef>
#include <stdexcept>
#include <string>


namespace tpc {
  // posistion: Position in a stream: (line, column).
  // 1-indexed. This means the first position is (1, 1).
  struct position {
    std::size_t line, column;
    
    constexpr position(
      std::size_t ln  = 1,
      std::size_t col = 1
    ) : line(ln), column(col)
    {
      if (ln < 1)
        throw std::invalid_argument("tpc::position - invalid line number");
      
      if (col < 1)
        throw std::invalid_argument("tpc::position - invalid column number");
    }
  };
  
  // operator+: Addition of positions.
  // Addition is not commutative on column:
  // line: line1 + line2 - 1;
  // column: if line2 > 1 then column2
  //                      else column1 + column2 - 1
  // { 1, 1 } is the identity to addition.
  constexpr position operator+(const position& p1, const position& p2) {
    return p2.line > 1 ? position(p1.line + p2.line - 1, p2.column)
                       : position(p1.line, p1.column + p2.column - 1);
  }
  
  // operator+=: Addition of positions.
  // Addition is not commutative.
  constexpr position& operator+=(position& p1, const position& p2) {
    p1 = p1 + p2;
    return p1;
  }
  
  
  // to_string(const position&): String representation of position: "(line, column)".
  inline std::string to_string(const position& pos) {
    return "(" + std::to_string(pos.line) + ", " + std::to_string(pos.column) + ")";
  }
}


#endif /* __TPC_PARSER_POSITION_HPP__ */
