aux_source_directory(. DIR_slave-spi_SRCS)

add_library(slave-spi ${DIR_slave-spi_SRCS})

target_link_libraries(slave-spi PUBLIC)