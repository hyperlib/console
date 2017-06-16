
file (
    GLOB_RECURSE
    INCLUDE_FILES
    "*.hpp"
)


foreach (file ${INCLUDE_FILES} )
    get_filename_component (dir ${file} DIRECTORY)
    install (FILES ${file} DESTINATION include/${dir})
endforeach()
