# TPC - Template Parser Combinator #


## Synopsis

TPC is a parser combinator that uses c++ templates to combine and generate parsers at compile time. TPC is inspired by [Parsec](https://github.com/aslatter/parsec).

TPC is still in an early development stage, thus it might have some bugs or missing features. It also might face big changes. Backwards compatibility is not guaranteed.

If you find a bug, or have any kind of suggestion, please report in or send a pull request.


## Usage

TPC is a header only library. It uses some features of the C++ 17 language standard, therefore you will need a compatible compiler to use TPC. In fact, both clang and gcc are currently able to compile TPC without any extra setup. Just add the `tpc` directory to the include path, set `-std=c++1z`, _#include_ the modules you want to use and you're ready to go.

For more detailed information on how to use TPC, see [Basic tutorial](#basic-tutorial) and [Examples](#examples).

For more technical information on compiling with TPC, see [Technical information](#technical-Information).


## Basic tutorial

### The parser type

The type of a parser for a type `T` is `tpc::parser<T>`.
That type is equivalent to the type `tpc::result<T> (&)(tpc::stream&)`.
`T` mustn't be a cv-qualified nor a reference type.

### The result type

The type `tpc::result<T>` represents the result of a parser for a value of type `T`. `T` mustn't be a cv-qualified nor a reference type. 

The result type indicates either failure or success. It contains three relevant members:
* `value`: A `std::optional<T>` that contains the value parsed if the parser succeeded.
* `pos`: The `tpc::position` where the parser stopped.
* `checkpoint`: The `std::streampos` where the last succeeded parser stopped. If the parser that generated the result succeeded, it indicates the position where that parser stopped.

The result type is projected to behave like a `std::optional<T>`. It has `operator bool()`, `operator ->()` and `operator *()`, so the usage is similar to `std::optional<T>`.

Examples on using `tpc::result<T>` can be found at [Inspecting the result](#inspecting-the-result).

More details on members and methods of the `tpc::result<T>` type can be found at its documentation, [result.hpp](parser/result.hpp).

### The stream type

The type `tpc::stream` is a synonym to the type `std::istream`. TPC is compatible with any `std::istream` that supports seeking. Streams like `std::cin` are not yet supported, since they do not allow seeking. Support for this kind of streams is in the list of features to be implemented. Other standard streams like `std::fstream` and `std::stringstream` are supported.

### Declaring a parser

A parser might be declared in two ways, considering it is a reference to a function:
* A function of type `tpc::result<T> (tpc::stream&)`
* A constexpr `tpc::parser<T>` value.

Examples of how to declare a parser can be found at [Declaring a parser](#declaring-a-parser-2).

### Applying a parser

To apply a parser, just do the function call supplying the stream of characters. The resulting value or parse error is the value returned by the function call. Examples of how to use a parser can be found at [Applying a parser](#applying-a-parser-2).

### Modules

TPC is organized into modules. That means one can _#include_ just what is needed, without having to _#include_ the whole library. The parser combinators can be found under `tpc/parser/combinators`. The standard parsers can be found under `tpc/parser/standard`. If for some reason you wish to include everything, just `#include <tpc/library.hpp>`. For more detailed information on modules, see [Modules](#modules).


## Examples

### Declaring a parser

```c++
#include <tpc/parser/combinators/parens.hpp>
#include <tpc/parser/standard/number.hpp>
```

As a function:
```c++
tpc::result<T> a_int_between_parens(tpc::stream& stream) {
  return tpc::parens< int, tpc::number<int> >(stream);
}
```
As a constexpr value:

```c++
constexpr tpc::parser<int> a_int_between_parens = tpc::parens< int, tpc::number<int> >;
```

### Applying a parser

```c++
#include <iostream>
#include <sstream>
#include <string>

std::string str;
std::getline(std::cin, str);      // capture a line from std::cin
std::stringstream my_stream(str); // create a string stream from that line

auto result = a_int_between_parens(my_stream);
```

### Inspecting the result

```c++
if (result) {
  std::cout << "parsed: " << *result << std::endl;
  std::cout << "position: " << tpc::to_string(result.pos) << std::endl;
}
else {
  std::cout << "failed!" << std::endl;
  std::cout << "position: " << tpc::to_string(result.pos) << std::endl;
  std::cout << "unexpected: " << tpc::illformed(result, my_stream) << std::endl;
}
```

### Inspecting the stream

```c++
std::cout << "remained: " << tpc::dump(stream) << std::endl;
```

### Other examples

More elaborate examples can be found under [examples](examples/).
A list of these examples contains:
* A parser for a CSV file
* A parser for chemical formulas
* A parser for basic mathematical expressions in lisp syntax
* A parser for roman numbers


## Modules

TPC is organized into modules. One can _#include_ just what is desired. If for some reason you wish to include everything, just `#include <tpc/library.hpp>`.
Each module is a header file. For the between combinator, the header file is `tpc/parser/combinators/between.hpp`. For the digit parser, the header file is `tpc/parser/standard/digit.hpp`.

### List of modules

Parser combinators, located under `tpc/parser/combinators/`:
* between
* bind
* consumption
* discard
* endby
* expect
* fold
* input
* join
* lexeme
* line
* many
* map
* maybe
* not
* or
* parens
* replace
* reserved
* sepby
* sependby
* try

Standard parsers, found under `tpc/parser/standard/`:
* char
* consume
* digit
* floating
* identifier
* integral
* number
* sign
* string


## Documentation

TPC is documented with comments adjacent to parser definitions and function prototypes. Module specific documentation can be found in the module's header file.


## Technical information

TPC is a header only library, due to the heavy use of templates to combine parsers. TPC uses some of the C++ 17 features, such as using constexpr references as a non-type template parameters, `std::disjunction`, etc. Currently, both gcc 6.3 and clang 3.9 were tested and are able to compile TPC with the flag -std=c++1z. Previous versions supporting c++1z are probably able to compile TPC as well.

TPC requires the `tpc` directory to be in the compiler's include path.

## Contributions

Contributions to TPC are welcome. If you find a bug, or have any kind of suggestion, please report in or send a pull request.

## License

Copyright (C) 2017 gahag
All rights reserved.

This software may be modified and distributed under the terms of the BSD license. See the [LICENSE](LICENSE.txt) file for details.
