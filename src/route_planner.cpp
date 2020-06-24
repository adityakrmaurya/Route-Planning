#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y,
                           float end_x, float end_y)
    : m_Model(model) {
  // converting the inputs to percentage
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}
std::vector<RouteModel::Node>
RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  std::vector<RouteModel::Node> path_found;
  distance = 0.0f;
  RouteModel::Node parent;

  while (current_node->parent != nullptr) {
    path_found.push_back(*current_node);
    parent = *(current_node->parent);
    distance += current_node->distance(parent);
    current_node = current_node->parent;
  }
  path_found.push_back(*current_node);
  distance *= m_Model.MetricScale();
  return path_found;
}

void RoutePlanner::AStarSearch() {
  end_node->parent = start_node;
  m_Model.path = ConstructFinalPath(end_node);
  return;
}

float RoutePlanner::CalculateHValue(const RouteModel::Node *node) {
  return node->distance(*end_node);
}

RouteModel::Node *RoutePlanner::NextNode() {
  std::sort(open_list.begin(), open_list.end(),
            [](const auto node1, const auto node2) {
              return node1->h_value + node1->g_value <
                     node2->h_value + node2->g_value;
            });
  RouteModel::Node *optimal_node = open_list.front();
  open_list.erase(open_list.begin());
  return optimal_node;
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  for (auto neighbor : current_node->FindNeighbors()) {
    neighbor->parent = current_node;
    neighbor->g_value = current_node->distance(neighbor) + current_node->g_value;
    neighbor->h_value = CalculateHValue(neighbor);
    open_list.push_back(neighbor);
    neighbor->visited = true;
  }
}