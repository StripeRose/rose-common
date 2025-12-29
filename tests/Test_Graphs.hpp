#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <rose-common/Graphs.hpp>

#include <map>

namespace
{
	SCENARIO("Pathfinding")
	{
		struct Graph
		{
			std::vector<char> Vertices;
			std::vector<std::tuple<char, char, int>> Edges;
		};

		GIVEN("A node graph")
		{
			// Node graph setup:
			// A - G = 22, only one shortest path
			// A - E = 20, two shortest paths
			// A - X, No valid path

			Graph graph;
			graph.Vertices.emplace_back('A');
			graph.Vertices.emplace_back('B');
			graph.Vertices.emplace_back('C');
			graph.Vertices.emplace_back('D');
			graph.Vertices.emplace_back('E');
			graph.Vertices.emplace_back('F');
			graph.Vertices.emplace_back('G');
			graph.Vertices.emplace_back('X');
			graph.Edges.emplace_back('A', 'B', 7);
			graph.Edges.emplace_back('A', 'C', 9);
			graph.Edges.emplace_back('A', 'F', 14);
			graph.Edges.emplace_back('B', 'C', 10);
			graph.Edges.emplace_back('B', 'D', 10);
			graph.Edges.emplace_back('C', 'D', 11);
			graph.Edges.emplace_back('C', 'F', 2);
			graph.Edges.emplace_back('D', 'E', 3);
			graph.Edges.emplace_back('D', 'G', 5);
			graph.Edges.emplace_back('E', 'F', 9);

			std::vector<char> resultingPath;
			std::string_view resultingPathString;
			auto pathfind = [&](char start, char end) {
				std::optional<int> distance = ROSECOMMON_NAMESPACE::Pathfind_Dijkstra<char, int>(
					start, end,
					[&graph](char node) {
						std::vector<std::pair<char, int>> neighbors;
						for (const auto& [a, b, cost] : graph.Edges)
						{
							if (node == a)
								neighbors.emplace_back(b, cost);
							else if (node == b)
								neighbors.emplace_back(a, cost);
						}
						return neighbors;
					},
					&resultingPath);

				if (distance.has_value())
					resultingPathString = std::string_view(&resultingPath[0], resultingPath.size());

				return distance;
				};

			WHEN("Using Dijkstra's algorithm to find a path between nodes with only one shortest path")
			{
				const std::optional<int> distance = pathfind('A', 'G');

				THEN("The single shortest path is returned")
				{
					CHECK(distance.has_value());
					CHECK(distance.value() == 22);
					CHECK(resultingPathString == "ABDG");
				}
			}

			WHEN("Using Dijkstra's algorithm to find a path between nodes with multiple shortest paths")
			{
				const std::optional<int> distance = pathfind('A', 'E');

				THEN("One of the shortest paths are found(which one is not defined)")
				{
					CHECK(distance.has_value());
					CHECK(distance.value() == 20);
					CHECK((resultingPathString == "ACFE" || resultingPathString == "ABDE"));
				}
			}

			WHEN("Using Dijkstra's algorithm to find a shortest path between unconnected nodes A and X")
			{
				const std::optional<int> distance = pathfind('A', 'X');

				THEN("No valid path is found")
				{
					CHECK(!distance.has_value());
				}
			}
		}
	}

	SCENARIO("Sorting directed acyclic graph")
	{
		struct Graph
		{
			std::vector<char> Vertices;
			std::map<char, char> Edges;
			inline bool HasEdge(char a, char b) { return Edges.contains(a) && Edges.at(a) == b; }

			inline const std::string_view to_string() const { return std::string_view(&Vertices[0], Vertices.size()); }
		};

		GIVEN("An acyclic graph")
		{
			Graph graph;
			graph.Vertices.emplace_back('A');
			graph.Vertices.emplace_back('B');
			graph.Vertices.emplace_back('C');
			graph.Vertices.emplace_back('D');
			graph.Edges.emplace('A', 'B');
			graph.Edges.emplace('A', 'C');
			graph.Edges.emplace('C', 'D');

			WHEN("Sorting topologically")
			{
				ROSECOMMON_NAMESPACE::TopologicalSort(
					graph.Vertices.begin(),
					graph.Vertices.end(),
					[&graph](char a, char b) { return graph.HasEdge(a, b); });

				THEN("Vertices are linearly sorted according to their edges")
				{
					auto result = graph.to_string();
					INFO("Order is: '" << result << "'");
					CHECK((
						result == "ABCD" ||
						result == "ACBD" ||
						result == "ACDB"
					));
				}
			}
		}

		GIVEN("A cyclic graph")
		{
			// Not defined at this time.
		}

		GIVEN("A bi-directional acyclic graph")
		{
			// Not defined at this time.
		}
	}
}