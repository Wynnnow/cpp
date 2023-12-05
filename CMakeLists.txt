# 指定cmake版本
cmake_minimum_required(VERSION 3.23)

# 指定项目名称
project(cpp)

# 指定c++标准版本
set(CMAKE_CXX_STANDARD 14)


# 添加三方库的头文件路径
include_directories(${CMAKE_SOURCE_DIR}/thirdLib/include)

# 添加三方库的库文件路径
link_directories(${CMAKE_SOURCE_DIR}/thirdLib/lib)

# 添加Google Test 框架的链接库
link_libraries(gtest)
link_libraries(gtest_main)

# 指定项目可执行文件 cpp 项目的名称， main.cpp 项目源代码文件
add_executable(cpp main.cpp)
