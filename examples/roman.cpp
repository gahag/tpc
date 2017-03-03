// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#include <iostream>
#include <sstream>
#include <string>

#include <tpc/parser/combinators/fold.hpp>
#include <tpc/parser/combinators/replace.hpp>
#include <tpc/parser/combinators/reserved.hpp>
#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/standard/char.hpp>


namespace roman {
  namespace util {
    int sum(int x, int y) { return x + y; }
  }
  
  const char i[]  = "I",  iv[] = "IV", v[]  = "V",  ix[] = "IX", x[]  = "X"
           , xl[] = "XL", l[]  = "L",  xc[] = "XC", c[]  = "C"
           , cd[] = "CD", d[]  = "D",  cm[] = "CM", m[]  = "M";
  
  
  template<const char* dig, int value>
  constexpr tpc::parser<int> digit = tpc::replace<tpc::void_t, tpc::skipReserved<dig>,
                                                  int,         value                  >;
  
  constexpr tpc::parser<int> one         = digit<i,  1>;
  constexpr tpc::parser<int> four        = digit<iv, 4>;
  constexpr tpc::parser<int> five        = digit<v,  5>;
  constexpr tpc::parser<int> nine        = digit<ix, 9>;
  constexpr tpc::parser<int> ten         = digit<x,  10>;
  constexpr tpc::parser<int> forty       = digit<xl, 40>;
  constexpr tpc::parser<int> fifty       = digit<l,  50>;
  constexpr tpc::parser<int> ninety      = digit<xc, 90>;
  constexpr tpc::parser<int> onehundred  = digit<c,  100>;
  constexpr tpc::parser<int> fourhundred = digit<cd, 400>;
  constexpr tpc::parser<int> fivehundred = digit<d,  500>;
  constexpr tpc::parser<int> ninehundred = digit<cm, 900>;
  constexpr tpc::parser<int> onethousand = digit<m,  1000>;
  
  constexpr tpc::parser<int> unity = tpc::orP<
    int, onethousand, ninehundred, fivehundred, fourhundred, onehundred
       , ninety, fifty, forty, ten, nine, five, four, one
  >;
  
  constexpr tpc::parser<int> numeral = tpc::fold1<int, unity, util::sum>;
}


auto main() -> int {
  std::string str;
  
  std::getline(std::cin, str);
  
  std::stringstream stream(str);
  
  
  auto r = roman::numeral(stream);
  
  
  if (r)
    std::cout << "result: " << *r << std::endl;
  else
    std::cout << "failed!" << std::endl;
}
