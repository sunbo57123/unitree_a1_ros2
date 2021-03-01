//
// Created by sun on 2021/3/1.
//

#include "unitree_driver/A1_ros.h"

int A1ROS::node_init(){
    rclcpp::init(0, nullptr);
    UNITREE_LEGGED_SDK::InitEnvironment();

    auto A1_node = std::make_shared<rclcpp::Node>(this->node_name);

    A1_node->create_subscription<geometry_msgs::msg::Twist>(
            "A1_walk",
            10,
            std::bind(&A1ROS::walkCallback,
                      this,
                      std::placeholders::_1)
    );
    float dt = 0.002f;

    UNITREE_LEGGED_SDK::LoopFunc loop_udpRecv("udp_recv", dt, 3, boost::bind(&A1Wrapper::UDPRecv, &wrapper));
    UNITREE_LEGGED_SDK::LoopFunc loop_udpSend("udp_send", dt, 3, boost::bind(&A1Wrapper::UDPSend, &wrapper));
    loop_udpRecv.start();
    loop_udpSend.start();

    rclcpp::spin(A1_node);
    rclcpp::shutdown();
}

void A1ROS::walkCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
    wrapper.walkCmd(msg->linear.x, msg->linear.y, msg->angular.z);
}