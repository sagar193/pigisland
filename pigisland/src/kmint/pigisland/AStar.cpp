#include "kmint/pigisland/aStar.hpp"
#include <queue>
#include <map>


namespace kmint {
namespace pigisland {
aStar::aStar()
	= default;

aStar::~aStar()
	= default;

std::vector<const kmint::map::map_node*> aStar::FindShortestPath(const kmint::map::map_node &startNode, const kmint::map::map_node &endNode)
{
	std::map<const kmint::map::map_node*, const kmint::map::map_node*> previous;
	std::map<const kmint::map::map_node*, float> cost;
	std::map<const kmint::map::map_node*, float> heuristicCost;

	std::vector<const kmint::map::map_node*> que;
	std::vector<const kmint::map::map_node*> visited;

	if (startNode.node_id() == endNode.node_id())
	{
		visited.push_back(&startNode);
		return visited;
	}

	cost[&startNode] = 0;
	heuristicCost[&startNode] = calculateDistance(startNode, endNode);
	que.push_back(&startNode);

	bool found = false;
	//
	while (que.size() > 0 && !found) {
		int it = 0;
		const kmint::map::map_node * smallestVertex = nullptr;
		for (int i = 0; i < que.size(); i++) {
			if (smallestVertex == nullptr || cost[que[i]] + heuristicCost[que[i]] < cost[smallestVertex] + heuristicCost[smallestVertex]) {
				smallestVertex = que[i];
				it = i;
			}
		}

		for (std::size_t i = 0; i < smallestVertex->num_edges(); ++i) {
			auto edge = (*smallestVertex)[i];
			auto toVertex = &edge.to();
			bool notInVisited = std::find(visited.begin(), visited.end(), toVertex) == visited.end();
			bool notInQue = std::find(que.begin(), que.end(), toVertex) == que.end();
			
			if (notInVisited && notInQue) {
				que.push_back(toVertex);
			}
			if (cost.find(toVertex) == cost.end() || cost[toVertex] > cost[smallestVertex] + edge.weight()) {
				cost[toVertex] = cost[smallestVertex] + edge.weight();
				heuristicCost[toVertex] = calculateDistance(*smallestVertex, endNode);
				previous[toVertex] = smallestVertex;
			}
			if (toVertex == &endNode) {
				cost[toVertex] = cost[smallestVertex] + edge.weight();
				heuristicCost[toVertex] = calculateDistance(*smallestVertex, endNode);
				previous[toVertex] = smallestVertex;
				found = true;
				break;
			}

		}
		que.erase(que.begin() + it);
		visited.push_back(smallestVertex);
	}

	auto lastNode = previous[&endNode];
	std::vector<const kmint::map::map_node*> path;
	while (lastNode != &startNode) {
		path.insert(path.begin(), lastNode);
		lastNode = previous[lastNode];
	}
	path.push_back(&endNode);

	///voor het testen welke nodes allemaal gevisited zijn, path veranderen naar visited
	return path;

}

float aStar::calculateDistance(const kmint::map::map_node &firstNode, const kmint::map::map_node &secondNode) {
	float distance = sqrt(pow(firstNode.location().x() - secondNode.location().x(), 2) + pow(firstNode.location().y() - secondNode.location().y(), 2));

	return distance / 32;
}
}
}