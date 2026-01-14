cmake_minimum_required(VERSION 3.16)

project(TestGithubUpdate VERSION 9.6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets Network Gui Core)

qt_standard_project_setup(REQUIRES 6.8)

file(GLOB UPDATER_COMMON_SOURCES
    updater/src/*.cpp
    updater/src/impl/*.cpp
    updater/src/impl/*.h
)

file(GLOB UPDATER_COMMON_HEADERS
    updater/src/*.h
    updater/src/impl/*.h
)

set(UPDATER_SOURCES ${UPDATER_COMMON_SOURCES})
set(UPDATER_HEADERS ${UPDATER_COMMON_HEADERS})

if(APPLE)
    file(GLOB UPDATER_SPARKLE_SOURCES updater/src/sparkle/*.mm)
    file(GLOB UPDATER_SPARKLE_HEADERS updater/src/sparkle/*.h)
    list(APPEND UPDATER_SOURCES ${UPDATER_SPARKLE_SOURCES})
    list(APPEND UPDATER_HEADERS ${UPDATER_SPARKLE_HEADERS})
endif()

qt_add_executable(appTestGithubUpdate
    main.cpp
    src/UpdateHelper.cpp
    src/UpdateHelper.h 
    ${UPDATER_SOURCES}
    ${UPDATER_HEADERS}
)

target_compile_definitions(appTestGithubUpdate PRIVATE
    APP_VERSION="${PROJECT_VERSION}"
)

qt_add_qml_module(appTestGithubUpdate
    URI TestGithubUpdate
    QML_FILES
        Main.qml
)

set_target_properties(appTestGithubUpdate PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appTestGithubUpdate PRIVATE
    src
    updater/src
    updater/src/impl
)

target_link_libraries(appTestGithubUpdate
    PRIVATE Qt6::Quick Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network
)

if(APPLE)
    target_include_directories(appTestGithubUpdate PRIVATE updater/src/sparkle)
    find_library(SPARKLE_FRAMEWORK Sparkle HINTS "${CMAKE_SOURCE_DIR}/Frameworks")
    
    if(SPARKLE_FRAMEWORK)
        message(STATUS "Found Sparkle: ${SPARKLE_FRAMEWORK}")
        target_link_libraries(appTestGithubUpdate PRIVATE ${SPARKLE_FRAMEWORK})
        
        target_include_directories(appTestGithubUpdate PRIVATE 
            "${CMAKE_SOURCE_DIR}/Frameworks/Sparkle.framework/Headers"
        )
        
        add_custom_command(TARGET appTestGithubUpdate POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:appTestGithubUpdate>/../Frameworks
            COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:appTestGithubUpdate>/../Frameworks/Sparkle.framework
            COMMAND /usr/bin/ditto --rsrc --noqtn
            "${CMAKE_SOURCE_DIR}/Frameworks/Sparkle.framework"
            "$<TARGET_FILE_DIR:appTestGithubUpdate>/../Frameworks/Sparkle.framework"
        )
    else()
        message(WARNING "Sparkle framework not found! Auto-update will not work on macOS.")
    endif()
endif()

include(GNUInstallDirs)
install(TARGETS appTestGithubUpdate
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
