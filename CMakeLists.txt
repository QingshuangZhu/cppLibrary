cmake_minimum_required(VERSION 3.12)
project(Mylib
    VERSION 1.0.0
    DESCRIPTION "My library with interface and Pimpl pattern"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# compiler options
if(MSVC)
    add_compile_options(/W4 /WX /EHsc)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
endif()

# options for building shared and static libraries
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_STATIC_LIBS "Build static library" ON)

# mylib_interface library configuration
add_library(mylib_interface INTERFACE)
target_include_directories(mylib_interface INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# shared library configuration
if(BUILD_SHARED_LIBS)
    add_library(mylib_shared SHARED
        src/MyClass.cpp
    )

    target_link_libraries(mylib_shared PUBLIC mylib_interface)
    
    # symbol visibility configuration
    if(WIN32)
        target_compile_definitions(mylib_shared PRIVATE MYLIBRARY_EXPORTS)
    else()
        target_compile_options(mylib_shared PRIVATE -fvisibility=hidden)
    endif()

    set_target_properties(mylib_shared PROPERTIES
        OUTPUT_NAME mylib
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        WINDOWS_EXPORT_ALL_SYMBOLS OFF
    )
endif()

# static library configuration
if(BUILD_STATIC_LIBS)
    add_library(mylib_static STATIC
        src/MyClass.cpp
    )

    target_link_libraries(mylib_static PUBLIC mylib_interface)
    set_target_properties(mylib_static PROPERTIES
        OUTPUT_NAME mylib
    )
endif()


# installation
install(DIRECTORY include DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(TARGETS mylib_shared mylib_static
    EXPORT mylib-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
