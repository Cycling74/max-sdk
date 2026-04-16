set(C74_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../externals")

set_property(DIRECTORY PROPERTY max::external YES)
project(dllcounter)

target_sources(dllcounter
    PRIVATE
        # Source files
        "dllcounter.cpp"

    PRIVATE FILE_SET HEADERS
        # Include directory
        BASE_DIRS
            "${CMAKE_CURRENT_LIST_DIR}/.."

        # Included headers
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/../mydll.h"
)

target_link_libraries(dllcounter PRIVATE mydll)

