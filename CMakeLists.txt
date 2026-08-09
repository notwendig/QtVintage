cmake_minimum_required(VERSION 3.21)

project(qvintage
    VERSION 1.0.0
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---------------------------------------------------------------------------
# Qt
# ---------------------------------------------------------------------------

find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------

option(
    QVINTAGE_BUILD_DESIGNER_PLUGIN
    "Build the Qt Designer plugin"
    ON
)

# ---------------------------------------------------------------------------
# qvintage widget library
# ---------------------------------------------------------------------------

set(QVINTAGE_WIDGET_SOURCES
    LED/LED.cpp
    LED/LED.h

    SEG7/SEG7.cpp
    SEG7/SEG7.h

    SWITCH/SWITCH.cpp
    SWITCH/SWITCH.h

    SWITCH2/SWITCH2.cpp
    SWITCH2/SWITCH2.h
)

add_library(
    qvintage_widgets
    STATIC
    ${QVINTAGE_WIDGET_SOURCES}
)

add_library(
    qvintage::Widgets
    ALIAS
    qvintage_widgets
)

set_target_properties(
    qvintage_widgets
    PROPERTIES
        EXPORT_NAME Widgets
        POSITION_INDEPENDENT_CODE ON
)

target_compile_features(
    qvintage_widgets
    PUBLIC
        cxx_std_20
)

target_link_libraries(
    qvintage_widgets
    PUBLIC
        Qt6::Widgets
)

target_include_directories(
    qvintage_widgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qvintage>
)

# ---------------------------------------------------------------------------
# Qt Designer plugin
# ---------------------------------------------------------------------------

if(QVINTAGE_BUILD_DESIGNER_PLUGIN)

    find_package(
        Qt6 6.2
        REQUIRED
        COMPONENTS
            Designer
            UiPlugin
    )

    #
    # IMPORTANT:
    #
    # Do NOT use:
    #
    #     PLUGIN_TYPE designer
    #     SOURCES
    #
    # here.
    #
    # With Qt 6.2 compatibility the portable solution is to create the
    # plugin first and add its sources afterwards with target_sources().
    #

    qt_add_plugin(
        devicesplugin
        CLASS_NAME devices
    )

    target_sources(
        devicesplugin
        PRIVATE
            devices.cpp
            devices.h

            LED/LEDPlugin.cpp
            LED/LEDPlugin.h

            SEG7/SEG7Plugin.cpp
            SEG7/SEG7Plugin.h

            SWITCH/SWITCHPlugin.cpp
            SWITCH/SWITCHPlugin.h

            SWITCH2/SWITCH2Plugin.cpp
            SWITCH2/SWITCH2Plugin.h

            icons.qrc
    )

    target_compile_features(
        devicesplugin
        PRIVATE
            cxx_std_20
    )

    target_include_directories(
        devicesplugin
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/LED"
            "${CMAKE_CURRENT_SOURCE_DIR}/SEG7"
            "${CMAKE_CURRENT_SOURCE_DIR}/SWITCH"
            "${CMAKE_CURRENT_SOURCE_DIR}/SWITCH2"
    )

    target_link_libraries(
        devicesplugin
        PRIVATE
            qvintage::Widgets
            Qt6::Widgets
            Qt6::Designer
            Qt6::UiPlugin
    )

    # Fedora:
    #   /usr/lib64/qt6/plugins/designer
    #
    # With the default CMAKE_INSTALL_PREFIX=/usr this becomes:
    #   /usr/lib64/qt6/plugins/designer
    #

    set(
        QVINTAGE_DESIGNER_PLUGIN_DIR
        "${CMAKE_INSTALL_LIBDIR}/qt6/plugins/designer"
        CACHE PATH
        "Installation directory for the Qt Designer plugin"
    )

    install(
        TARGETS devicesplugin
        LIBRARY DESTINATION "${QVINTAGE_DESIGNER_PLUGIN_DIR}"
        RUNTIME DESTINATION "${QVINTAGE_DESIGNER_PLUGIN_DIR}"
        BUNDLE  DESTINATION "${QVINTAGE_DESIGNER_PLUGIN_DIR}"
    )

endif()

# ---------------------------------------------------------------------------
# Install qvintage widget library
# ---------------------------------------------------------------------------

install(
    TARGETS qvintage_widgets
    EXPORT qvintageTargets

    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}

    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qvintage
)

# ---------------------------------------------------------------------------
# Install public headers
# ---------------------------------------------------------------------------

install(
    FILES
        LED/LED.h
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/qvintage/LED
)

install(
    FILES
        SEG7/SEG7.h
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/qvintage/SEG7
)

install(
    FILES
        SWITCH/SWITCH.h
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/qvintage/SWITCH
)

install(
    FILES
        SWITCH2/SWITCH2.h
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/qvintage/SWITCH2
)

# ---------------------------------------------------------------------------
# CMake package configuration
# ---------------------------------------------------------------------------

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/qvintageConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qvintageConfig.cmake"

    INSTALL_DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/qvintage"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/qvintageConfigVersion.cmake"

    VERSION
        ${PROJECT_VERSION}

    COMPATIBILITY
        SameMajorVersion
)

# ---------------------------------------------------------------------------
# Export targets
# ---------------------------------------------------------------------------

install(
    EXPORT qvintageTargets

    FILE
        qvintageTargets.cmake

    NAMESPACE
        qvintage::

    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/qvintage"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/qvintageConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/qvintageConfigVersion.cmake"

    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/qvintage"
)
