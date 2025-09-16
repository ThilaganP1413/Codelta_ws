cmake_minimum_required(VERSION 3.8)
project(delta_gz_sim_cpp)

find_package(ament_cmake REQUIRED)
# find_package(delta_gz_sim_cpp REQUIRED)

# Install project launch files
install(
  DIRECTORY
    launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# Install project configuration files
install(
  DIRECTORY
    configs/
  DESTINATION share/${PROJECT_NAME}/configs
)

install(
  DIRECTORY
    descriptions/
  DESTINATION share/${PROJECT_NAME}/descriptions
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
