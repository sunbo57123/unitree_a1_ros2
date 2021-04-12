//
// Created by sun on 2021/3/1.
//

#ifndef UNITREE_DRIVER_A1_ROS_H
#define UNITREE_DRIVER_A1_ROS_H

#include <memory>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"
#include "a1_driver/A1_wrapper.h"

class A1ROS {
public:
  A1ROS(std::string node_name) : wrapper(A1Wrapper()) {
    this->node_name = node_name;
  }

  void node_init(int argc, char * argv[]);

  A1Wrapper wrapper;

private:
  std::string node_name;
};

#endif   //UNITREE_DRIVER_A1_ROS_H
