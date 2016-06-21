#pragma once

#include <algorithm>

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

        template <typename ForwardIterator, typename BinaryFunction>
        BinaryFunction for_each_adjacent(ForwardIterator first, ForwardIterator last, BinaryFunction f)
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

        template <typename ForwardIterator, typename Size, typename BinaryFunction>
        for_each_n_result<ForwardIterator, BinaryFunction>
        for_each_adjacent_n(ForwardIterator first, Size count, BinaryFunction f)
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

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
