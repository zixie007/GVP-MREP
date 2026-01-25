#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include<murder_swarm/murderFSM.h>

#include <glog/logging.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "murder_node");
    ros::NodeHandle nh, nh_private("~");
    // 初始化Google日志系统 glog
    google::InitGoogleLogging(argv[0]);
    // 解析通过gflags定义的命令行参数（DEFINE_*）
    google::ParseCommandLineFlags(&argc, &argv, true);
    // 当程序崩溃时，glog会自动打印调用栈，方便调试
    google::InstallFailureSignalHandler();

    MurderFSM M_FSM;
    M_FSM.init(nh, nh_private);
    ros::spin();
    return 0;
}