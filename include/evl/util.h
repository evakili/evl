#pragma once

#include <ostream>

namespace evl
{

template<typename I, typename Char>
inline
std::basic_ostream<Char>& join(I first, I last, std::basic_ostream<Char>& os, Char delim) {
    if (first == last) return os;

    os << *first;

    ++first;
    while (first != last) {
        os << delim << *first;
        ++first;
    }
    return os;
}

template<typename I, typename Char>
inline
std::basic_ostream<Char>& join(I first, I last, std::basic_ostream<Char>& os) {
    return join(first, last, os, os.widen(','));
}

}
