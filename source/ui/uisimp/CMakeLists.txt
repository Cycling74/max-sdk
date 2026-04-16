set_property(DIRECTORY PROPERTY max::external YES)
project(uisimp)

target_sources(uisimp
    PRIVATE
        # Change this to compile a different uisimp*.c file
        uisimp.c
)
