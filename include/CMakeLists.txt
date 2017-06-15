
macro (install_headers_with_directory HEADER_LIST)
    foreach (HEADER ${${HEADER_LIST}})
        string (REGEX MATCH "(.\\\*)\\\[/\\\]" DIR ${HEADER})
        install (FILES ${HEADER} DESTINATION include/${DIR})
    endforeach (HEADER)

endmacro (install_headers_with_directory)

file (
    GLOB_RECURSE
    HEADERS_FILES
    "*.hpp"
)

install_headers_with_directory (HEADERS_FILES)
