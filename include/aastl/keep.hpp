#pragma once

#include <aastl/find.hpp>

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename ForwardIterator, typename UnaryPredicate>
        ForwardIterator keep_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
        {
            ForwardIterator write = first = find_if_not(first, last, p);
            if (first != last)
                ++first;
            while (first != last) {
                if (p(*first)) {
#if __cplusplus >= 201103L
                    *write = *first;
#else
                    *write = std::move(*first);
#endif
                    ++write;
                }
                ++first;
            }
            return write;
        }

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator keep(ForwardIterator first, ForwardIterator last, const T& value)
        {
            return keep_if(first, last, std::bind2nd(std::equal_to<T>(), value));
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
