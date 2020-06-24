#pragma once

#include "model.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <unordered_map>

class RouteModel : public Model {

public:
  class Node : public Model::Node {
  public:
    Node *parent = nullptr;
    float h_value = std::numeric_limits<float>::max();
    float g_value = 0.0;
    bool visited = false;
    std::vector<Node *> neighbors;

    float distance(Node node) const {
      return std::sqrt(std::pow((x - node.x), 2) + std::pow((y - node.y), 2));
    }

    Node() {}
    Node(int idx, RouteModel *search_model, Model::Node node)
        : Model::Node(node), parent_model(search_model), index(idx) {}
    void FindNeighbors();

  private:
    int index;
    RouteModel *parent_model = nullptr;
    Node *FindNeighbor(std::vector<int> node_indices);
  };

  RouteModel(const std::vector<std::byte> &xml);
  std::vector<Node> path;
  auto &SNodes() { return m_Nodes; };
  auto &GetNodeToRoadMap() { return node_to_road; }
  Node &FindClosestNode(float x, float y);

private:
  std::vector<Node> m_Nodes;
  std::unordered_map<int, std::vector<const Model::Road *>> node_to_road;
  void CreateNodeToRoadHashmap();
};
