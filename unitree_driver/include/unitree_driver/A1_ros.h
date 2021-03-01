//
// Created by sun on 2021/3/1.
//

#ifndef UNITREE_DRIVER_A1_ROS_H
#define UNITREE_DRIVER_A1_ROS_H

#include <memory>
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "unitree_driver/A1_wrapper.h"

class A1ROS
{
public:
    A1ROS(std::string node_name):wrapper(A1Wrapper()){
        this->node_name = node_name;
    };

    int node_init();
    void walkCallback(const geometry_msgs::msg::Twist::SharedPtr msg);
    A1Wrapper wrapper;

private:
    std::string node_name;
};

#endif //UNITREE_DRIVER_A1_ROS_H