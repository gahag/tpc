// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <tpc/util/string.hpp>

#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/combinators/sepby.hpp>
#include <tpc/parser/combinators/sependby.hpp>
#include <tpc/parser/standard/char.hpp>
#include <tpc/parser/standard/identifier.hpp>
#include <tpc/parser/standard/string.hpp>


typedef std::vector<std::string> Line;
typedef std::vector<Line> CSV;


bool isIdent(char c) {
  return std::isprint(c)
      && c != tpc::Char::Comma
      && c != tpc::Char::LineFeed
      && c != tpc::Char::Carriage;
}

constexpr tpc::parser<std::string> cell = tpc::orP<std::string, tpc::string
                                                              , tpc::identifier<isIdent> >;

constexpr tpc::parser<Line> line = tpc::sepBy1<char, tpc::comma, // No empty lines allowed.
                                               Line, cell       >;

constexpr tpc::parser<CSV> csv =
  tpc::first< CSV, tpc::sepEndBy< tpc::void_t, tpc::newline,
                                  CSV,         line          >,
              char, tpc::eos                                    >;


auto main() -> int {
  std::ifstream stream("Examples/test.csv");
  
  auto r = csv(stream);
  
  if (r)
    std::cout << "lines: "      << r->size()        << std::endl
              << "last field: " << r->back().back() << std::endl;
  else
    std::cerr << "Failed at " << tpc::to_string(r.pos) << std::endl;
}
