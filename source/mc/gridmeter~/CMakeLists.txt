set_property(DIRECTORY PROPERTY max::external YES)
project(gridmeter_tilde)

target_sources(gridmeter_tilde
    PRIVATE
        "gridmeter~.c"
        "${MAXSDK_SOURCE_DIR}/c74support/max-includes/common/commonsyms.c")

