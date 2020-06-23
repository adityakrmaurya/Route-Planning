#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  int counter = 0;
  for (Model::Node node : this->Nodes()) {
    m_Nodes.push_back(Node(counter, this, node));
    counter++;
  }
  CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap() {
  for (const Model::Road &road : Roads()) {
    if (road.type != Model::Road::Type::Footway) {
      for (int node_idx : Ways()[road.way].nodes) {
        if (node_to_road.find(node_idx) == node_to_road.end()) {
          node_to_road[node_idx] = std::vector<const Model::Road *>();
        }
        node_to_road[node_idx].push_back(&road);
      }
    }
  }
}

RouteModel::Node *
RouteModel::Node::FindNeighbor(std::vector<int> node_indices) {
  Node *closest_node = nullptr;
  Node node;
  for (int node_index : node_indices) {
    node = parent_model->SNodes()[node_index];
    if (this->distance(node) != 0 && !node.visited) {
      if (closest_node == nullptr ||
          this->distance(node) < this->distance(*closest_node)) {
        closest_node = &parent_model->SNodes()[node_index];
      }
    }
  }
  return closest_node;
}