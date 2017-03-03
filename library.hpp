// Copyright (C) 2017 gahag
// All rights reserved.
//
// This software may be modified and distributed under the terms
// of the BSD license. See the LICENSE file for details.

#ifndef __TPC_LIBRARY_HPP__
#define __TPC_LIBRARY_HPP__

// Include this file to obtain all of TPC's functionality.

#include <tpc/parser/base.hpp>

// Combinators:
#include <tpc/parser/combinators/between.hpp>
#include <tpc/parser/combinators/bind.hpp>
#include <tpc/parser/combinators/consumption.hpp>
#include <tpc/parser/combinators/discard.hpp>
#include <tpc/parser/combinators/endby.hpp>
#include <tpc/parser/combinators/expect.hpp>
#include <tpc/parser/combinators/fold.hpp>
#include <tpc/parser/combinators/input.hpp>
#include <tpc/parser/combinators/join.hpp>
#include <tpc/parser/combinators/lexeme.hpp>
#include <tpc/parser/combinators/line.hpp>
#include <tpc/parser/combinators/many.hpp>
#include <tpc/parser/combinators/map.hpp>
#include <tpc/parser/combinators/maybe.hpp>
#include <tpc/parser/combinators/not.hpp>
#include <tpc/parser/combinators/or.hpp>
#include <tpc/parser/combinators/parens.hpp>
#include <tpc/parser/combinators/replace.hpp>
#include <tpc/parser/combinators/reserved.hpp>
#include <tpc/parser/combinators/sepby.hpp>
#include <tpc/parser/combinators/sependby.hpp>
#include <tpc/parser/combinators/try.hpp>

// Standard:
#include <tpc/parser/standard/char.hpp>
#include <tpc/parser/standard/consume.hpp>
#include <tpc/parser/standard/digit.hpp>
#include <tpc/parser/standard/floating.hpp>
#include <tpc/parser/standard/identifier.hpp>
#include <tpc/parser/standard/integral.hpp>
#include <tpc/parser/standard/number.hpp>
#include <tpc/parser/standard/sign.hpp>
#include <tpc/parser/standard/string.hpp>

#endif /* __TPC_LIBRARY_HPP__ */
