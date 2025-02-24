#pragma once

//
// This file is distributed under the MIT License. See LICENSE.md for details.
//

#include <iterator>

#include "revng/Support/Assert.h"

template<typename TypeT, typename Derived, bool Reference = true>
class RandomAccessIterator
  : public std::iterator<std::random_access_iterator_tag, TypeT> {

private:
  using iterator = typename std::iterator<std::random_access_iterator_tag,
                                          TypeT>;
  using type = RandomAccessIterator<TypeT, Derived, Reference>;
  using it_ref = typename iterator::reference;
  template<bool C, typename A, typename B>
  using conditional = std::conditional<C, A, B>;

public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename iterator::value_type;
  using difference_type = typename iterator::difference_type;
  using reference = typename conditional<Reference, it_ref, value_type>::type;
  using pointer = typename iterator::pointer;

private:
  const Derived &constThisDerived() const {
    return *static_cast<const Derived *>(this);
  }

  Derived &thisDerived() { return *static_cast<Derived *>(this); }

  reference get(unsigned Index) const { return constThisDerived().get(Index); }

  Derived clone(unsigned NewIndex) const {
    return Derived(constThisDerived(), NewIndex);
  }

  void assertCompatibility(const type &R) const {
    revng_assert(constThisDerived().isCompatible(R.constThisDerived()));
  }

protected:
  RandomAccessIterator() : Index(0) {}
  RandomAccessIterator(unsigned Index) : Index(Index) {}
  RandomAccessIterator(const type &R) : Index(R.Index) {}

  Derived &operator=(const type &R) {
    assertCompatibility(R);
    Index = R.Index;
    return thisDerived();
  }

public:
  Derived &operator++() {
    ++Index;
    return thisDerived();
  }

  Derived &operator--() {
    --Index;
    return thisDerived();
  }

  Derived operator++(int) { return clone(Index++); }

  Derived operator--(int) { return clone(Index--); }

  Derived operator+(const difference_type &N) const { return clone(Index + N); }

  Derived &operator+=(difference_type N) {
    Index += N;
    return thisDerived();
  }

  Derived operator-(const difference_type &N) const { return clone(Index - N); }

  Derived &operator-=(const difference_type &N) {
    Index -= N;
    return thisDerived();
  }

  reference operator*() const { return get(Index); }

  pointer operator->() const { return &get(Index); }

  reference operator[](const difference_type &N) const {
    return get(Index + N);
  }

  bool operator==(const type &R2) const {
    assertCompatibility(R2);
    return Index == R2.Index;
  }

  bool operator!=(const type &R2) {
    assertCompatibility(R2);
    return Index != R2.Index;
  }

  bool operator<(const type &R2) {
    assertCompatibility(R2);
    return Index < R2.Index;
  }

  bool operator>(const type &R2) {
    assertCompatibility(R2);
    return Index > R2.Index;
  }

  bool operator<=(const type &R2) {
    assertCompatibility(R2);
    return Index <= R2.Index;
  }

  bool operator>=(const type &R2) {
    assertCompatibility(R2);
    return Index >= R2.Index;
  }

  template<typename T, typename D, bool R>
  Derived operator+(const RandomAccessIterator<T, D, R> &R2) {
    assertCompatibility(R2);
    return clone(Index + R2.Index);
  }

  template<typename T, typename D, bool R>
  difference_type operator-(const RandomAccessIterator<T, D, R> &R2) const {
    assertCompatibility(R2);
    return Index - R2.Index;
  }

private:
  unsigned Index;
};
