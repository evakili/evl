#pragma once

#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

namespace evl
{

template<typename I>
using range = std::pair<I, I>;

template<typename I>
struct is_empty_range {
    bool operator()(const range<I>& x) const {
        return x.first == x.second;
    }
};

template<typename I, typename Compare>
struct range_compare {
    range_compare(Compare comp) : comp_{ comp } {}
    bool operator()(const range<I>& x, const range<I>& y) const {
        return comp_(*x.first, *y.first);
    }

    Compare comp_;
};

template<typename I, typename O, typename Compare>
O multi_merge(std::vector<range<I>> inputs, O output, Compare comp) {
    inputs.erase(std::remove_if(std::begin(inputs), std::end(inputs), is_empty_range<I>{}),
        std::end(inputs));

    if (inputs.empty())
        return output;
    
    while (inputs.size() != 1) {
        auto min = std::min_element(std::begin(inputs), std::end(inputs), range_compare<I, Compare>{comp});
        if (min->first != min->second) {
            *output = *min->first;
            ++min->first;
            ++output;
        }
        else {
            inputs.erase(min);
        }
    }

    return std::copy(inputs[0].first, inputs[0].second, output);
}

template<typename I, typename O>
O multi_merge(std::vector<range<I>> inputs, O output) {
    return multi_merge(inputs, output, std::less<typename std::iterator_traits<I>::value_type>{});
}

}
