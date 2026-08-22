cmake_minimum_required(VERSION 3.16)

project(T1DiscreteMath VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(project_warnings INTERFACE)

if(MSVC)
  target_compile_options(project_warnings INTERFACE /W4 /WX /permissive-)
else()
  target_compile_options(project_warnings INTERFACE
    -Wall
    -Wextra
    -Werror
    -pedantic
  )
endif()

add_library(pa SHARED src/pa.c)
target_compile_definitions(pa PRIVATE $<$<PLATFORM_ID:Windows>:PA_BUILD_DLL>)
target_include_directories(pa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(pa PRIVATE project_warnings)

add_library(menu STATIC src/menu.c)
target_compile_definitions(menu PRIVATE $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)
target_include_directories(menu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(menu PRIVATE pa project_warnings)

add_executable(pa_app src/main.c)
set_target_properties(pa_app PROPERTIES OUTPUT_NAME pa)
target_link_libraries(pa_app PRIVATE menu project_warnings)

include(CTest)

if(BUILD_TESTING)
  add_executable(test_pa tests/test_pa.c)
  target_link_libraries(test_pa PRIVATE pa project_warnings)
  add_test(NAME pa_tests COMMAND test_pa)
endif()
