#include <aastl/separate.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <forward_list>
#include <iterator>

TEST_CASE("separate_if basics", "[separate][separate_if]") {

    auto input = {0.0, 1.5, 3.0, 4.5};
    auto matched = {0.0, 3.0};
    auto unmatched = {1.5, 4.5};

    auto is_integer = [](double x) noexcept { return x == static_cast<long long>(x); };

    SECTION("std::vector") {

        const std::vector<double> v = input;

        SECTION("empty range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if(v.begin(), v.begin(),
                                             std::back_inserter(r1),
                                             std::back_inserter(r2),
                                             is_integer);

            const std::vector<double> x1, x2;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

        SECTION("range of one element") {

            SECTION("matching") {

                std::vector<double> r1, r2;

                auto result = aastl::separate_if(v.begin(), v.begin() + 1,
                                                 std::back_inserter(r1),
                                                 std::back_inserter(r2),
                                                 is_integer);

                const std::vector<double> x1(matched.begin(), matched.begin() + 1), x2;

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }

            SECTION("non-matching") {

                std::vector<double> r1, r2;

                auto result = aastl::separate_if(v.begin() + 1, v.begin() + 2,
                                                 std::back_inserter(r1),
                                                 std::back_inserter(r2),
                                                 is_integer);

                const std::vector<double> x1, x2(unmatched.begin(), unmatched.begin() + 1);

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }
        }

        SECTION("general range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if(v.begin(), v.end(),
                                             std::back_inserter(r1),
                                             std::back_inserter(r2),
                                             is_integer);

            const std::vector<double> x1 = matched, x2 = unmatched;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

    }
    SECTION("std::forward_list") {

        const std::forward_list<double> v = input;

        SECTION("empty range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if(v.begin(), v.begin(),
                                             std::back_inserter(r1),
                                             std::back_inserter(r2),
                                             is_integer);

            const std::vector<double> x1, x2;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

        SECTION("range of one element") {

            SECTION("matching") {

                std::vector<double> r1, r2;

                auto begin = v.begin();
                auto result = aastl::separate_if(v.begin(), ++begin,
                                                 std::back_inserter(r1),
                                                 std::back_inserter(r2),
                                                 is_integer);

                const std::vector<double> x1(matched.begin(), matched.begin() + 1), x2;

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }

            SECTION("non-matching") {

                std::vector<double> r1, r2;

                auto begin = v.begin();
                auto second = ++begin;
                auto third = ++begin;
                auto result = aastl::separate_if(second, third,
                                                 std::back_inserter(r1),
                                                 std::back_inserter(r2),
                                                 is_integer);

                const std::vector<double> x1, x2(unmatched.begin(), unmatched.begin() + 1);

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }
        }

        SECTION("general range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if(v.begin(), v.end(),
                                             std::back_inserter(r1),
                                             std::back_inserter(r2),
                                             is_integer);

            const std::vector<double> x1 = matched, x2 = unmatched;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

    }
}

TEST_CASE("separate_if_n basics", "[separate][separate_if_n]") {

    auto input = {0.0, 1.5, 3.0, 4.5};
    auto const num = input.size();
    auto matched = {0.0, 3.0};
    auto unmatched = {1.5, 4.5};

    auto is_integer = [](double x) noexcept { return x == static_cast<long long>(x); };

    SECTION("std::vector") {

        const std::vector<double> v = input;

        SECTION("empty range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if_n(v.begin(), 0,
                                               std::back_inserter(r1),
                                               std::back_inserter(r2),
                                               is_integer);

            const std::vector<double> x1, x2;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

        SECTION("range of one element") {

            SECTION("matching") {

                std::vector<double> r1, r2;

                auto result = aastl::separate_if_n(v.begin(), 1,
                                                   std::back_inserter(r1),
                                                   std::back_inserter(r2),
                                                   is_integer);

                const std::vector<double> x1(matched.begin(), matched.begin() + 1), x2;

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }

            SECTION("non-matching") {

                std::vector<double> r1, r2;

                auto result = aastl::separate_if_n(v.begin() + 1, 1,
                                                   std::back_inserter(r1),
                                                   std::back_inserter(r2),
                                                   is_integer);

                const std::vector<double> x1, x2(unmatched.begin(), unmatched.begin() + 1);

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }
        }

        SECTION("general range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if_n(v.begin(), v.size(),
                                               std::back_inserter(r1),
                                               std::back_inserter(r2),
                                               is_integer);

            const std::vector<double> x1 = matched, x2 = unmatched;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

    }
    SECTION("std::forward_list") {

        const std::forward_list<double> v = input;

        SECTION("empty range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if_n(v.begin(), 0,
                                               std::back_inserter(r1),
                                               std::back_inserter(r2),
                                               is_integer);

            const std::vector<double> x1, x2;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

        SECTION("range of one element") {

            SECTION("matching") {

                std::vector<double> r1, r2;

                auto result = aastl::separate_if_n(v.begin(), 1,
                                                   std::back_inserter(r1),
                                                   std::back_inserter(r2),
                                                   is_integer);

                const std::vector<double> x1(matched.begin(), matched.begin() + 1), x2;

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }

            SECTION("non-matching") {

                std::vector<double> r1, r2;

                auto begin = v.begin();
                auto second = ++begin;
                auto result = aastl::separate_if_n(second, 1,
                                                   std::back_inserter(r1),
                                                   std::back_inserter(r2),
                                                   is_integer);

                const std::vector<double> x1, x2(unmatched.begin(), unmatched.begin() + 1);

                REQUIRE(r1 == x1);
                REQUIRE(r2 == x2);

                // check returned iterators are functional:
                *result.matched_end = 0.0;
                *result.unmatched_end = 0.5;

                REQUIRE(r1.back() == 0.0);
                REQUIRE(r2.back() == 0.5);
            }
        }

        SECTION("general range") {

            std::vector<double> r1, r2;

            auto result = aastl::separate_if_n(v.begin(), input.size(),
                                               std::back_inserter(r1),
                                               std::back_inserter(r2),
                                               is_integer);

            const std::vector<double> x1 = matched, x2 = unmatched;

            REQUIRE(r1 == x1);
            REQUIRE(r2 == x2);

            // check returned iterators are functional:
            *result.matched_end = 0.0;
            *result.unmatched_end = 0.5;

            REQUIRE(r1.back() == 0.0);
            REQUIRE(r2.back() == 0.5);
        }

    }

}
