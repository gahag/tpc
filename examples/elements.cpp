// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

#include <tpc/parser/combinators/fold.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/maybe.hpp>
#include <tpc/parser/standard/identifier.hpp>
#include <tpc/parser/standard/number.hpp>


namespace elements {
  namespace util {
    bool islower(char c) { return std::islower(c); }
    bool isupper(char c) { return std::isupper(c); }
    
    float sum(float x, float y) { return x + y; }
  }
  
  
  float weight(const std::string& element, const unsigned& count) {
    if (element == "O")  return 15.9994 * count;
    if (element == "H")  return 1.00794 * count;
    if (element == "Na") return 22.9897 * count;
    if (element == "Cl") return 35.4527 * count;
    if (element == "C")  return 12.0107 * count;
    if (element == "S")  return 32.0655 * count;
    
    return -1;
  }
  
  
  constexpr tpc::parser<std::string> element = tpc::identifier<util::isupper, util::islower>;
  
  constexpr tpc::parser<unsigned> count = tpc::number<unsigned>;
  
  constexpr tpc::parser<float> formula = tpc::fold1<
    float, tpc::join< std::string, element,
                      unsigned,    tpc::maybe<unsigned, 1, count>,
                      float,       weight                           >,
           util::sum
  >;
}


auto main() -> int {
  std::string str;
  
  std::getline(std::cin, str);
  
  std::stringstream stream(str);
  
  
  auto r = elements::formula(stream);
  
  
  if (r)
    std::cout << "result: " << *r << std::endl;
  else
    std::cout << "failed!" << std::endl;
}
