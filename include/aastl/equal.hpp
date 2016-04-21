#pragma once

#include <aastl/mismatch.hpp>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename InputIterator1, typename InputIterator2>
        bool
        equal(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2)
        {
            return std::equal(first1, last1, first2);
        }

        template <typename InputIterator1, typename Size, typename InputIterator2>
        bool
        equal_n(InputIterator1 first1, Size count,
                InputIterator2 first2)
        {
            return mismatch_n(first1, count, first2).count_remaining == 0;
        }


        template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
        bool
        equal(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate p)
        {
            return std::equal(first1, last1, first2, p);
        }

        template <typename InputIterator1, typename Size, typename InputIterator2, typename BinaryPredicate>
        bool
        equal_n(InputIterator1 first1, Size count,
                InputIterator2 first2,
                BinaryPredicate p)
        {
            return mismatch_n(first1, count, first2, p).count_remaining == 0;
        }



        template <typename InputIterator1, typename InputIterator2>
        bool
        equal(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2)
        {
#if __cplusplus >= 201402L
            return std::equal(first1, last1, first2, last2);
#else
            const auto result = mismatch(first1, last1, first2, last2);
            return result.first == last1 && result.second == last2;
#endif
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2>
        bool
        equal_n(InputIterator1 first1, Size1 count1,
                InputIterator2 first2, InputIterator2 last2)
        {
            const auto result = mismatch_n(first1, count1, first2, last2);
            return result.count_remaining == 0 && result.second == last2;
        }

        template <typename InputIterator1, typename InputIterator2, typename Size2>
        bool
        equal_n(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, Size2 count2)
        {
            const auto result = mismatch_n(first1, last1, first2, count2);
            return result.count_remaining == 0 && result.first == last1;
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2, typename Size2>
        bool
        equal_n(InputIterator1 first1, Size1 count1,
                InputIterator2 first2, Size2 count2)
        {
            const auto result = mismatch_n(first1, count1, first2, count2);
            return result.first_count_remaining == 0 && result.second_count_remaining == 0;
        }


        template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
        bool
        equal(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2,
              BinaryPredicate p)
        {
#if __cplusplus >= 201402L
            return std::equal(first1, last1, first2, last2, p);
#else
            const auto result = mismatch(first1, last1, first2, last2, p);
            return result.first == last1 && result.second == last2;
#endif
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2, typename BinaryPredicate>
        bool
        equal_n(InputIterator1 first1, Size1 count1,
                InputIterator2 first2, InputIterator2 last2,
                BinaryPredicate p)
        {
            const auto result = mismatch_n(first1, count1, first2, last2, p);
            return result.count_remaining == 0 && result.second == last2;
        }

        template <typename InputIterator1, typename InputIterator2, typename Size2, typename BinaryPredicate>
        bool
        equal_n(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, Size2 count2,
                BinaryPredicate p)
        {
            const auto result = mismatch_n(first1, last1, first2, count2, p);
            return result.first == last1 && result.count_remaining == 0;
        }

        template <typename InputIterator1, typename Size1, typename InputIterator2, typename Size2, typename BinaryPredicate>
        bool
        equal_n(InputIterator1 first1, Size1 count1,
                InputIterator2 first2, Size2 count2,
                BinaryPredicate p)
        {
            const auto result = mismatch_n(first1, count1, first2, count2, p);
            return result.first_count_remaining == 0 && result.second_count_remaining == 0;
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl

