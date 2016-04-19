#pragma once

namespace aastl {

#ifndef AASTL_NO_VERSIONING
    inline
    namespace v1 {
#endif

        template <typename OutputIterator1, typename OutputIterator2>
        struct separate_if_result {
            OutputIterator1 matched_end;
            OutputIterator2 unmatched_end;
        };

        template <typename InputIterator, typename OutputIterator1,
                  typename OutputIterator2, typename UnaryPredicate>
        separate_if_result<OutputIterator1, OutputIterator2>
        separate_if(InputIterator first, InputIterator last,
                    OutputIterator1 dest1, OutputIterator2 dest2, UnaryPredicate p)
        {
            while (first != last) {
                if (p(*first)) {
                    *dest1 = *first;
                    ++dest1;
                } else {
                    *dest2 = *first;
                    ++dest2;
                }
                ++first;
            }

            return { dest1, dest2 };
        }

        template <typename InputIterator, typename OutputIterator1,
                  typename OutputIterator2, typename UnaryPredicate>
        separate_if_result<OutputIterator1, OutputIterator2>
        separate_if_not(InputIterator first, InputIterator last,
                        OutputIterator1 dest1, OutputIterator2 dest2, UnaryPredicate p)
        {
            typedef separate_if_result<OutputIterator2, OutputIterator1> R;
            R result = separate_if(first, last, dest2, dest1, p);
            return { result.unmatched_end, result.matched_end };
        }

        template <typename InputIterator,
                  typename OutputIterator1, typename OutputIterator2>
        struct separate_if_n_result {
            InputIterator end;
            OutputIterator1 matched_end;
            OutputIterator2 unmatched_end;
        };

        template <typename InputIterator, typename Size,
                  typename OutputIterator1, typename OutputIterator2, typename UnaryPredicate>
        separate_if_n_result<InputIterator, OutputIterator1, OutputIterator2>
        separate_if_n(InputIterator first, Size count,
                      OutputIterator1 dest1, OutputIterator2 dest2, UnaryPredicate p)
        {
            const Size zero = 0;
            while (count > zero) {
                if (p(*first)) {
                    *dest1 = *first;
                    ++dest1;
                } else {
                    *dest2 = *first;
                    ++dest2;
                }
                ++first;
                --count;
            }

            return { first, dest1, dest2 };
        }

        template <typename InputIterator, typename Size,
                  typename OutputIterator1, typename OutputIterator2, typename UnaryPredicate>
        separate_if_n_result<InputIterator, OutputIterator1, OutputIterator2>
        separate_if_not_n(InputIterator first, Size count,
                          OutputIterator1 dest1, OutputIterator2 dest2, UnaryPredicate p)
        {
            typedef separate_if_n_result<InputIterator, OutputIterator2, OutputIterator1> R;
            R result = separate_if_n(first, count, dest2, dest1, p);
            return { result.end, result.unmatched_end, result.matched_end };
        }

#ifndef AASTL_NO_VERSIONING
    }
#endif

} // namespace aastl
