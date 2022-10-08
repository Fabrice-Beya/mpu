aux_source_directory(. DIR_main-controller_SRCS)
include_directories(../slave-spi)
include_directories(../utils)

add_library(main-controller ${DIR_main-controller_SRCS})

target_link_libraries(main-controller PUBLIC slave-spi utils)