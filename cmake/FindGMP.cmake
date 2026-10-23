find_path(GMP_INCLUDE_DIR
    NAMES gmp.h gmpxx.h
    PATHS
        ENV GMP_LOCATION
        ${CMAKE_PREFIX_PATH}
    PATH_SUFFIXES include
)
find_path(GMP_LIBRARY
    NAMES gmp libgmp
    PATHS
        ENV GMP_LOCATION
        ${CMAKE_PREFIX_PATH}
    PATH_SUFFIXES lib lib64 bin
)
find_path(GMPXX_LIBRARY
    NAMES gmpxx libgmpxx
    PATHS
        ENV GMP_LOCATION
        ${CMAKE_PREFIX_PATH}
    PATH_SUFFIXES lib lib64 bin
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    REQUIRED_VARS GMP_INCLUDE_DIR GMP_LIBRARY
)

if(GMP_FOUND AND NOT TARGET GMP::GMP)
    add_library(GMP::GMP UNKNOWN IMPORTED)
    set_target_properties(GMP::GMP PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
        IMPORTED_LOCATION "${GMP_LIBRARY}"
    )
endif()

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARY)