/*
 * We use this code provides an adaptor to make a const_iterator out of an
 * iterator. Essentially, it's simple wrapper around the iterator that makes
 * operator*() return a const reference instead of a non-const reference.
 *
 * Students do not need to understand this code, and should not modify it.
 *
 * It is implemented using a C++ class template, which is a feature that
 * we will cover later on in the course. It is only designed to be sufficient
 * to work with the IntList class, although a general solution would be
 * very similar.
 */

#ifndef CONST_ADAPTOR_HPP
#define CONST_ADAPTOR_HPP

#include <iterator>

template <typename Iter>
class const_adaptor {
 public:
    // Iterator traits
    //   These definitions are required by the standard library to make
    //   iterators work correctly in generic algorithms.
    using value_type        = typename Iter::value_type;
    using reference         = const value_type&;
    using pointer           = const value_type*;
    using difference_type   = ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const_adaptor() = default;

    const_adaptor(Iter iter) : iter_(iter) {
    }

    const typename Iter::reference operator*() const {
        return *iter_;
    }

    const_adaptor& operator++() {
        ++iter_;
        return *this;
    }

    bool operator==(const const_adaptor& rhs) const {
        return iter_ == rhs.iter_;
    }

    bool operator!=(const const_adaptor& rhs) const {
        return !(*this == rhs);
    }

 private:
    Iter iter_{};  // The iterator we're adapting
};

#endif  // CONST_ADAPTOR_HPP
