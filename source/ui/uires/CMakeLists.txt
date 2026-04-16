set_property(DIRECTORY PROPERTY max::external YES)
project(uires)

target_sources(uires
    PRIVATE
        uires.c
        "${MAXSDK_SOURCE_DIR}/c74support/max-includes/common/commonsyms.c")

