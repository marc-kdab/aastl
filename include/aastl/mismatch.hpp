#pragma once

#include <algorithm>
#include <utility>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename Iterator1, typename Iterator2>
        struct mismatch_result {
            Iterator1 first;
            Iterator2 second;

            operator std::pair<Iterator1, Iterator2>() const {
                return std::make_pair(first, second);
            }
        };

        template <typename Iterator1, typename Size, typename Iterator2>
        struct mismatch_n_result {
            Iterator1 first;
            Iterator2 second;
            Size count_remaining;

            operator std::pair<Iterator1, Iterator2>() const {
                return std::make_pair(first, second);
            }
        };

        template <typename Iterator1, typename Iterator2, typename Size1, typename Size2>
        struct mismatch_n2_result {
            Iterator1 first;
            Iterator2 second;
            Size1 first_count_remaining;
            Size2 second_count_remaining;

            operator std::pair<Iterator1, Iterator2>() const {
                return std::make_pair(first, second);
            }
        };

        template <typename InputIterator1, typename InputIterator2>
        mismatch_result<InputIterator1, InputIterator2>
        mismatch(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2)
        {
            std::pair<InputIterator1, InputIterator2> result = std::mismatch(first1, last1, first2);
            return { result.first, result.second };
        }

        template <typename InputIterator1, typename Size, typename InputIterator2>
        mismatch_n_result<InputIterator1, Size, InputIterator2>
        mismatch_n(InputIterator1 first1, Size count,
                   InputIterator2 first2)
        {
            const Size zero = 0;
            while (count > zero && *first1 == *first2) {
                ++first1;
                ++first2;
                --count;
            }
            return { first1, first2, count };
        }


        template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
        mismatch_result<InputIterator1, InputIterator2>
        mismatch(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, BinaryPredicate p)
        {
            std::pair<InputIterator1, InputIterator2> result = std::mismatch(first1, last1, first2, p);
            return { result.first, result.second };
        }

        template <typename InputIterator1, typename Size, typename InputIterator2, typename BinaryPredicate>
        mismatch_n_result<InputIterator1, Size, InputIterator2>
        mismatch_n(InputIterator1 first1, Size count,
                   InputIterator2 first2,
                   BinaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero && p(*first1, *first2)) {
                ++first1;
                ++first2;
                --count;
            }
            return { first1, first2, count };
        }



        template <typename InputIterator1, typename InputIterator2>
        mismatch_result<InputIterator1, InputIterator2>
        mismatch(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, InputIterator2 last2)
        {
#if __cplusplus >= 201402L
            std::pair<InputIterator1, InputIterator2> result = std::mismatch(first1, last1, first2);
            return { result.first, result.second };
#else
            while (first1 != last1 && first2 != last2 && *first1 == *first2) {
                ++first1;
                ++first2;
            }
            return { first1, first2 };
#endif
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2>
        mismatch_n_result<InputIterator1, Size1, InputIterator2>
        mismatch_n(InputIterator1 first1, Size1 count1,
                   InputIterator2 first2, InputIterator2 last2)
        {
            const Size1 zero1 = 0;
            while (count1 > zero1 && first2 != last2 && *first1 == *first2) {
                ++first1;
                ++first2;
                --count1;
            }
            return { first1, first2, count1 };
        }

        template <typename InputIterator1, typename InputIterator2, typename Size2>
        mismatch_n_result<InputIterator1, Size2, InputIterator2>
        mismatch_n(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, Size2 count2)
        {
            const Size2 zero2 = 0;
            while (first1 != last1 && count2 > zero2 && *first1 == *first2) {
                ++first1;
                ++first2;
                --count2;
            }
            return { first1, first2, count2 };
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2, typename Size2>
        mismatch_n2_result<InputIterator1, InputIterator2, Size1, Size2>
        mismatch_n(InputIterator1 first1, Size1 count1,
                   InputIterator2 first2, Size2 count2)
        {
            const Size1 zero1 = 0;
            const Size2 zero2 = 0;
            while (count1 > zero1 && count2 > zero2 && *first1 == *first2) {
                ++first1;
                ++first2;
                --count2;
                --count1;
            }
            return { first1, first2, count1, count2 };
        }


        template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
        mismatch_result<InputIterator1, InputIterator2>
        mismatch(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, InputIterator2 last2,
                 BinaryPredicate p)
        {
#if __cplusplus >= 201402L
            std::pair<InputIterator1, InputIterator2> result = std::mismatch(first1, last1, first2, p);
            return { result.first, result.second };
#else
            while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
                ++first1;
                ++first2;
            }
            return { first1, first2 };
#endif
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2, typename BinaryPredicate>
        mismatch_n_result<InputIterator1, Size1, InputIterator2>
        mismatch_n(InputIterator1 first1, Size1 count1,
                   InputIterator2 first2, InputIterator2 last2,
                   BinaryPredicate p)
        {
            const Size1 zero1 = 0;
            while (count1 > zero1 && first2 != last2 && p(*first1, *first2)) {
                ++first1;
                ++first2;
                --count1;
            }
            return { first1, first2, count1 };
        }

        template <typename InputIterator1, typename InputIterator2, typename Size2, typename BinaryPredicate>
        mismatch_n_result<InputIterator1, Size2, InputIterator2>
        mismatch_n(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, Size2 count2,
                   BinaryPredicate p)
        {
            const Size2 zero2 = 0;
            while (first1 != last1 && count2 > zero2 && p(*first1, *first2)) {
                ++first1;
                ++first2;
                --count2;
            }
            return { first1, first2, count2 };
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2, typename Size2, typename BinaryPredicate>
        mismatch_n2_result<InputIterator1, InputIterator2, Size1, Size2>
        mismatch_n(InputIterator1 first1, Size1 count1,
                   InputIterator2 first2, Size2 count2,
                   BinaryPredicate p)
        {
            const Size1 zero1 = 0;
            const Size2 zero2 = 0;
            while (count1 > zero1 && count2 > zero2 && p(*first1, *first2)) {
                ++first1;
                ++first2;
                --count1;
                --count2;
            }
            return { first1, first2, count1, count2 };
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl

