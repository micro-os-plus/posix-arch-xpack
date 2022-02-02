#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# This Source Code Form is subject to the terms of the MIT License.
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# https://cmake.org/cmake/help/v3.20/
# https://cmake.org/cmake/help/v3.20/manual/cmake-packages.7.html#package-configuration-file
cmake_minimum_required(VERSION 3.20)

# Use targets as include markers (variables are not scope independent).
if(TARGET micro-os-plus-architecture-synthetic-posix-included)
  return()
else()
  add_custom_target(micro-os-plus-architecture-synthetic-posix-included)
endif()

if(NOT TARGET micro-os-plus-build-helper-included)
  message(FATAL_ERROR "Include the mandatory build-helper (xpacks/micro-os-plus-build-helper/cmake/xpack-helper.cmake)")
endif()

message(STATUS "Processing xPack ${PACKAGE_JSON_NAME}@${PACKAGE_JSON_VERSION}...")

# -----------------------------------------------------------------------------
# Local dependencies.

if(MICRO_OS_PLUS_INCLUDE_RTOS)
include("${CMAKE_CURRENT_LIST_DIR}/../rtos-port/meta/config.cmake")
endif()

# -----------------------------------------------------------------------------
# The current folder.

get_filename_component(xpack_current_folder ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# -----------------------------------------------------------------------------

if(NOT TARGET micro-os-plus-architecture-synthetic-posix-interface)

# -----------------------------------------------------------------------------
## The project library definitions ##

# https://cmake.org/cmake/help/v3.20/command/add_library.html?highlight=interface#normal-libraries
# PRIVATE: build definitions, used internally
# INTERFACE: usage definitions, passed up to targets linking to it
# PUBLIC: both

add_library(micro-os-plus-architecture-synthetic-posix-interface INTERFACE EXCLUDE_FROM_ALL)

# -----------------------------------------------------------------------------
# Target settings.

  xpack_glob_recurse_cxx(source_files "${xpack_current_folder}/src")
  xpack_display_relative_paths("${source_files}" "${xpack_current_folder}")

  target_sources(
    micro-os-plus-architecture-synthetic-posix-interface

    INTERFACE
      ${source_files}
  )

  target_include_directories(
    micro-os-plus-architecture-synthetic-posix-interface

    INTERFACE
      ${xpack_current_folder}/include
  )

  target_compile_definitions(
    micro-os-plus-architecture-synthetic-posix-interface

    INTERFACE
      _XOPEN_SOURCE=700L
  )

# -----------------------------------------------------------------------------
  # Aliases.

  add_library(micro-os-plus::architecture-synthetic-posix ALIAS micro-os-plus-architecture-synthetic-posix-interface)
  # message(STATUS "=> micro-os-plus::architecture-synthetic-posix")
  add_library(micro-os-plus::architecture ALIAS micro-os-plus-architecture-synthetic-posix-interface)
  message(STATUS "=> micro-os-plus::architecture")

endif()

# -----------------------------------------------------------------------------
