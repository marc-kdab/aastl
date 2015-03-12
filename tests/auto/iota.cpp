#include <aastl/iota.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <sstream>
#include <vector>
#include <list>
#include <iterator>

TEST_CASE("iota_n basics", "[iota][iota_n]") {

    SECTION("std::vector") {

        std::vector<double> v;

        REQUIRE(v.empty());

        SECTION("n == 0") {
            aastl::iota_n(std::back_inserter(v), 0, 0);

            REQUIRE(v.empty());
        }

        SECTION("n < 0") {
            aastl::iota_n(std::back_inserter(v), -10, 0);

            REQUIRE(v.empty());
        }

        SECTION("n > 0") {
            auto it = aastl::iota_n(std::back_inserter(v), 1, 0);
            it = aastl::iota_n(it, 10, 0);

            const std::vector<double> expected = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            REQUIRE(v == expected);
        }

    }

    SECTION("std::list") {

        std::list<double> l;

        REQUIRE(l.empty());

        SECTION("n == 0") {
            aastl::iota_n(std::back_inserter(l), 0, 0);

            REQUIRE(l.empty());
        }

        SECTION("n < 0") {
            aastl::iota_n(std::back_inserter(l), -10, 0);

            REQUIRE(l.empty());
        }

        SECTION("n > 0") {
            auto it = aastl::iota_n(std::back_inserter(l), 1, 0);
            it = aastl::iota_n(it, 10, 0);

            const std::list<double> expected = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            REQUIRE(l == expected);
        }

    }

    SECTION("std::stringstream") {

        std::stringstream ss;

        REQUIRE(ss.str().empty());

        SECTION("n == 0") {
            aastl::iota_n(std::ostream_iterator<double>(ss, " "), 0, 0);

            REQUIRE(ss.str().empty());
        }

        SECTION("n < 0") {
            aastl::iota_n(std::ostream_iterator<double>(ss, " "), -10, 0);

            REQUIRE(ss.str().empty());
        }

        SECTION("n > 0") {
            auto it = aastl::iota_n(std::ostream_iterator<double>(ss, " "), 1, 0);
            it = aastl::iota_n(it, 10, 0);

            REQUIRE(ss.str() == "0 0 1 2 3 4 5 6 7 8 9 ");
        }

    }
}
