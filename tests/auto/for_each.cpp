#include <aastl/for_each.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <list>
#include <iterator>
#include <sstream>

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

    SECTION("std::stringstream") {

        std::stringstream s;

        auto begin = [&s]() { return std::istream_iterator<double>(s); };
        auto end   = []() { return std::istream_iterator<double>(); };
        auto make  = [&s,input](int n) {
            std::copy_n(input.begin(), n,
                        std::ostream_iterator<decltype(*input.begin())>(s, " "));
            s.seekg(0);
        };
        auto make_all = [=]() {
            make(input.size());
        };

        SECTION("empty range") {
            make(0);

            const decltype(binary_function) f = aastl::for_each_adjacent(begin(), end(), binary_function);
            (void)f;

            REQUIRE(output.empty());
        }

        SECTION("range of just one element") {
            make(1);

            const decltype(binary_function) f = aastl::for_each_adjacent(begin(), end(), binary_function);
            (void)f;

            REQUIRE(output.empty());
        }

        SECTION("range of two elements") {
            make(2);

            const decltype(binary_function) f = aastl::for_each_adjacent(begin(), end(), binary_function);
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}};

            REQUIRE(output == expected);
        }

        SECTION("general range") {
            make_all();

            const decltype(binary_function) f = aastl::for_each_adjacent(begin(), end(), binary_function);
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

    SECTION("std::stringstream") {

        std::stringstream s;

        auto begin = [&s]() { return std::istream_iterator<double>(s); };
        auto end   = []() { return std::istream_iterator<double>(); };
        auto make  = [&s,input](int n) {
            std::copy_n(input.begin(), n,
                        std::ostream_iterator<decltype(*input.begin())>(s, " "));
            s.seekg(0);
        };
        auto make_all = [=]() { make(input.size()); };

        SECTION("negative count") {
            make(0);

            const auto result = aastl::for_each_adjacent_n(begin(), -1, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == begin());
            REQUIRE(result.end == end());
        }

        SECTION("empty range") {
            make(0);

            const auto result = aastl::for_each_adjacent_n(begin(), 0, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == begin());
            REQUIRE(result.end == end());
        }

        SECTION("range of just one element") {
            make(1);

            const auto result = aastl::for_each_adjacent_n(begin(), 1, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            REQUIRE(output.empty());
            REQUIRE(result.end == end());
        }

        SECTION("range of two elements") {
            make(2);

            const auto result = aastl::for_each_adjacent_n(begin(), 2, binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}};

            REQUIRE(output == expected);
            REQUIRE(result.end == end());
        }

        SECTION("general range") {
            make_all();

            const auto result = aastl::for_each_adjacent_n(begin(), input.size(), binary_function);
            const decltype(binary_function) f = result.function;
            (void)f;

            const decltype(output) expected = {{0.0, 1.5}, {1.5, 3.0}, {3.0, 4.5}};

            REQUIRE(output == expected);
            REQUIRE(result.end == end());
        }

    }

}
