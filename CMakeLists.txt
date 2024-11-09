# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (Algo_DA CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)
# 包含子项目。
add_subdirectory(array_and_linkedlist)
add_subdirectory(binary_tree)
add_subdirectory(sorting)
add_subdirectory(searching)
add_subdirectory(heap_top)
add_subdirectory(hashing)
add_subdirectory(greedy)
add_subdirectory(divide_and_conquer)
add_subdirectory(computational_complexity)
add_subdirectory(decision_tree)
add_subdirectory(backtracking)
add_subdirectory(graph)
add_subdirectory(dynamic_programming)

add_subdirectory(extern_api)