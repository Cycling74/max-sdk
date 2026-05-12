set(C74_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../externals")

set_property(DIRECTORY PROPERTY max::external YES)
project(dllreport)

target_sources(dllreport
    PRIVATE
        # Source files
        "dllreport.cpp"

    PRIVATE FILE_SET HEADERS
        # Include dirs
        BASE_DIRS
            "${CMAKE_CURRENT_LIST_DIR}/.."

        # Included headers
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/../mydll.h"
)

target_link_libraries(dllreport PRIVATE mydll)
