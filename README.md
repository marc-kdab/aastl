# Introducing the AAS Algorithm Selection Template Library

The AASTL is a collection of STL-style algorithms. It does not intend
to be a range library, but will likely adopt whatever range concept
Standard C++ comes up with in the future.

## License

The library is distributed under the Boost Licence. Please see the
file `LICENSE.txt` for details.

## Design principles

For now, like in the original STL, counted-range algorithms are
suffixed by `_n` and take an iterator and a count, and bounded-range
algorithms have no suffix and take two iterators.

The focus of this library is to fill holes in the STL (such as missing
`_n` versions), collect useful algorithms, and getting their semantics,
complexity guarantees, and interfaces right (e.g. by always returning
useful information calculated as a by-product).

The library uses C++11, but tries to not do so expansively. Contributions
to compile on C++98 are welcome. C++11 is used pervasively in the tests,
though, and for versioning (see below).

Unlike the original STL, functions returning multiple values don't
return `std::pair`, but a small struct. The intent is to provide better
names than just `first` and `second` for the different return values. Users
of the algorithms are advised to use C++11 `auto` variables to receive the
return values.

## Configuration

The library does not have a configuration subsystem, but relies on proper
values for `__cplusplus` to detect the C++ standard, and P0096 SD10 Feature
Test Macros for individual features. Patches that introduce version number
macros or other compiler-specific detection mechanisms are _not_ welcome :)

## Versioning

For versioning, the library uses inline namespaces. This is
experimental, and how this will eventually be used will probably be
decided only once we'll have a source-incompatible change. If your
compiler does not support inline namespaces, you can define
`AASTL_NO_VERSIONING` prior to including any AASTL header.

The master branch only contains properly-tested and documented algorithms
while the wip branch contains many more algorithms that may be in any state
from "may or may not compile" to "almost done".

Releases will be made from master every five (5) STL algorithm families or
every two (2) non-STL algorithm families finished, whichever comes first.
Version 1.0 will be the first version to contain all STL algorithm families.
The C++17 `ExecutionPolicy` overloads are not in-scope for 1.0.

