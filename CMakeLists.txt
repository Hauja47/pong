# CMakeList.txt : CMake project for pong, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("pong")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

# Add source to this project's executable.
add_executable (pong "pong.cpp" "pong.h" "bat.h" "bat.cpp" "ball.h" "ball.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pong PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(pong PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)

add_custom_target(copy_assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/assets"
          "${CMAKE_CURRENT_BINARY_DIR}/assets"
  COMMENT "Copying assets to build directory"
)

add_dependencies(${PROJECT_NAME} copy_assets)
