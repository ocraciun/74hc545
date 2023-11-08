aux_source_directory(. DIR_hc545_SRCS)

add_library(hc545 ${DIR_hc545_SRCS})
target_link_libraries(hc545 PUBLIC pico_stdlib hardware_spi)
