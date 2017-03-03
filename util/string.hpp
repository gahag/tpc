// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_UTIL_STRING_HPP__
#define __TPC_UTIL_STRING_HPP__

#include <string>
#include <vector>


namespace tpc::Util::String {
  template<const char* str>
  inline std::string to_string() {
    return std::string(str);
  }
}


#endif /* __TPC_UTIL_STRING_HPP__ */
