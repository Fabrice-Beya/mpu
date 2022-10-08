cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(components/slave-spi)
add_subdirectory(components/mpu6050)
add_subdirectory(components/main-controller)
add_subdirectory(components/utils)

include_directories(./main)
include_directories(./components/utils)
include_directories(./components/slave-spi)
include_directories(./components/mpu6050)
include_directories(./components/main-controller)

add_executable(${PROJECT_NAME} main/main.c)


target_link_libraries(main utils main-controller mpu6050 slave-spi Threads::Threads)
