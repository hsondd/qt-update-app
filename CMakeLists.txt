cmake_minimum_required(VERSION 3.16)

project(TestGithubUpdate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets Network Gui Core)

qt_standard_project_setup(REQUIRES 6.8)

file(GLOB UPDATER_SOURCES
    updater/src/*.cpp
    updater/src/impl/*.cpp
    updater/src/impl/*.h
    updater/src/sparkle/*.mm
    updater/src/sparkle/*.h
)

file(GLOB UPDATER_HEADERS
    updater/src/*.h
    updater/src/impl/*.h
    updater/src/sparkle/*.h
)

qt_add_executable(appTestGithubUpdate
    main.cpp
    src/UpdateHelper.cpp  # <--- Thêm dòng này
    src/UpdateHelper.h    # <--- Thêm dòng này
    ${UPDATER_SOURCES}
    ${UPDATER_HEADERS}
)

qt_add_qml_module(appTestGithubUpdate
    URI TestGithubUpdate
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTestGithubUpdate PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTestGithubUpdate
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# XÓA hoặc COMMENT dòng này vì updater không có CMakeLists.txt
# add_subdirectory(updater)

target_include_directories(appTestGithubUpdate PRIVATE
    src
    updater/src
    updater/src/impl
    updater/src/sparkle
)

target_link_libraries(appTestGithubUpdate
    PRIVATE Qt6::Quick Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network
)

if(APPLE)
    # 1. Tìm thư viện Sparkle trong thư mục Frameworks của dự án
    find_library(SPARKLE_FRAMEWORK Sparkle HINTS "${CMAKE_SOURCE_DIR}/Frameworks")
    
    if(SPARKLE_FRAMEWORK)
        message(STATUS "Found Sparkle: ${SPARKLE_FRAMEWORK}")
        target_link_libraries(appTestGithubUpdate PRIVATE ${SPARKLE_FRAMEWORK})
        
        # 2. Quan trọng: Đăng ký thư mục Frameworks để compiler tìm thấy header
        target_include_directories(appTestGithubUpdate PRIVATE 
            "${CMAKE_SOURCE_DIR}/Frameworks/Sparkle.framework/Headers"
        )
        
        # 3. Copy Sparkle.framework vào trong App Bundle sau khi build xong
        # (Bước này bắt buộc để app chạy được trên máy khác)
        add_custom_command(TARGET appTestGithubUpdate POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:appTestGithubUpdate>/../Frameworks
            COMMAND ${CMAKE_COMMAND} -E copy_directory
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
