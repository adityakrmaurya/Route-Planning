#pragma once

#include "route_model.h"
#include <iostream>
#include <string>
#include <vector>

class RoutePlanner {
public:
  RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x,
               float end_y);
  // Add public variables or methods declarations here.
  float GetDistance() { return distance; }
  void AStarSearch();

private:
  // Add private variables or methods declarations here.
  RouteModel &m_Model;
  RouteModel::Node *start_node, *end_node;
  float distance;
  std::vector<RouteModel::Node>
  ConstructFinalPath(RouteModel::Node *current_node);
  float CalculateHValue(const RouteModel::Node *node);
  std::vector<RouteModel::Node *> open_list;
  RouteModel::Node *NextNode();
};
