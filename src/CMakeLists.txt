
file (
    GLOB_RECURSE
    SRC_FILES
    "*.cpp"
)

add_library (HyperConsoleLib ${SRC_FILES})

set_target_properties (HyperConsoleLib PROPERTIES
    XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
    OUTPUT_NAME hyperconsole
    COMPILE_FLAGS "${HYPER_LINK_FLAGS} -I."
    LINK_FLAGS "${HYPER_LINK_FLAGS}"
)

target_include_directories (HyperConsoleLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install (TARGETS HyperConsoleLib DESTINATION lib)
