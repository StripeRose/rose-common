#pragma once

#include "RoseCommon_Namespace.hpp"

namespace ROSECOMMON_NAMESPACE
{
	/**
	 * @brief Sort a list of vertices in a directed acyclic graph into a linear order.
	 * @tparam RandomIt Type of the random access iterator used to access vertices.
	 * @param aFirst, aLast The pair of iterators defining the range of elements to sort.
	 * @param aHasEdge A callable used to determine if a particular directed edge exist between two vertices.
	 */
	template <typename RandomIt, typename EdgeFunctor>
	void TopologicalSort(RandomIt aFirst, RandomIt aLast, EdgeFunctor aHasEdge)
	{
        // Sourced from: https://cpp.bioweapon.dev/2023/11/03/topological-sort.html

        const std::size_t n = std::ranges::distance(aFirst, aLast);
        std::vector<std::size_t> in_degree(n);

        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                in_degree[i] += bool(aHasEdge(aFirst[j], aFirst[i]));
            }
        }

        // [s_first, s_last) are the sources of the sub-graph [s_first, last)
        auto s_first = aFirst;
        auto s_last = s_first;

        for (std::size_t i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                std::swap(aFirst[i], *s_last);
                std::swap(in_degree[i], in_degree[s_last - aFirst]);
                ++s_last;
            }
        }

        for (; s_first != s_last; ++s_first) {
            for (auto t_it = s_last; t_it != aLast; ++t_it) {
                if (aHasEdge(*s_first, *t_it) && --in_degree[t_it - aFirst] == 0) {
                    std::swap(*t_it, *s_last);
                    std::swap(in_degree[t_it - aFirst], in_degree[s_last - aFirst]);
                    ++s_last;
                }
            }
        }
	}
}
