# Copyright 2018 The Max-API Authors. All rights reserved.
# Use of this source code is governed by the MIT License found in the License.md file.

cmake_minimum_required(VERSION 3.19)

string(REGEX REPLACE "(.*)/" "" THIS_FOLDER_NAME "${CMAKE_CURRENT_SOURCE_DIR}")
project(${THIS_FOLDER_NAME})

set(GIT_VERSION_MAJ 0)
set(GIT_VERSION_MIN 0)
set(GIT_VERSION_SUB 0)
# Set version variables based on the current Git tag
include("${CMAKE_CURRENT_LIST_DIR}/git-rev.cmake")

set(ADD_VERINFO YES)

# Update package-info.json, if present
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/package-info.json.in")
	set(C74_PACKAGE_NAME "${THIS_FOLDER_NAME}")
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/package-info.json.in" "${CMAKE_CURRENT_SOURCE_DIR}/package-info.json" @ONLY)

	message("Reading ${CMAKE_CURRENT_SOURCE_DIR}/package-info.json")
	
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/package-info.json" PKGINFOFILE)

	string(JSON AUTHOR GET ${PKGINFOFILE} "author")

	string(JSON PACKAGE_VERSION ERROR_VARIABLE PKG_ERROR GET ${PKGINFOFILE} "version")
	if (PACKAGE_VERSION MATCHES "-NOTFOUND")
		set(PACKAGE_VERSION "${GIT_VERSION_MAJ}.${GIT_VERSION_MIN}.${GIT_VERSION_SUB}")
	endif ()
	
	string(JSON PKG_EXTRA_STR ERROR_VARIABLE PKG_ERROR GET ${PKGINFOFILE} "package_extra")

	string(JSON AUTHOR_DOMAIN ERROR_VARIABLE PKG_ERROR GET ${PKG_EXTRA_STR} "reverse_domain")
	if (AUTHOR_DOMAIN MATCHES "-NOTFOUND")
		set(AUTHOR_DOMAIN "com.acme")
	endif ()

	string(JSON COPYRIGHT_STRING ERROR_VARIABLE PKG_ERROR GET ${PKG_EXTRA_STR} "copyright")
	if (COPYRIGHT_STRING MATCHES "-NOTFOUND")
		set(COPYRIGHT_STRING "Copyright (c) 1974 Acme Inc")
	endif ()

	string(JSON ADD_VERINFO_STR ERROR_VARIABLE PKG_ERROR GET ${PKG_EXTRA_STR} "add_verinfo")
	if (NOT ADD_VERINFO_STR MATCHES "-NOTFOUND" AND NOT ADD_VERINFO_STR STREQUAL true)
		set(ADD_VERINFO NO)
	endif ()

	string(JSON EXCLUDE_FROM_COLLECTIVES ERROR_VARIABLE PKG_ERROR GET ${PKG_EXTRA_STR} "exclude_from_collectives")
	if (EXCLUDE_FROM_COLLECTIVES MATCHES "-NOTFOUND")
		set(EXCLUDE_FROM_COLLECTIVES "no")
	endif ()

	message("Building _____ ${PACKAGE_VERSION} _____")
endif ()


# Copy PkgInfo and update Info.plist files on the Mac
if (APPLE)
	message("Generating Info.plist")
	
	set(BUNDLE_IDENTIFIER "\${PRODUCT_NAME:rfc1034identifier}")
	#configure_file("${CMAKE_CURRENT_LIST_DIR}/Info.plist.in" "${CMAKE_CURRENT_LIST_DIR}/Info.plist" @ONLY)
endif ()

if (WIN32 AND ADD_VERINFO)
	message("Generating verinfo.rc")

	string(REPLACE "." "," PACKAGE_VERSION ${PACKAGE_VERSION})
	configure_file("${CMAKE_CURRENT_LIST_DIR}/verinfo.rc.in" "${CMAKE_CURRENT_LIST_DIR}/verinfo.rc" @ONLY)
endif()

# Macro from http://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

