cmake_minimum_required(VERSION 3.20)
project(wtr-lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------------
# Configuración de Opciones de Dependencias
# -------------------------------------------------------------------
# fmt / spdlog
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)

# cpr (Usar la libcurl del sistema operativo)
set(CPR_USE_SYSTEM_CURL ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# wxWidgets
set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)
set(wxUSE_PKGCONFIG OFF CACHE BOOL "" FORCE)
set(wxUSE_WEBVIEW OFF CACHE BOOL "" FORCE)
set(wxUSE_ZLIB "builtin" CACHE STRING "" FORCE)
set(wxUSE_EXPAT "builtin" CACHE STRING "" FORCE)
set(wxUSE_LIBJPEG "builtin" CACHE STRING "" FORCE)
set(wxUSE_LIBPNG "builtin" CACHE STRING "" FORCE)

add_subdirectory(external/fmt)
add_subdirectory(external/spdlog)
add_subdirectory(external/cpr)
add_subdirectory(external/wxWidgets)
add_subdirectory(external/webview)

# Dependencias del sistema necesarias en Linux
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

    pkg_check_modules(WEBKIT IMPORTED_TARGET webkit2gtk-4.1)
    if(NOT WEBKIT_FOUND)
        pkg_check_modules(WEBKIT REQUIRED IMPORTED_TARGET webkit2gtk-4.0)
    endif()
endif()

add_executable(wtr-lab
    src/main.cpp
    src/window.hpp
    src/window.cpp
    src/config_items.hpp
)

add_custom_command(
    TARGET wtr-lab POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:wtr-lab>/assets"
)

target_link_libraries(wtr-lab PRIVATE
    fmt::fmt
    spdlog::spdlog
    cpr::cpr
    wx::core
    wx::base
    webview::core
)

if(UNIX AND NOT APPLE)
    target_link_libraries(wtr-lab PRIVATE
        PkgConfig::WEBKIT
        PkgConfig::GTK3
    )
endif()