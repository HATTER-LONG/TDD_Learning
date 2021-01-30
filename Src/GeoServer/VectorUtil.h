#pragma once

#include <algorithm>
#include <functional>
#include <vector>

template <typename TFrom, typename TTo>
std::vector<TTo> Collect(const std::vector<TFrom>& source, std::function<TTo(TFrom)> func)
{
    std::vector<TTo> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results), func);
    return results;
}
