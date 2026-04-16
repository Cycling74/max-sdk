set_property(DIRECTORY PROPERTY max::external YES)
project(jit.str.op LANGUAGES C)

target_sources(jit.str.op
    PRIVATE
        "jit.str.op.c"
        "max.jit.str.op.c"
        "max.jit.str.op.c"
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES "jit.str.op.h")
