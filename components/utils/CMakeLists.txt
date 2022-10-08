aux_source_directory(. DIR_utils_SRCS)

add_library(utils ${DIR_utils_SRCS})

target_link_libraries(utils PUBLIC)