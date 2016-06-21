#include <aastl/for_each.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <list>
#include <iterator>

TEST_CASE("for_each_adjacent basics", "[for_each][for_each_adjacent]") {

    std::vector<std::pair<double, double> > output;

    auto input = {0.0, 1.5, 3.0, 4.5};
    auto binary_function = [&output](auto lhs, auto rhs) { output.push_back({lhs, rhs}); };

    SECTION("std::vector") {

        const std::vector<double> v = input;

        SECTION("empty range") {
            const decltype(binary_function) f = aastl::for_each_adjacent(v.begin(), v.begin(), binary_function);
            (void)f;

            REQUIRE(output.empty());
        }

        SECTION("range of just one element") {
            const decltype(binary_function) f = aastl::for_each_adjacent(v.begin(), v.begin() + 1, binary_function);
            (void)f;

            REQUIRE(output.empty());
        }

        SECTION("range of two elements") {
            const decltype(binary_function) f = aastl::for_each_adjacent(v.begin(), v.begin() + 2, binary_function);
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}};

            REQUIRE(output == expected);
        }

        SECTION("general range") {
            const decltype(binary_function) f = aastl::for_each_adjacent(v.begin(), v.end(), binary_function);
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}, {1.5, 3.0}, {3.0, 4.5}};

            REQUIRE(output == expected);
        }

    }

    SECTION("std::list") {

        const std::list<double> l = input;

        SECTION("empty range") {
            const decltype(binary_function) f = aastl::for_each_adjacent(l.begin(), l.begin(), binary_function);
            (void)f;

            REQUIRE(output.empty());
        }

        SECTION("range of just one element") {
            const decltype(binary_function) f = aastl::for_each_adjacent(l.begin(), ++l.begin(), binary_function);
            (void)f;

            REQUIRE(output.empty());
        }

        SECTION("range of two elements") {
            const decltype(binary_function) f = aastl::for_each_adjacent(l.begin(), ++++l.begin(), binary_function);
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}};

            REQUIRE(output == expected);
        }

        SECTION("general range") {
            const decltype(binary_function) f = aastl::for_each_adjacent(l.begin(), l.end(), binary_function);
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}, {1.5, 3.0}, {3.0, 4.5}};

            REQUIRE(output == expected);
        }

    }

}

TEST_CASE("for_each_adjacent_n basics", "[for_each][for_each_adjacent]") {

    std::vector<std::pair<double, double> > output;

    auto input = {0.0, 1.5, 3.0, 4.5};
    auto binary_function = [&output](auto lhs, auto rhs) { output.push_back({lhs, rhs}); };

    SECTION("std::vector") {

        const std::vector<double> v = input;

        SECTION("negative count") {
            const auto result = aastl::for_each_adjacent_n(v.begin(), -1, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == v.begin());
        }

        SECTION("empty range") {
            const auto result = aastl::for_each_adjacent_n(v.begin(), 0U, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == v.begin());
        }

        SECTION("range of just one element") {
            const auto result = aastl::for_each_adjacent_n(v.begin(), 1, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == v.begin() + 1);
        }

        SECTION("range of two elements") {
            const auto result = aastl::for_each_adjacent_n(v.begin(), 2, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}};

            REQUIRE(output == expected);
            REQUIRE(result.end == v.begin() + 2);
        }

        SECTION("general range") {
            const auto result = aastl::for_each_adjacent_n(v.begin(), v.size(), binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}, {1.5, 3.0}, {3.0, 4.5}};

            REQUIRE(output == expected);
            REQUIRE(result.end == v.end());
        }

    }

    SECTION("std::list") {

        const std::list<double> l = input;

        SECTION("empty range") {
            const auto result = aastl::for_each_adjacent_n(l.begin(), 0, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == l.begin());
        }

        SECTION("range of just one element") {
            const auto result = aastl::for_each_adjacent_n(l.begin(), 1, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == ++l.begin());
        }

        SECTION("range of two elements") {
            const auto result = aastl::for_each_adjacent_n(l.begin(), 2, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}};

            REQUIRE(output == expected);
            REQUIRE(result.end == ++++l.begin());
        }

        SECTION("general range") {
            const auto result = aastl::for_each_adjacent_n(l.begin(), l.size(), binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}, {1.5, 3.0}, {3.0, 4.5}};

            REQUIRE(output == expected);
            REQUIRE(result.end == l.end());
        }

    }

}
