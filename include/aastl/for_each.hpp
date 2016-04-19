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

        template <typename InputIterator, typename UnaryFunction>
        UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f)
        {
            // C++98 version is ok:
            return std::for_each(first, last, f);
        }

        template <typename InputIterator, typename Size, typename UnaryFunction>
        for_each_n_result<InputIterator, UnaryFunction>
        for_each_n(InputIterator first, Size count, UnaryFunction f)
        {
            // cannot use the C++17 version, because it fails to return 'f':
            const Size zero = 0;
            while (count > zero) {
                f(*first);
                ++first;
                --count;
            }
            return { first, f };
        }

        template <typename InputIterator, typename UnaryFunction, typename UnaryPredicate>
        UnaryFunction
        for_each_if(InputIterator first, InputIterator last, UnaryFunction f, UnaryPredicate p)
        {
            while (first != last) {
                if (p(*first))
                    f(*first);
                ++first;
            }
            return f;
        }


        template <typename InputIterator, typename Size, typename UnaryFunction, typename UnaryPredicate>
        for_each_n_result<InputIterator, UnaryFunction>
        for_each_if_n(InputIterator first, Size count, UnaryFunction f, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero) {
                if (p(*first))
                    f(*first);
                ++first;
                --count;
            }
            return { first, f };
        }

        template <typename InputIterator, typename UnaryFunction, typename UnaryPredicate>
        UnaryFunction
        for_each_if_not(InputIterator first, InputIterator last, UnaryFunction f, UnaryPredicate p)
        {
            while (first != last) {
                if (!p(*first))
                    f(*first);
                ++first;
            }
            return f;
        }

        template <typename InputIterator, typename Size, typename UnaryFunction, typename UnaryPredicate>
        for_each_n_result<InputIterator, UnaryFunction>
        for_each_if_not_n(InputIterator first, Size count, UnaryFunction f, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero) {
                if (!p(*first))
                    f(*first);
                ++first;
                --count;
            }
            return { first, f };
        }

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
