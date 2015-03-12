#pragma once

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename OutputIterator, typename Size, typename T>
        OutputIterator iota_n(OutputIterator first, Size count, T value)
        {
            const Size zero = 0;
            while (count > zero) {
                *first = value;
                ++value;
                ++first;
                --count;
            }
            return first;
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
