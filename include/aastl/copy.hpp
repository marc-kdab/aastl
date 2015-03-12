#pragma once

#include <algorithm>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename InputIterator, typename OutputIterator>
        OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
        {
            return std::copy(first, last, dest);
        }


        template <typename InputIterator, typename OutputIterator>
        struct copy_n_result {
            InputIterator input_end;
            OutputIterator output_end;

            // for compatibility with the broken C++11 std::copy_n():
            operator OutputIterator() const { return output_end; }
        };

        template <typename InputIterator, typename Size, typename OutputIterator>
        copy_n_result<InputIterator, OutputIterator>
        copy_n(InputIterator first, Size count, OutputIterator dest)
        {
            const Size zero = 0;
            while (count > zero) {
                *dest = *first;
                ++dest;
                ++first;
                --count;
            }
            return { first, dest };
        }

        template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
        OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator dest, UnaryPredicate p)
        {
#if __cplusplus >= 201103L
            return std::copy_if(first, last, dest, p);
#else
            while (first != last) {
                if (p(*first)) {
                    *dest = *first;
                    ++dest;
                }
                ++first;
            }
            return dest;
#endif
        }

        template <typename InputIterator, typename OutputIterator, typename Size, typename UnaryPredicate>
        copy_n_result<InputIterator, OutputIterator>
        copy_if_n(InputIterator first, Size count, OutputIterator dest, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero) {
                if (p(*first)) {
                    *dest = *first;
                    ++dest;
                }
                ++first;
                --count;
            }
            return { first, dest };
        }

        template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
        OutputIterator copy_if_not(InputIterator first, InputIterator last, OutputIterator dest, UnaryPredicate p)
        {
            while (first != last) {
                if (!p(*first)) {
                    *dest = *first;
                    ++dest;
                }
                ++first;
            }
            return dest;
        }

        template <typename InputIterator, typename OutputIterator, typename Size, typename UnaryPredicate>
        copy_n_result<InputIterator, OutputIterator>
        copy_if_n(InputIterator first, Size count, OutputIterator dest, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero) {
                if (!p(*first)) {
                    *dest = *first;
                    ++dest;
                }
                ++first;
                --count;
            }
            return { first, dest };
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
