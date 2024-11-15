// Copyright Louis Dionne 2013-2022
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/tuple.hpp>

#include <memory>
namespace hana = boost::hana;


// Tuples of smart pointers; based on LLVM bug #18350
int main() {
    {
        hana::tuple<std::unique_ptr<char>> up;
        hana::tuple<std::shared_ptr<char>> sp;
        hana::tuple<std::weak_ptr  <char>> wp;
    }
    {
        hana::tuple<std::unique_ptr<char[]>> up;
        hana::tuple<std::shared_ptr<char[]>> sp;
        hana::tuple<std::weak_ptr  <char[]>> wp;
    }
}
