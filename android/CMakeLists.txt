cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "react-native-fast-fs")
set (BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

# Specifies a path to native header files.
include_directories(
            ../cpp
            "${NODE_MODULES_DIR}/react-native/React"
            "${NODE_MODULES_DIR}/react-native/React/Base"
            "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
)


if(${REACT_NATIVE_VERSION} LESS 66)
        set (
                INCLUDE_JSI_CPP
                "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp"
        )
endif()

add_library(reactnativefastfs  # <-- Library name
        SHARED
        "cpp-adapter.cpp"
        "../cpp/Directory.cpp"
        "../cpp/Directory.hpp"
        "../cpp/FastFilesystemModule.cpp"
        "../cpp/FastFilesystemModule.h"
        "../cpp/File.cpp"
        "../cpp/File.hpp"
        "../cpp/JSIUtils.cpp"
        "../cpp/JSIUtils.hpp"
        "../cpp/filesystem/filesystem.hpp"
        "../cpp/filesystem/fs_fwd.hpp"
        "../cpp/filesystem/fs_impl.hpp"
        "../cpp/filesystem/fs_std_fwd.hpp"
        "../cpp/filesystem/fs_std_impl.hpp"
        "../cpp/filesystem/fs_std.hpp"
        ${INCLUDE_JSI_CPP} # only on older RN versions
)

set_target_properties(
        reactnativefastfs PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

file (GLOB LIBRN_DIR "${PREBUILT_DIR}/${ANDROID_ABI}")

find_library(
        log-lib
        log
)
find_library(
        REACT_NATIVE_JNI_LIB
        reactnativejni
        PATHS ${LIBRN_DIR}
        NO_CMAKE_FIND_ROOT_PATH
)
if(${REACT_NATIVE_VERSION} LESS 66)
        # JSI lib didn't exist on RN 0.65 and before. Simply omit it.
        set (JSI_LIB "")
else()
        # RN 0.66 distributes libjsi.so, can be used instead of compiling jsi.cpp manually.
        find_library(
                JSI_LIB
                jsi
                PATHS ${LIBRN_DIR}
                NO_CMAKE_FIND_ROOT_PATH
        )
endif()

target_link_libraries(
        reactnativefastfs
        ${log-lib}
        ${JSI_LIB}
        ${REACT_NATIVE_JNI_LIB}
        android
)