# Automatic solution, but GLOB needs re-configuring, maybe not optimal.
# Safer to specify the files explicitly.
# file(GLOB_RECURSE SOURCE_FILES "*.cpp")
# file(GLOB_RECURSE HEADER_FILES "*.h")
# 
# add_executable(RayTracing ${SOURCE_FILES} ${HEADER_FILES})

# Add source to this project's executable.
add_executable( RayTracing
	main.cpp
	${PROJECT_SOURCE_DIR}/include/color.h
)

# If there are more source files, explicitly list them here
target_sources(RayTracing PRIVATE
    main.cpp
    # Assume we have additional cpp files and headers
    # additional_file.cpp
    # ${PROJECT_SOURCE_DIR}/include/additional_file.h
)

# Specify where the compiler should look for header files
target_include_directories(RayTracing PRIVATE ${PROJECT_SOURCE_DIR}/include)