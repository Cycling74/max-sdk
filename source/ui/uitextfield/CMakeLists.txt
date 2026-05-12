set_property(DIRECTORY PROPERTY max::external YES)
project(uitextfield)

target_sources(uitextfield
    PRIVATE
        uitextfield.c
        "${MAXSDK_SOURCE_DIR}/c74support/max-includes/common/jpatcher_syms.c")
