#pragma once

namespace aastl {

    inline
    namespace v1 {

        template <typename InputIterator, typename T>
        T accumulate(InputIterator first, InputIterator last, T value)
        {
            while (first != last) {
                value += *first; // differs from std::accumulate in use of +=
                ++first;
            }
            return value;
        }

        template <typename InputIterator, typename T, typename Action>
        T accumulate(InputIterator first, InputIterator last, T value, Action action)
        {
            while (first != last) {
                action(value, *first); // differs from std::accumulate in use of action instead of operation
                ++first;
            }
            return value;
        }

        template <typename InputIterator, typename T, typename Predicate>
        T accumulate_if(InputIterator first, InputIterator last, T value, Predicate pred)
        {
            while (first != last) {
                if (pred(*first))
                    value += *first;
                ++first;
            }
            return value;
        }

        template <typename InputIterator, typename T, typename Predicate, typename Action>
        T accumulate_if(InputIterator first, InputIterator last, T value, Predicate pred, Action action)
        {
            while (first != last) {
                if (pred(*first))
                    action(value, *first);
                ++first;
            }
            return value;
        }

        template <typename InputIterator, typename T, typename UnaryOperation>
        T accumulate_xform(InputIterator first, InputIterator last, T value, UnaryOperation op)
        {
            while (first != last) {
                value += op(*first);
                ++first;
            }
            return value;
        }

        // ### useful? the action can always incorporate the UnaryOperation...
        template <typename InputIterator, typename T, typename Action, typename UnaryOperation>
        T accumulate_xform(InputIterator first, InputIterator last, T value, Action action, UnaryOperation op)
        {
            while (first != last) {
                action(value, op(*first));
                ++first;
            }
            return value;
        }

        template <typename InputIterator, typename T, typename Predicate, typename UnaryOperation>
        T accumulate_xform_if(InputIterator first, InputIterator last, T value, Predicate pred, UnaryOperation op)
        {
            while (first != last) {
                if (pred(*first))
                    value += op(*first);
                ++first;
            }
            return value;
        }

        // ### useful? the action can always incorporate the UnaryOperation...
        template <typename InputIterator, typename T, typename Predicate, typename Action, typename UnaryOperation>
        T accumulate_xform_if(InputIterator first, InputIterator last, T value, Predicate pred, Action action, UnaryOperation op)
        {
            while (first != last) {
                if (pred(*first))
                    action(value, op(*first));
                ++first;
            }
            return value;
        }

        template <typename InputIterator, typename Size, typename T>
        T accumulate_n(InputIterator first, Size count, T value)
        {
            const Size zero = 0;
            while (count > zero) {
                value += *first;
                ++first;
                --count;
            }
            return value;
        }

        template <typename InputIterator, typename Size, typename T, typename Action>
        T accumulate_n(InputIterator first, Size count, T value, Action action)
        {
            const Size zero = 0;
            while (count > zero) {
                action(value, *first);
                ++first;
                --count;
            }
            return value;
        }

        template <typename InputIterator, typename Size, typename T, typename Predicate>
        T accumulate_if_n(InputIterator first, Size count, T value, Predicate pred)
        {
            const Size zero = 0;
            while (count > zero) {
                if (pred(*first))
                    value += *first;
                ++first;
                --count;
            }
            return value;
        }

        template <typename InputIterator, typename Size, typename T, typename Predicate, typename Action>
        T accumulate_if_n(InputIterator first, Size count, T value, Predicate pred, Action action)
        {
            const Size zero = 0;
            while (count > zero) {
                if (pred(*first))
                    action(value, *first);
                ++first;
                --count;
            }
            return value;
        }

        template <typename InputIterator, typename Size, typename T, typename UnaryOperation>
        T accumulate_xform_n(InputIterator first, Size count, T value, UnaryOperation op)
        {
            const Size zero = 0;
            while (count > zero) {
                value += op(*first); // differs from std::accumulate in use of +=
                ++first;
                --count;
            }
            return value;
        }

        // ### useful? cf. above
        template <typename InputIterator, typename Size, typename T, typename Action, typename UnaryOperation>
        T accumulate_xform_n(InputIterator first, Size count, T value, Action action, UnaryOperation op)
        {
            const Size zero = 0;
            while (count > zero) {
                action(value, op(*first));
                ++first;
                --count;
            }
            return value;
        }

        template <typename InputIterator, typename Size, typename T, typename Predicate, typename UnaryOperation>
        T accumulate_xform_if_n(InputIterator first, Size count, T value, Predicate pred, UnaryOperation op)
        {
            const Size zero = 0;
            while (count > zero) {
                if (pred(*first))
                    value += op(*first);
                ++first;
                --count;
            }
            return value;
        }

        // ### useful? cf. above
        template <typename InputIterator, typename Size, typename T, typename Predicate, typename Action, typename UnaryOperation>
        T accumulate_xform_if_n(InputIterator first, Size count, T value, Predicate pred, Action action, UnaryOperation op)
        {
            const Size zero = 0;
            while (count > zero) {
                if (pred(*first))
                    action(value, op(*first));
                ++first;
                --count;
            }
            return value;
        }

    }

} // namespace aastl
