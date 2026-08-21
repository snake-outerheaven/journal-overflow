cmake_minimum_required(VERSION 3.16)

project(T1DiscreteMath VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_library(pa SHARED src/pa.c)
target_compile_definitions(pa PRIVATE $<$<PLATFORM_ID:Windows>:PA_BUILD_DLL>)
target_include_directories(pa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(utils SHARED src/utils.c)
target_compile_definitions(utils PRIVATE $<$<PLATFORM_ID:Windows>:UTILS_BUILD_DLL>)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(pa_app src/main.c)
set_target_properties(pa_app PROPERTIES OUTPUT_NAME pa)
target_link_libraries(pa_app PRIVATE pa utils)

include(CTest)

if(BUILD_TESTING)
  add_executable(test_pa tests/test_pa.c)
  target_link_libraries(test_pa PRIVATE pa)
  add_test(NAME pa_tests COMMAND test_pa)
endif()
