cmake_minimum_required(VERSION 3.7)
set(project_name cpp_20_study)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_COMPILER "/usr/bin/gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fcoroutines")

project(${project_name})

#设置版本号
set(VERSION_MAJOR 1.2)
set(VERSION_MINOR 0)

#log 选项
# 这个项目没有使用boost
#add_definitions(-DLOG_BOOST)

# 设置conan 参数
set(CONAN_ARGS "${CONAN_ARGS} --profile gcc10")
message("CONAN_ARGS: ${CONAN_ARGS}")


# 设置源码根目录(包含cmake的文件夹将被解析为一个编译target)
set(SRC_DIR_ROOT ${CMAKE_SOURCE_DIR}/src)
# 设置配目录(运行时拷贝)
set(CONFIG_DIR ${CMAKE_SOURCE_DIR}/data)
# 设置 boostStrap 文件夹名
set(BOOTSTRAP_DIR ${CMAKE_SOURCE_DIR}/cpp_bootstrap)

# 开始加载
include(cpp_bootstrap/BasicCmake.cmake)
