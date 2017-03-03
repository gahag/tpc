// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_PARSER_CONTAINER_HPP__
#define __TPC_PARSER_CONTAINER_HPP__

#include <type_traits>

#include <tpc/util/traits.hpp>


namespace tpc {
  // Introducing the container contract.
  // 
  // A container type is a type that stores the multiple values produced by a parser.
  // For a type to be used as a container, it must satisfy the following constraints:
  // . It must have a constructor with no parameters.
  // . It must be move constructible.
  // . It must have a `value_type` member type, that indicates the type of the elements
  //   stored.
  // . It must have a push_back method, including at least one of the following ovearloads:
  //    void push_back(Container::value_type);
  //    void push_back(const Container::value_type&);
  //    void push_back(Container::value_type&&);
  //
  // Examples of types that can be used as a container are:
  // std::list<float>
  // std::deque<std::string>
  // std::vector<int>
  // std::string
  
  // Alias to allow omitting the typename keyword.
  template<typename Container>
  using value_type = typename Container::value_type;
  
  // Trait for the push_back method.
  namespace Traits {
    template<typename Container>
    struct has_push_back;
  }
  
  // SFINAE to produce an error when the supplied type
  // does not satisfy the container contract.
  template<typename Container>
  using is_container = typename std::enable_if<
                        std::conjunction<
                          std::is_constructible<Container>,
                          std::is_move_constructible<Container>,
                          Traits::has_push_back<Container>
                        >::value,
                        bool
                       >::type;
}


#include <tpc/parser/impl/container.impl>

#endif /* __TPC_PARSER_CONTAINER_HPP__ */
