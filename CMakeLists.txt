cmake_minimum_required(VERSION 3.23)

project(kisstype LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 1)
add_compile_definitions(VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR})
add_compile_definitions(VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR})
add_compile_definitions(VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH})

find_package(Doxygen)

set(SRC_FILES
	eistype.cpp
	spectra.cpp
	strops.cpp
	spectra_c.cpp
	type_c.cpp
)

set(API_HEADERS_CPP_DIR ${PROJECT_NAME}/)

set(API_HEADERS_CPP
	${API_HEADERS_CPP_DIR}/type.h
	${API_HEADERS_CPP_DIR}/spectra.h
)

set(API_HEADERS_C_DIR ${PROJECT_NAME}/c)

set(API_HEADERS_C
	${API_HEADERS_C_DIR}/type.h
	${API_HEADERS_C_DIR}/spectra.h)

message("Platform " ${CMAKE_SYSTEM_NAME})
if(WIN32)
	message("Building on Windows")

	set(COMMON_LINK_FLAGS "-flto -dl")

	if(NOT CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/package-win.sh ${CMAKE_CURRENT_BINARY_DIR}/package.sh @ONLY)
		add_custom_target(package
			COMMAND ${CMAKE_CURRENT_BINARY_DIR}/package.sh
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Createing release archive"
			VERBATIM)
	endif()

else()
	message("Building on UNIX")

	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
	endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

	set(COMMON_LINK_FLAGS "-flto -ltbb -pthread")
endif(WIN32)

set(COMMON_COMPILE_FLAGS "-Wall -O2 -g -fPIC")

add_library(${PROJECT_NAME}_obj OBJECT ${SRC_FILES} ${API_HEADERS_CPP})
target_link_libraries(${PROJECT_NAME}_obj ${LIBS})
target_sources(${PROJECT_NAME}_obj INTERFACE FILE_SET header_set TYPE HEADERS BASE_DIRS ${API_HEADERS_CPP_DIR} FILES ${API_HEADERS_CPP})
target_sources(${PROJECT_NAME}_obj INTERFACE FILE_SET header_c_set TYPE HEADERS BASE_DIRS ${API_HEADERS_CPP_DIR} FILES ${API_HEADERS_C})
target_include_directories(${PROJECT_NAME}_obj PUBLIC ${PROJECT_NAME} .)
set_target_properties(${PROJECT_NAME}_obj PROPERTIES COMPILE_FLAGS ${COMMON_COMPILE_FLAGS} LINK_FLAGS ${COMMON_LINK_FLAGS})

add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)

configure_file(pkgconfig/lib${PROJECT_NAME}.pc.in pkgconfig/lib${PROJECT_NAME}.pc @ONLY)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(TARGETS ${PROJECT_NAME}_static DESTINATION lib)
install(TARGETS ${PROJECT_NAME} FILE_SET header_set DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} FILE_SET header_c_set DESTINATION include/${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/lib${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${PROJECT_NAME}_test main.cpp)
add_dependencies(${PROJECT_NAME}_test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test -L. -l${PROJECT_NAME}_static)
target_include_directories(${PROJECT_NAME}_test PUBLIC ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_test PROPERTIES COMPILE_FLAGS ${COMMON_COMPILE_FLAGS} LINK_FLAGS ${COMMON_LINK_FLAGS})
install(TARGETS ${PROJECT_NAME}_test DESTINATION bin)

if (DOXYGEN_FOUND)
	message("Doxygen build started")

	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM )
else (DOXYGEN_FOUND)
	message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
