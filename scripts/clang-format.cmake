# additional target to perform clang-format run, requires clang-format

# get all project files
set(SOURCES

    main.cpp

)

list(TRANSFORM SOURCES PREPEND ${PROJECT_SOURCE_DIR}/src/)

foreach (SOURCE_FILE ${SOURCES})

    string(FIND ${SOURCE_FILE} ${PROJECT_SOURCE_DIR}/src PROJECT_SOURCE_DIR_FOUND)
    if (NOT ${PROJECT_SOURCE_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM SOURCES ${SOURCE_FILE})
    endif ()

endforeach ()

add_custom_target(
        clangformat
        COMMAND /usr/bin/clang-format
        -style=LLVM
        -i
        ${SOURCES}
)
