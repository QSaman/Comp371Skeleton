project(opengl)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

################################################################################
if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    OPTION(USE_External_GLFW "Use GLFW externally (recommended for platforms which support pkgconfig like Linux" ON)
    OPTION(USE_External_GLEW "Use GLEW externally (recommended for platforms like Linux" ON)
    OPTION(USE_External_GLM "Use GLM externally (recommended for platforms like Linux" ON)
else (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    OPTION(USE_External_GLFW "Use GLFW externally (recommended for platforms which support pkgconfig like Linux" OFF)
    OPTION(USE_External_GLEW "Use GLEW externally (recommended for platforms like Linux" OFF)
    OPTION(USE_External_GLM "Use GLM externally (recommended for platforms like Linux" OFF)
endif (${CMAKE_SYSTEM_NAME} STREQUAL Linux)    
################################################################################

# Adding header files recursively. aux_source_directory doesn't do that very well
file(GLOB_RECURSE headerFilesList "*.h" "*.hpp")
add_custom_target(headerFiles SOURCES ${headerFilesList})

################################################################################
# Enabling C++11. Add these two lines after add_executable. Notice you must 
# Enable C++11 for every target in all your CMake scripts.
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

################################################################################

find_package(OpenGL REQUIRED)

if (${USE_External_GLEW})
    find_package(GLEW REQUIRED)
    set(externalLibs ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
else (${USE_External_GLEW})
    add_subdirectory(${PROJECT_SOURCE_DIR}/external/glew/build/cmake)
    include_directories(${PROJECT_SOURCE_DIR}/external/glew/include)
    set(target_list ${PROJECT_NAME} glew)
endif (${USE_External_GLEW})

if (${USE_External_GLFW})
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    set(externalLibs ${externalLibs} ${GLFW_LIBRARIES})
else (${USE_External_GLFW})
    add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw)
    include_directories(${PROJECT_SOURCE_DIR}/external/glfw/include)
    set(externalLibs ${externalLibs} glfw ${GLFW_LIBRARIES})
endif (${USE_External_GLFW})

if (NOT ${USE_External_GLM})
    include_directories(${PROJECT_SOURCE_DIR}/external/glm)
endif (NOT ${USE_External_GLM})

target_link_libraries(${PROJECT_NAME} ${externalLibs})

file(COPY ${PROJECT_SOURCE_DIR}/shaders/ DESTINATION ${PROJECT_BINARY_DIR}/shaders
     FILES_MATCHING PATTERN "*")

