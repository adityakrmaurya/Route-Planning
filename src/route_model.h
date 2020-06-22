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
    // Add public Node variables and methods here.

    Node() {}
    Node(int idx, RouteModel *search_model, Model::Node node)
        : Model::Node(node), parent_model(search_model), index(idx) {}

  private:
    // Add private Node variables and methods here.
    int index;
    RouteModel *parent_model = nullptr;
  };

  // Add public RouteModel variables and methods here.
  RouteModel(const std::vector<std::byte> &xml);
  std::vector<Node> path; // This variable will eventually store the path that
                          // is found by the A* search.
  auto &SNodes() { return m_Nodes; };

private:
  // Add private RouteModel variables and methods here.
  std::vector<Node> m_Nodes;
};
