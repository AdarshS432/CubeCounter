# TEMPORARY FOR FETCHCONTENT TESTING: FetchContent_MakeAvailable requires CMake 3.14+.
cmake_minimum_required(VERSION 3.16)

option(BUILD_GUI "Build the GUI version of the application" ON)
option(OPEN_CMD "Open the command line interface with GUI" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(CubeCounter VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent) # TEMPORARY FOR FETCHCONTENT TESTING

find_library(GMP_LIBRARY NAMES gmp libgmp REQUIRED)
find_library(GMPXX_LIBRARY NAMES gmpxx libgmpxx REQUIRED)
find_path(GMP_INCLUDE NAMES gmpxx.h REQUIRED)

# >>> TEMPORARY BOOST.MP TEST DEPENDENCY: remove this block if not adopting Boost.
FetchContent_Declare(boost_multiprecision
    GIT_REPOSITORY https://github.com/boostorg/multiprecision.git
    GIT_TAG Boost_1_92_0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(boost_multiprecision)
# <<< TEMPORARY BOOST.MP TEST DEPENDENCY

if(BUILD_GUI) 
    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
    # Extra X-11 Extensions
    set(SDL_X11_XCURSOR OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XDBE OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XINPUT OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XFIXES OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XRANDR OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XSCRNSAVER OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XSHAPE OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XSYNC OFF CACHE BOOL "" FORCE)
    set(SDL_X11_XTEST OFF CACHE BOOL "" FORCE)
    set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.18
        GIT_SHALLOW TRUE
    )
    FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(SDL3 glm)

    FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.9b
        GIT_SHALLOW TRUE
    )
    FetchContent_GetProperties(imgui)
    if(NOT imgui_POPULATED)
        FetchContent_Populate(imgui)
    endif()

    add_library(imgui STATIC
        "${imgui_SOURCE_DIR}/imgui.cpp"
        "${imgui_SOURCE_DIR}/imgui_draw.cpp"
        "${imgui_SOURCE_DIR}/imgui_tables.cpp"
        "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
        "${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp"
        "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    )
    add_library(imgui::imgui ALIAS imgui)
    target_include_directories(imgui PUBLIC
        "${imgui_SOURCE_DIR}"
        "${imgui_SOURCE_DIR}/backends"
    )
    target_link_libraries(imgui PUBLIC SDL3::SDL3)



    find_package(OpenGL REQUIRED)
    #find_package(gmp REQUIRED)

    add_library(glad STATIC "source/glad/glad.c")
    target_include_directories(glad PUBLIC include)

    file(GLOB_RECURSE SOURCES CMAKE_CONFIGURE_DEPENDS
        "source/*.cpp"
        "source/*.c"
    )
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/MainCLI.cpp")

    file(COPY "shaders" DESTINATION "${CMAKE_BINARY_DIR}")
    file(COPY "Fonts" DESTINATION "${CMAKE_BINARY_DIR}")
    if(OPEN_CMD)
        add_executable(CubeCounter ${SOURCES})
    else()
        add_executable(CubeCounter WIN32 MACOSX_BUNDLE ${SOURCES})
    endif()

    target_compile_definitions(CubeCounter PRIVATE __GMP_WITHIN_GMP)
    target_include_directories(CubeCounter PRIVATE ${GMP_INCLUDE} include)
    target_include_directories(CubeCounter PRIVATE include)

    target_link_libraries(CubeCounter PRIVATE 
        SDL3::SDL3
        glm::glm 
        glad 
        ${GMP_LIBRARY}
        Boost::multiprecision
        OpenGL::GL
        imgui::imgui
    )
endif()

add_executable(cubecounter-cli 
    "source/MainCLI.cpp"
    "source/Calculation.cpp"
    "include/Calculation.h")
target_include_directories(cubecounter-cli PRIVATE include)
target_compile_definitions(cubecounter-cli PRIVATE __GMP_WITHIN_GMP)
target_include_directories(cubecounter-cli PRIVATE ${GMP_INCLUDE})
target_link_libraries(cubecounter-cli PRIVATE 

    Boost::multiprecision
)
target_link_libraries(cubecounter-cli PRIVATE 
    ${GMPXX_LIBRARY}
    ${GMP_LIBRARY}
)