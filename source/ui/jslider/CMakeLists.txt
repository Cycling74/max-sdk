set_property(DIRECTORY PROPERTY max::external YES)
project(jslider)

target_sources(jslider
    PRIVATE
        jslider.c
        "${MAXSDK_SOURCE_DIR}/c74support/max-includes/common/commonsyms.c")
