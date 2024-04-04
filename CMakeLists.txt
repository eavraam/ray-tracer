# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project name
project ("RayTracing")

# Output directories
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Add subdirectories
add_subdirectory(src)

# Folder organization for the IDE, not affecting the build (virtual folder)
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.h")
SOURCE_GROUP("Headers" FILES ${HEADER_FILES})

# Specify the C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()

# Include directories
include_directories (${PROJECT_SOURCE_DIR}/include)