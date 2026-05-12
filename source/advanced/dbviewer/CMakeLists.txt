set_property(DIRECTORY PROPERTY max::external YES)
project(dbviewer)

target_sources(dbviewer
    PRIVATE
        "dbviewer.c"
        "${MAXSDK_SOURCE_DIR}/c74support/max-includes/common/commonsyms.c")

