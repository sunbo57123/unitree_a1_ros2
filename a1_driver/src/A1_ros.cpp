//
// Created by sun on 2021/3/1.
//
#include "a1_driver/A1_ros.h"

void A1ROS::node_init(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto A1_node = rclcpp::Node::make_shared(this->node_name);
  auto A1_sub = A1_node->create_subscription<geometry_msgs::msg::Twist>(
      "unitree_a1/cmd_vel", 10,
      [this](geometry_msgs::msg::Twist::UniquePtr msg) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "received: speed = %f",
                    msg->linear.x);
        wrapper.walkCmd(msg->linear.x, msg->linear.y, msg->angular.z);
      });
  auto A1_pose = A1_node->create_subscription<geometry_msgs::msg::Pose>(
          "unitree_a1/body_pose", 10,
          [this](geometry_msgs::msg::Pose::UniquePtr msg) {
              RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "set pose");
                tf2::Quaternion received_quaternion;
                received_quaternion.setX(msg->orientation.x);
                received_quaternion.setY(msg->orientation.y);
                received_quaternion.setZ(msg->orientation.z);
                received_quaternion.setW(msg->orientation.w);
                tf2::Matrix3x3 matrix(received_quaternion);
                double roll, pitch, yaw;
                matrix.getRPY(roll, pitch, yaw);
                wrapper.bodyPose(roll, pitch, yaw);
          }
          );
  ////    A1_node->create_subscription<...>();
  //    auto srv_stop =
  //    A1_node->create_service<std_srvs::srv::Trigger>("stop_service",
  //                                                                    [this,
  //                                                                    A1_node]()
  //                                                                    {
  //                                                                        RCLCPP_INFO(A1_node->get_logger(),
  //                                                                                    "execute stop cmds");
  //                                                                        wrapper.stop();
  //                                                                    });
  ////    unitree
  UNITREE_LEGGED_SDK::InitEnvironment();
  float dt = 0.002f;
  UNITREE_LEGGED_SDK::LoopFunc loop_udpRecv(
      "udp_recv", dt, 3, boost::bind(&A1Wrapper::UDPRecv, &wrapper));
  UNITREE_LEGGED_SDK::LoopFunc loop_udpSend(
      "udp_send", dt, 3, boost::bind(&A1Wrapper::UDPSend, &wrapper));
  loop_udpRecv.start();
  loop_udpSend.start();

  rclcpp::spin(A1_node);
  rclcpp::shutdown();
}
