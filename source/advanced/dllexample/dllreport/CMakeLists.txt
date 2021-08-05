include(${CMAKE_CURRENT_SOURCE_DIR}/../../../max-sdk-base/script/max-pretarget.cmake)

#############################################################
# MAX EXTERNAL
#############################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../externals")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

include_directories( 
	"${MAX_SDK_INCLUDES}"
	"${MAX_SDK_MSP_INCLUDES}"
	"${MAX_SDK_JIT_INCLUDES}"
	".."
)

file(GLOB PROJECT_SRC
     "../*.h"
     "*.h"
	"*.c"
     "*.cpp"
)

add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_SRC}
)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
	mydll # add project to ensure that it's a dependency
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../../max-sdk-base/script/max-posttarget.cmake)
