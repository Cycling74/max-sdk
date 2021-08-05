project(dllexample)

if (NOT DEFINED C74_SUPPORT_DIR)
	set(C74_SUPPORT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../max-sdk-base/c74support)
endif ()

message(STATUS ${C74_SUPPORT_DIR})

set(MAX_SDK_INCLUDES "${C74_SUPPORT_DIR}/max-includes")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../../../support")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

if (APPLE)
	if (CMAKE_OSX_ARCHITECTURES STREQUAL "")
		set(CMAKE_OSX_ARCHITECTURES x86_64)
	endif()
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "Minimum OS X deployment version" FORCE)
endif ()

add_library( 
	mydll
	SHARED
	"mydll.h"
	"mydll.cpp"
)

target_include_directories( 
	mydll
	PUBLIC
	"${MAX_SDK_INCLUDES}"
)

if (APPLE)
	target_link_options(
		mydll
		PUBLIC
		"-Wl,-U,_object_post"
		"-Wl,-install_name,@loader_path/../../../../support/mydll.dylib"
	)
else ()
	target_link_libraries(mydll PUBLIC ${MAX_SDK_INCLUDES}/x64/MaxAPI.lib)
endif ()

# Generate a project for every folder in the "source/category" folder
SUBDIRLIST(PROJECT_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach (project_dir ${PROJECT_DIRS})
	set(project_path ${CMAKE_CURRENT_SOURCE_DIR}/${project_dir})
	message("checking in: ${project_path}")
	if (EXISTS "${project_path}/CMakeLists.txt")
		message("Generating: ${project_dir}")
		add_subdirectory(${project_path})
	endif ()
endforeach ()
