#pragma once

#include <algorithm>
#include <iterator>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename Iterator, typename Function>
        struct for_each_n_result {
            Iterator end;
            Function function;
        };

        namespace impl {

        template <typename InputIterator, typename BinaryFunction>
        BinaryFunction
        for_each_adjacent(InputIterator first, InputIterator last, BinaryFunction f,
                          std::input_iterator_tag)
        {
            typedef typename std::iterator_traits<InputIterator>::value_type V;
            if (first != last) {
                V prev = *first;
                while (++first != last) {
                    f(prev, *first);
                    prev = *first;
                }
            }
            return f;
        }

        template <typename ForwardIterator, typename BinaryFunction>
        BinaryFunction
        for_each_adjacent(ForwardIterator first, ForwardIterator last, BinaryFunction f,
                          std::forward_iterator_tag)
        {
            if (first != last) {
                ForwardIterator prev = first;
                while (++first != last) {
                    f(*prev, *first);
                    prev = first;
                }
            }
            return f;
        }

        } // impl

        template <typename InputIterator, typename BinaryFunction>
        BinaryFunction
        for_each_adjacent(InputIterator first, InputIterator last, BinaryFunction f)
        {
            return impl::for_each_adjacent(first, last, f, typename std::iterator_traits<InputIterator>::iterator_category());
        }

        namespace impl {

        template <typename InputIterator, typename Size, typename BinaryFunction>
        for_each_n_result<InputIterator, BinaryFunction>
        for_each_adjacent_n(InputIterator first, Size count, BinaryFunction f,
                            std::input_iterator_tag)
        {
            const Size zero = 0;
            typedef typename std::iterator_traits<InputIterator>::value_type V;
            if (count > zero) {
                V prev = *first;
                ++first;
                --count;
                while (count > zero) {
                    f(prev, *first);
                    prev = *first;
                    ++first;
                    --count;
                }
            }
            return { first, f };
        }

        template <typename ForwardIterator, typename Size, typename BinaryFunction>
        for_each_n_result<ForwardIterator, BinaryFunction>
        for_each_adjacent_n(ForwardIterator first, Size count, BinaryFunction f,
                            std::forward_iterator_tag)
        {
            const Size zero = 0;
            if (count > zero) {
                ForwardIterator prev = first;
                ++first;
                --count;
                while (count > zero) {
                    f(*prev, *first);
                    prev = first;
                    ++first;
                    --count;
                }
            }
            return { first, f };
        }

        } // impl

        template <typename InputIterator, typename Size, typename BinaryFunction>
        for_each_n_result<InputIterator, BinaryFunction>
        for_each_adjacent_n(InputIterator first, Size count, BinaryFunction f)
        {
            return impl::for_each_adjacent_n(first, count, f, typename std::iterator_traits<InputIterator>::iterator_category());
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
