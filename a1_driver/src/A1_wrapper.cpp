//
// Created by sun on 2021/3/1.
//

#include "a1_driver/A1_wrapper.h"

#include <time.h>

void A1Wrapper::walkCmd(float forwardSpeed, float sideSpeed,
                        float rotateSpeed) {
  UNITREE_LEGGED_SDK::HighState current_state;
  UNITREE_LEGGED_SDK::HighCmd high_cmd = {};

  udp.GetRecv(current_state);
  //    unitree a1 cannot send correct state information now, this function is
  //    unfinished. (From Unitree Development Team) std::cout <<
  //    unsigned(current_state.mode) << std::endl;

  //    step 1 : UDP mode = 1
  high_cmd.mode = 1;
  std::cout << "change mode : 0 -> 1, sleep : 2s." << std::endl;
  udp.SetSend(high_cmd);
  sleep(2);

  //    step 2 : mode = 2
  high_cmd.mode = 2;
  std::cout << "change mode : 1 -> 2, sleep : 2s." << std::endl;
  udp.SetSend(high_cmd);
  sleep(2);

  //    step 3: walk
  std::cout << "walk 4s" << std::endl;
  high_cmd.forwardSpeed = forwardSpeed;
  high_cmd.sideSpeed = sideSpeed;
  high_cmd.rotateSpeed = rotateSpeed;
  udp.SetSend(high_cmd);
  sleep(4);

  std::cout << "stop 10s" << std::endl;
  stop();
}

void A1Wrapper::stop() {
  UNITREE_LEGGED_SDK::HighCmd stop_cmd = {};
  stop_cmd.mode = 1;
  udp.SetSend(stop_cmd);
  sleep(4);
}

void A1Wrapper::setVel(float forward_speed) {
  UNITREE_LEGGED_SDK::HighCmd foward_cmd = {};
  foward_cmd.forwardSpeed = forward_speed;
  udp.SetSend(foward_cmd);
  sleep(10);
}

void A1Wrapper::setWalkMode() {
  UNITREE_LEGGED_SDK::HighCmd walk_mode = {};
  walk_mode.mode = 1;
  udp.SetSend(walk_mode);
  sleep(10);
}

void A1Wrapper::bodyPose(double roll, double pitch, double yaw) {
    UNITREE_LEGGED_SDK::HighCmd pose_cmd = {};
    pose_cmd.mode = 1;
    pose_cmd.roll = roll;
    pose_cmd.pitch = pitch;
    pose_cmd.yaw = yaw;
    udp.SetSend(pose_cmd);
}