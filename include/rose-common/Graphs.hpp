#pragma once

#include "RoseCommon_Namespace.hpp"

#include <optional>
#include <vector>
#include <map>

namespace ROSECOMMON_NAMESPACE
{
	/**
	 * @brief Finds one of the shortest paths in a graph, using Dijkstra's algorithm.
	 * @tparam NodeT Type used for each node in the graph.
	 * @tparam DistanceT Type used for distances between nodes in the graph. Must allow addition and less-than comparisons.
	 * @param aStart The initial node to search from.
	 * @param aDestination The destination node to get the shortest path to.
	 * @param aGetNeighbors Functor to fetch a list of neighbors of a given node. Result should be an iteratable which can be bound into [node, distance].
	 * @param aRouteOut If specified, the shortest path found will be appended to the vector.
	 * @return The distance between the start and destination nodes, or nullopt.
	 */
	template <typename NodeT, typename DistanceT, typename NeighborFunctor>
	std::optional<DistanceT> Pathfind_Dijkstra(NodeT aStart, NodeT aDestination, NeighborFunctor aGetNeighbors, std::vector<NodeT>* aRouteOut = nullptr)
	{
		struct NodeInfo
		{
			std::optional<NodeT> myPreviousNode;
			std::optional<DistanceT> myCost;
			bool myWasVisited = false;
		};

		std::vector<NodeT> nodeQueue;
		std::map<NodeT, NodeInfo> nodeInfo;

		nodeQueue.emplace_back(aStart);
		nodeInfo[aStart].myCost = DistanceT(0);

		while (!nodeQueue.empty())
		{
			NodeT currentNode = nodeQueue[0];
			nodeQueue.erase(nodeQueue.begin());

			if (currentNode == aDestination)
				break;

			NodeInfo& currentNodeInfo = nodeInfo[currentNode];
			if (currentNodeInfo.myWasVisited)
				continue;

			currentNodeInfo.myWasVisited = true;

			for (const auto& [node, distance] : aGetNeighbors(currentNode))
			{
				const DistanceT costToNeighbor = currentNodeInfo.myCost.value() + distance;
				auto neighborInfo = nodeInfo.find(node);
				if (neighborInfo == nodeInfo.end())
				{
					NodeInfo& newInfo = nodeInfo[node];
					newInfo.myCost = costToNeighbor;
					newInfo.myPreviousNode = currentNode;
				}
				else if (!neighborInfo->second.myWasVisited && (!neighborInfo->second.myCost.has_value() || costToNeighbor < neighborInfo->second.myCost.value()))
				{
					neighborInfo->second.myCost = costToNeighbor;
					neighborInfo->second.myPreviousNode = currentNode;
				}

				nodeQueue.push_back(node);
			}
		}

		auto destinationInfo = nodeInfo.find(aDestination);
		const bool foundPath = (destinationInfo != nodeInfo.end());

		if (aRouteOut != nullptr && foundPath)
		{
			NodeT currentNode = aDestination;
			auto currentNodeInfo = nodeInfo.find(currentNode)->second;
			do
			{
				currentNodeInfo = nodeInfo.find(currentNode)->second;
				aRouteOut->push_back(currentNode);
				if (currentNodeInfo.myPreviousNode.has_value())
					currentNode = currentNodeInfo.myPreviousNode.value();
			} while (currentNodeInfo.myPreviousNode.has_value());

			std::reverse(aRouteOut->begin(), aRouteOut->end());
		}

		return foundPath ? destinationInfo->second.myCost : std::optional<DistanceT>();
	}

	/**
	 * @brief Sort a list of vertices in a directed acyclic graph into a linear order.
	 * @tparam RandomIt Type of the random access iterator used to access vertices.
	 * @param aFirst, aLast The pair of iterators defining the range of elements to sort.
	 * @param aHasEdge A callable used to determine if a particular directed edge exist between two vertices.
	 */
	template <typename RandomIt, typename EdgeFunctor>
	void TopologicalSort(RandomIt aFirst, RandomIt aLast, EdgeFunctor aHasEdge)
	{
		// Sourced from: https://biowpn.github.io/bioweapon/2023/11/03/topological-sort.html

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
