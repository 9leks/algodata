#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
using Fn = std::function<T()>;

struct Assert {
    Fn<void> beforeEach = [] {};

    Assert(std::string const& title) {
        fmt::print("\n=== {} ===\n", title);
    }

    template <typename T>
    void equals(std::string const& description, Fn<T> const& actual, Fn<T> const& expected) const {
        fmt::print("--- {} ---\n", description);

        beforeEach();
        T lhs = actual();
        beforeEach();
        T rhs = expected();

        if (lhs != rhs) {
            fmt::print("🗿\ttest failed!\nactual:   {}\nexpected: {}\n", lhs, rhs);
            return;
        }

        fmt::print("✅\ttest passed! ({} = {})\n", lhs, rhs);
    }

    void throws(std::string const& description, Fn<void> const& fn) const {
        fmt::print("--- {} ---\n", description);

        beforeEach();
        try {
            fn();
        } catch (const std::exception& e) {
            fmt::print("✅\ttest passed!\n");
            return;
        }

        fmt::print("🗿\ttest failed!\n");
    }

    void exits(std::string const& description, Fn<void> const& fn) const {
        fmt::print("--- {} ---\n", description);
        beforeEach();
        fmt::print("\ttesting for segfault or exception.\n");
        fn();
        fmt::print("✅\ttest passed!\n");
    }

    void raise() {
        throw std::runtime_error("runtime exception raised in testing");
    }
};
