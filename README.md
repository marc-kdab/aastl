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

The focus of this library is to collect useful algorithms, and getting
their semantics, complexity guarantees, and interfaces right.

The library uses C++11, but tries to not do so expansively. C++11 is
used pervasively in the tests, though, and for versioning (see below).

Unlike the original STL, functions returning multiple values don't
return std::pair, but a small struct. The intent is to provide better
names than just `first` and `second` for the different return values.

## Versioning

For versioning, the library uses inline namespaces. This is
experimental, and how this will eventually be used will probably be
decided only once we'll have a source-incompatible change. If your
compiler does not support inline namespaces, you can define
`AASTL_NO_VERSIONING` prior to including any AASTL header.

