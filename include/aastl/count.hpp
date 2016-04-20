#pragma once

#include <algorithm>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename InputIterator, typename EqualityComparble>
        typename std::iterator_traits<InputIterator>::difference_type
        count(InputIterator first, InputIterator last, const EqualityComparable& value)
        {
            return std::count(first, last, value);
        }

        template <typename InputIterator>
        struct count_n_result {
            InputIterator end;
            typename std::iterator_traits<InputIterator>::difference_type count;
        };

        template <typename InputIterator, typename Size, typename EqualityComparable>
        count_n_result<InputIterator>
        count_n(InputIterator first, Size count, const EqualityComparable& value)
        {
            typename std::iterator_traits<InputIterator>::difference_type result = 0;
            const Size zero = 0;
            while (count > zero) {
                if (*first == value)
                    ++result;
                ++first;
                --count;
            }
            return { first, result };
        }

        template <typename InputIterator, typename EqualityComparable>
        typename std::iterator_traits<InputIterator>::difference_type
        count_not(InputIterator first, InputIterator last, const EqualityComparable &value)
        {
            typename std::iterator_traits<InputIterator>::difference_type result = 0;
            while (first != last) {
                if (!(*first == value))
                    ++result;
                ++first;
            }
            return result;
        }

        template <typename InputIterator, typename Size, typename EqualityComparable>
        count_n_result<InputIterator>
        count_not_n(InputIterator first, Size count, const EqualityComparable &value)
        {
            typename std::iterator_traits<InputIterator>::difference_type result = 0;
            const Size zero = 0;
            while (count > zero) {
                if (!(*first == value))
                    ++result;
                ++first;
                --count;
            }
            return { first, result };
        }

        template <typename InputIterator, typename UnaryPredicate>
        typename std::iterator_traits<InputIterator>::difference_type
        count_if(InputIterator first, InputIterator last, UnaryPredicate p)
        {
            return std::count_if(first, last, p);
        }

        template <typename InputIterator, typename Size, typename UnaryPredicate>
        count_n_result<InputIterator>
        count_if_n(InputIterator first, Size count, UnaryPredicate p)
        {
            typename std::iterator_traits<InputIterator>::difference_type result = 0;
            const Size zero = 0;
            while (count > zero) {
                if (p(*first))
                    ++result;
                ++first;
                --count;
            }
            return { first, result };
        }

        template <typename InputIterator, typename UnaryPredicate>
        typename std::iterator_traits<InputIterator>::difference_type
        count_if_not(InputIterator first, InputIterator last, UnaryPredicate p)
        {
            while (first != last) {
                if (!p(*first))
                    ++result;
                ++first;
            }
            return result;
        }

        template <typename InputIterator, typename Size, typename UnaryPredicate>
        count_n_result<InputIterator>
        count_if_not_n(InputIterator first, Size count, UnaryPredicate p)
        {
            typename std::iterator_traits<InputIterator>::difference_type result = 0;
            const Size zero = 0;
            while (count > zero) {
                if (!p(*first))
                    ++result;
                ++first;
                --count;
            }
            return { first, result };
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl

