// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#include <iostream>
#include <sstream>
#include <string>

#include <tpc/parser/combinators/between.hpp>
#include <tpc/parser/combinators/input.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/lexeme.hpp>
#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/combinators/parens.hpp>
#include <tpc/parser/standard/char.hpp>
#include <tpc/parser/standard/number.hpp>


namespace lisp {
  template<typename N>
  N operation(const char& o, const N& i, const N& j) {
    switch (o) {
      case '+': return i + j;
      case '-': return i - j;
      case '*': return i * j;
      case '/': return i / j;
      
      default: return N();
    }
  }
  
  bool is_operator(char c) {
    return c == '+'
        || c == '-'
        || c == '*'
        || c == '/';
  }
  
  
  template<typename N>
  tpc::result<N> parse(tpc::stream& stream) {
    constexpr tpc::parser<char> op = tpc::lexeme< char, tpc::character<is_operator> >;
  
    constexpr tpc::parser<N> expr = tpc::lexeme<
      N, tpc::parens< N, tpc::join< char, op,
                                    N,    parse<N>,
                                    N,    parse<N>,
                                    N,    operation<N> > >
    >;
    
    return tpc::orP< N, tpc::lexeme< N, tpc::number<N> >
                      , expr                            >(stream);
  }
}


auto main() -> int {
  std::string str;
  
  std::getline(std::cin, str);
  
  std::stringstream stream(str);
  
  
  // Try changing `int` to `float` in the following line.
  // Test both options with the expression: (/ (+ 2 3) 2)
  auto r = tpc::input< int, lisp::parse<int> >(stream);
  
  
  if (r)
    std::cout << "result: " << *r << std::endl;
  else
    std::cout << "failed!" << std::endl;
}
