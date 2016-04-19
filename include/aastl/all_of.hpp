#pragma once

#include <aastl/find.hpp>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename InputIterator, typename UnaryPredicate>
        bool all_of(InputIterator first, InputIterator last, UnaryPredicate p)
        {
#if __cplusplus >= 201103L
            return std::all_of(first, last, p);
#else
            return find_if_not(first, last, p) == last;
#endif
        }

        template <typename InputIterator, typename Size, typename UnaryPredicate>
        bool all_of_n(InputIterator first, Size count, UnaryPredicate p)
        {
            return find_if_not_n(first, count, p).count_remaining == 0;
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl

