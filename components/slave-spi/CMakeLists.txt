aux_source_directory(. DIR_slave-spi_SRCS)

include_directories(../utils)

add_library(slave-spi ${DIR_slave-spi_SRCS})

target_link_libraries(slave-spi PUBLIC utils)