#pragma once

#include <memory>    // addressof
#include <iterator>  // iterator_traits

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename ForwardIterator>
        void uninitialized_destroy(ForwardIterator first, ForwardIterator last)
        {
            typedef typename std::iterator_traits<ForwardIterator>::value_type T;

            while (first != last) {
                first->~T(); // or addressof(*first)->~T() ?
                ++first;
            }
        }

        template <typename ForwardIterator, typename Size>
        ForwardIterator uninitialized_destroy_n(ForwardIterator first, Size count)
        {
            typedef typename std::iterator_traits<ForwardIterator>::value_type T;

            const Size zero = 0;
            while (count > zero) {
                first->~T(); // or addressof(*first)->~T() ?
                ++first;
                --count;
            }
            return first;
        }

        template <typename ForwardIterator, typename... Args>
        void uninitialized_inplace_construct(ForwardIterator first, ForwardIterator last, const Args &...args)
        {
            typedef typename std::iterator_traits<ForwardIterator>::value_type T;

            ForwardIterator start = first;
            try {
                while (first != last) {
                    ::new (static_cast<void*>(std::addressof(*first))) T(args...);
                    ++first;
                }
            } catch (...) {
                uninitialized_destroy(start, first);
                throw;
            }
        }

        template <typename ForwardIterator, typename Size, typename... Args>
        ForwardIterator uninitialized_inplace_construct_n(ForwardIterator first, Size count, const Args &... args)
        {
            typedef typename std::iterator_traits<ForwardIterator>::value_type T;

            ForwardIterator start = first;
            try {
                const Size zero = 0;
                while (count > zero) {
                    ::new (static_cast<void*>(std::addressof(*first))) T(args...);
                    ++first;
                    --count;
                }
            } catch (...) {
                uninitialized_destroy(start, first);
                throw;
            }
            return first;
        }

        template <typename ForwardIterator, typename T>
        void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & x)
        {
            return std::uninitialized_fill(first, last, x);
        }

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count, const T & x)
        {
#if __cplusplus >= 201103L
            return std::uninitialized_fill_n(first, count, x);
#else
            return uninitialized_inplace_construct_n(first, count, x);
#endif
        }

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
        {
            return std::uninitialized_copy(first, last, result);
        }

        template <typename InputIterator, typename ForwardIterator>
        struct uninitialized_copy_n_result {
            InputIterator input_end;
            ForwardIterator output_end;

            // for compatibility with the broken C++11 uninitialized_copy_n:
            operator ForwardIterator() const { return output_end; }
        };

        template <typename InputIterator, typename Size, typename ForwardIterator>
        uninitialized_copy_n_result<InputIterator, ForwardIterator>
        uninitialized_copy_n(InputIterator first, Size count, ForwardIterator result)
        {
            typedef typename std::iterator_traits<ForwardIterator>::value_type T;

            ForwardIterator start = result;
            try {
                const Size zero = 0;
                while (count > zero) {
                    ::new (static_cast<void*>(std::addressof(*result))) T(*first);
                    ++first;
                    ++result;
                    --count;
                }
            } catch (...) {
                uninitialized_destroy(start, result);
                throw;
            }

            return { first, result };
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
