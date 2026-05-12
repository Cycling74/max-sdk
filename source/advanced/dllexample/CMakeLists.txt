project(dllexample)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../../../support")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

add_library(
	mydll
	SHARED
	"mydll.h"
	"mydll.cpp"
)

target_link_libraries(mydll PUBLIC Max::Max)

if (APPLE)
	target_link_options(
		mydll
		PUBLIC
		"-Wl,-U,_object_post"
		"-Wl,-install_name,@loader_path/../../../../support/mydll.dylib"
	)
endif ()

add_subdirectory(dllcounter)
add_subdirectory(dllreport)
