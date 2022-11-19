cmake_minimum_required(VERSION 3.5)
project(kiroku)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -fPIC)
endif()

find_package(ament_cmake REQUIRED)
find_package(kiroku_interfaces REQUIRED)
find_package(rclcpp REQUIRED)

add_library(${PROJECT_NAME} SHARED
  "src/kiroku/examples/node/publisher_node.cpp"
  "src/kiroku/node/kiroku_node.cpp"
  "src/kiroku/writer/writer.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  kiroku_interfaces)

install(DIRECTORY "include" DESTINATION ".")

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  RUNTIME DESTINATION "bin")

add_executable(publisher_main "examples/publisher_main.cpp")
target_include_directories(publisher_main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(publisher_main ${PROJECT_NAME})

add_executable(kiroku_main "src/kiroku_main.cpp")
target_include_directories(kiroku_main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(kiroku_main ${PROJECT_NAME})

install(TARGETS
  publisher_main
  kiroku_main
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(
  rclcpp
  kiroku_interfaces)
ament_export_include_directories("include")
ament_export_libraries(${PROJECT_NAME})
ament_package()
