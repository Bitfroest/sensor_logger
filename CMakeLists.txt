set ( SOURCES 
    "src/sensor_logger.cpp"
    "src/interface.cpp"
)

set (HEADERS
    "include/sensor_logger.h"
)

include_directories("include")

add_library ( sensor_logger MODULE ${SOURCES} ${HEADERS})
target_link_libraries(sensor_logger PRIVATE lms sense_link)
