cmake_minimum_required(VERSION 3.15)
project(pong CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML REQUIRED)

add_executable(pong src/ball.cpp src/bat.cpp src/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml::sfml)

target_include_directories(${PROJECT_NAME} 
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

add_custom_target(copy_assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/assets"
          "${CMAKE_CURRENT_BINARY_DIR}/assets"
  COMMENT "Copying assets to build directory"
)

add_dependencies(${PROJECT_NAME} copy_assets)

install(TARGETS pong DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
