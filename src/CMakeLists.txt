
file (
    GLOB_RECURSE
    SRC_FILES
    "*.cpp"
)

add_library (HyperConsole ${SRC_FILES})

set_target_properties (HyperConsole PROPERTIES
    XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
    OUTPUT_NAME hyperconsole
    LINK_FLAGS "${HYPER_LINK_FLAGS}"
)

target_include_directories (HyperConsole PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
