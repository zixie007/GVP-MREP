cmake_minimum_required(VERSION 3.0.2)
# ${PROJECT_NAME} = murder_swarm
project(murder_swarm)

add_definitions(-std=c++14)
set(CMAKE_BUILD_TYPE Release)
# This catkin package is designed to make the CMakeLists.txt of other catkin packages simpler
# https://github.com/catkin/catkin_simple
find_package(catkin_simple REQUIRED)

# catkin包:功能包。必须同时包含package.xml(主要)和CMakeLists.txt

# find_package(catkin REQUIRED COMPONENTS
#   roscpp
#   nav_msgs
#   std_msgs
#   quadrotor_msgs
#   eigen_conversions
#   visualization_msgs
#   sensor_msgs
#   pcl_ros
#   mavros
#   rosfmt
# )

# 从package.xml中收集build_depend(有些非catkin包也行，eg:opencv)存入列表中，再把列表传递到find_package(catkin REQUIRED COMPONENTS ...)，自动处理${catkin_INCLUDE_DIRS}、${catkin_LIBRARIES}
# This command is required.
catkin_simple(ALL_DEPS_REQUIRED)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

# 等价于 add_library(murder_swarm src/murder.cpp) + target_link_libraries(murder_swarm ${catkin_LIBRARIES})
cs_add_library(${PROJECT_NAME} src/murder.cpp)

# 库murder_swarm_fsm 还依赖于 库murder_swarm
cs_add_library(${PROJECT_NAME}_fsm src/murderFSM.cpp)
target_link_libraries(${PROJECT_NAME}_fsm
    ${catkin_LIBRARIES} ${PROJECT_NAME} )

cs_add_library(ground src/ground.cpp)

# 等价于 add_executable(murder_swarm_node src/murder_node.cpp) + target_link_libraries(murder_swarm_node ${catkin_LIBRARIES})
cs_add_executable(murder_swarm_node src/murder_node.cpp)
# Notice that here we have to explicitly call target_link_libraries for linking against our library, 
# this is because there is no way to enforce order of target creation  也就是说cs_add_executable后必须跟target_link_libraries
# 可执行文件murder_swarm_node 还依赖于 库murder_swarm_fsm，executable会自动链接到${catkin_LIBRARIES}这里不写也行
target_link_libraries(murder_swarm_node
    ${catkin_LIBRARIES} ${PROJECT_NAME}_fsm)

cs_add_executable(swarm_trigger src/swarm_trigger.cpp)

target_link_libraries(swarm_trigger
    ${catkin_LIBRARIES})



cs_add_executable(ground_node src/ground_node.cpp)

target_link_libraries(ground_node
        ${catkin_LIBRARIES} ground)
##########
# EXPORT #
##########

# This command is optional
cs_install()
# 底层调用catkin_package(...) This command is required.
# catkin_package(...)：声明该catkin包合法。以${PROJECT_NAME}导出当前包的信息（头文件 库 依赖关系），使得其他catkin包可以通过find_package()找到它并依赖它
cs_export()