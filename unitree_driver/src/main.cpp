//
// Created by sun on 2021/3/1.
//

#include "unitree_driver/A1_ros.h"
#include "unitree_driver/A1_wrapper.h"
static void show_usage(std::string name){
    std::cerr << "running ros2 run unitree_driver a1_main --node-name A1_node" << std::endl;
}
int main(int argc, char* argv[]){

    std::string node_name = "A1_node";
    if (argc < 3){
        show_usage(argv[0]);
    }
    for (int i =1; i < argc ; ++i) {
        std::string arg = argv[i];
        if (arg == "--node-name") {
            node_name = argv[i+1];
        }
    }

    A1ROS a1_ros = A1ROS(node_name);
    std::cout << "creating a node named :" << node_name << std::endl;
    a1_ros.node_init(argc, argv);

    return 0;
}
