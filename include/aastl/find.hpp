#pragma once

#include <algorithm>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename InputIterator, typename T>
        InputIterator
        find(InputIterator first, InputIterator last, const T& value)
        {
            return std::find(first, last, value);
        }

        template <typename InputIterator, typename Size>
        struct find_n_result {
            InputIterator iterator;
            Size count_remaining;
        };

        template <typename InputIterator, typename Size, typename T>
        find_n_result<InputIterator, Size>
        find_n(InputIterator first, Size count, const T& value)
        {
            const Size zero = 0;
            while (count > zero && !(*first == value)) {
                ++first;
                --count;
            }
            return { first, count };
        }

        template <typename InputIterator, typename T>
        InputIterator
        find_not(InputIterator first, InputIterator last, const T &value)
        {
            while (first != last && *first == value)
                ++first;
            return first;
        }

        template <typename InputIterator, typename Size, typename T>
        find_n_result<InputIterator, Size>
        find_not_n(InputIterator first, Size count, const T &value)
        {
            const Size zero = 0;
            while (count > zero && *first == value) {
                ++first;
                --count;
            }
            return { first, count };
        }

        template <typename InputIterator, typename UnaryPredicate>
        InputIterator
        find_if(InputIterator first, InputIterator last, UnaryPredicate p)
        {
            return std::find_if(first, last, p);
        }

        template <typename InputIterator, typename Size, typename UnaryPredicate>
        find_n_result<InputIterator, Size>
        find_if_n(InputIterator first, Size count, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero && !p(*first)) {
                ++first;
                --count;
            }
            return { first, count };
        }

        template <typename InputIterator, typename UnaryPredicate>
        InputIterator
        find_if_not(InputIterator first, InputIterator last, UnaryPredicate p)
        {
#if __cplusplus >= 201103L
            return std::find_if_not(first, last, p);
#else
            while (first != last && p(*first))
                ++first;
            return first;
#endif
        }

        template <typename InputIterator, typename Size, typename UnaryPredicate>
        find_n_result<InputIterator, Size>
        find_if_not_n(InputIterator first, Size count, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero && p(*first)) {
                ++first;
                --count;
            }
            return { first, count };
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl

