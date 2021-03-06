//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads
//  ... assertion fails line 31

// <atomic>

// template <class T>
//     T
//     atomic_load_explicit(const volatile atomic<T>* obj, memory_order m);
// 
// template <class T>
//     T
//     atomic_load_explicit(const atomic<T>* obj, memory_order m);

#include <atomic>
#include <type_traits>
#include <cassert>

#include "powerpc-darwin.h"

template <class T>
void
test()
{
    typedef std::atomic<T> A;
    A t;
    std::atomic_init(&t, T(1));
    assert(std::atomic_load_explicit(&t, std::memory_order_seq_cst) == T(1));
    volatile A vt;
    std::atomic_init(&vt, T(2));
    assert(std::atomic_load_explicit(&vt, std::memory_order_seq_cst) == T(2));
}

struct A
{
    int i;

    explicit A(int d = 0) noexcept {i=d;}

    friend bool operator==(const A& x, const A& y)
        {return x.i == y.i;}
};

int main()
{
    test<A>();
    test<char>();
    test<signed char>();
    test<unsigned char>();
    test<short>();
    test<unsigned short>();
    test<int>();
    test<unsigned int>();
    test<long>();
    test<unsigned long>();
#ifndef	MISSING_64B_ATOMIC_OPS
    test<long long>();
    test<unsigned long long>();
#endif
    test<wchar_t>();
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
    test<char16_t>();
    test<char32_t>();
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
    test<int*>();
    test<const int*>();
}
