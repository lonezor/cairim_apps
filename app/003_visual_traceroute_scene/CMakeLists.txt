cmake_minimum_required(VERSION 3.0)

project(visual_traceroute_scene)

set(CMAKE_BUILD_TYPE Debug) # Release / Debug

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(XLIB REQUIRED x11)
pkg_check_modules(RSVG REQUIRED librsvg-2.0)
pkg_check_modules(CARES REQUIRED libcares)

find_package(Cairim REQUIRED)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME}
  ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  cairim
  ${CAIRO_LIBRARIES}
  ${XLIB_LIBRARIES}
  ${RSVG_LIBRARIES}
  ${CARES_LIBRARIES}
  pthread
  png
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CAIRO_INCLUDE_DIRS}
  ${XLIB_INCLUDE_DIRS}
  ${RSVG_INCLUDE_DIRS}
  ${CARES_INCLUDE_DIRS}
  include
)

target_compile_options(${PROJECT_NAME}
  PUBLIC
  ${CAIRO_CFLAGS_OTHER})

install(FILES svg/laptop.svg DESTINATION share/${PROJECT_NAME})
install(FILES svg/server.svg DESTINATION share/${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

