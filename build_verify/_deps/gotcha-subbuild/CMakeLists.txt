# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.24.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(gotcha-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[/usr/tce/bin/git]==])
set(GIT_VERSION_STRING [==[2.29.1]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[/usr/tce/bin/git;2.29.1]==]
)


include(ExternalProject)
ExternalProject_Add(gotcha-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/LLNL/GOTCHA.git" "GIT_TAG" "v1.0.10" "GIT_SHALLOW" "FALSE" "GIT_SUBMODULES" "GIT_SUBMODULES_RECURSE" "OFF"
                    SOURCE_DIR          "/usr/workspace/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-src"
                    BINARY_DIR          "/usr/workspace/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


