set_property(DIRECTORY PROPERTY max::external YES)
project(mc.pack_tilde)

target_sources(mc.pack_tilde
    PRIVATE
        "mc.pack~.c"
        "${MAXSDK_SOURCE_DIR}/c74support/max-includes/common/commonsyms.c")

