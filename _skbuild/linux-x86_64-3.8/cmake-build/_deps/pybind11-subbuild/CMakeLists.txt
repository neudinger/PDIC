# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.21.1)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(pybind11-populate NONE)



include(ExternalProject)
ExternalProject_Add(pybind11-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/pybind/pybind11/archive/refs/tags/v2.7.1.tar.gz"
                    SOURCE_DIR          "/media/kbarre/1d7f0a7c-34d5-4837-ad9a-95be3ec8cb53/Documents/dev/desciptor/pdic/_skbuild/linux-x86_64-3.8/cmake-build/_deps/pybind11-src"
                    BINARY_DIR          "/media/kbarre/1d7f0a7c-34d5-4837-ad9a-95be3ec8cb53/Documents/dev/desciptor/pdic/_skbuild/linux-x86_64-3.8/cmake-build/_deps/pybind11-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


