cmake_minimum_required(VERSION 2.8.3)

project(gcopter)

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -fPIC")

# 非catkin库-case1、case2、case3;  catkin库-case4   

# case1：eigen库只有头文件 <Eigen3Config.cmake>中未定义${EIGEN3_LIBRARIES}，所以只需要include_directories(${EIGEN3_INCLUDE_DIRS})
find_package(Eigen3 REQUIRED)

# case1：<omplConfig.cmake>中定义${OMPL_INCLUDE_DIRS}和${OMPL_LIBRARIES}
# find_package(ompl REQUIRED)
# include_directories(${OMPL_INCLUDE_DIRS})、target_link_libraries(traj_opt ${OMPL_LIBRARIES})

# case3：<OsqpEigenConfig.cmake>中未定义${OSQPEIGEN_INCLUDE_DIRS}和${OSQPEIGEN_LIBRARIES},采用imported target方式<OsqpEigenTargets.cmake>
# find_package(OsqpEigen REQUIRED)
# target_link_libraries(${PROJECT_NAME}_node OsqpEigen::OsqpEigen)

# case4：find_package(catkin REQUIRED COMPONENTS...)
# include_directories(${catkin_INCLUDE_DIRS})、target_link_libraries(traj_opt ${catkin_LIBRARIES})
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
  visualization_msgs
)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${OMPL_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    include
)

# catkin_package(
#   INCLUDE_DIRS include   #- 导出包的include路径
#   LIBRARIES my_dep_app   #- 导出项目中的库
#   CATKIN_DEPENDS my_dep  #- 该项目依赖的其他catkin项目
#   DEPENDS system_lib     #- 该项目所依赖的非catkin CMake项目，如普通的opencv库。
# )

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES traj_opt
#  DEPENDS system_lib
)

add_library(traj_opt src/traj_opt.cpp)

target_link_libraries(traj_opt
  ${OMPL_LIBRARIES}
  ${catkin_LIBRARIES}
)
