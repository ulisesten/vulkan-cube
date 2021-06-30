cmake_minimum_required(VERSION 3.1)

project(vulkan)

add_subdirectory(modules/glslang/)

set( SRC src/main.cpp
         src/util.cpp
         src/util_init.cpp )

find_package(Vulkan REQUIRED FATAL_ERROR)

find_package(X11 REQUIRED)

#list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/glslang")
#find_package(GLSLang COMPONENTS GLSLang SPIRV)

#find_library(SPIRV NAMES SPIRV PATHS ${PROJECT_SOURCE_DIR}/glslang/build/SPIRV/)
#find_library(SPIRV_Tools_Lib NAMES SPIRV-Tools PATHS ${PROJECT_SOURCE_DIR}/glslang/build/External/spirv-tools/source/)
#find_library(glslang NAMES glslang PATHS "${PROJECT_SOURCE_DIR}/glslang/build/glslang/")

include_directories(${Vulkan_INCLUDE_DIR})
include_directories(${X11_INCLUDE_DIR})


add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/glslang
)

set(GLSLANGLIBS
    glslang
    SPIRV
#    HLSL
#    OSDependent
#    OGLCompiler
)

#target_link_libraries(${PROJECT_NAME} ${SPIRV_Tools_Lib})
#target_link_libraries(${PROJECT_NAME} ${SPIRV_Lib})
target_link_libraries(${PROJECT_NAME} ${GLSLANGLIBS})
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${X11_xcb_LIB})