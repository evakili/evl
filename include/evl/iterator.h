#pragma once

#include <iterator>
#include <istream>
#include <utility>

namespace evl
{

template<typename T, typename Char, size_t BufLength = 1024>
struct basic_istream_line_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::input_iterator_tag;
    
    constexpr basic_istream_line_iterator() : stream_{ nullptr }, current_{} {}
    basic_istream_line_iterator(std::basic_istream<Char>& stream) : stream_{ &stream } {
        ++*this;
    }

    const T& operator*() const { return current_; }
    const T* const operator->() const { return current_; }

    basic_istream_line_iterator& operator++() {
        char buffer[BufLength];
        if (!stream_->getline(buffer, BufLength))
            stream_ = nullptr;
        else
            current_ = T(buffer);
        return *this;
    }

    friend
    bool operator==(const basic_istream_line_iterator& x, const basic_istream_line_iterator& y) {
        return x.stream_ == y.stream_;
    }
    friend
    bool operator!=(const basic_istream_line_iterator& x, const basic_istream_line_iterator& y) {
        return !(x == y);
    }

    std::basic_istream<Char>* stream_;
    T current_;
};

template<typename T, size_t BufLength = 1024>
using istream_line_iterator = basic_istream_line_iterator<T, char, BufLength>;

template<typename T, size_t BufLength = 1024>
using wistream_line_iterator = basic_istream_line_iterator<T, wchar_t, BufLength>;

}
