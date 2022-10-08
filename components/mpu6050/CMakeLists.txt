aux_source_directory(. DIR_mpu6050_SRCS)

add_library(mpu6050 ${DIR_mpu6050_SRCS})

target_link_libraries(mpu6050 PUBLIC)