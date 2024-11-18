cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME ChessGame)

set(SOURCE_FOLDER src)
set(INCLUDE_FOLDER include)
set(DEPENDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
add_definitions(-DPROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")
add_definitions(-DASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
add_definitions(-DTEXTURE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/textures/")

project(${PROJECT_NAME} LANGUAGES CXX)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

file(GLOB_RECURSE HEADER_FILES
${INCLUDE_FOLDER}/*.hpp
${INCLUDE_FOLDER}/*.h)

file(GLOB_RECURSE SOURCE_FILES
${SOURCE_FOLDER}/*.cpp
${SOURCE_FOLDER}/*.c)

foreach(SOURCE_FILE ${SOURCE_FILES})
    file(RELATIVE_PATH RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER} ${SOURCE_FILE})
    string(REPLACE "\\" "/" GROUP_NAME ${RELATIVE_PATH})
	get_filename_component(GROUP_NAME ${GROUP_NAME} DIRECTORY)
	if (GROUP_NAME STREQUAL "")
		source_group("Source Files" FILES ${SOURCE_FILE})
		break()
    endif()
    source_group("Source Files\\${GROUP_NAME}" FILES ${SOURCE_FILE})
endforeach()

foreach(HEADER_FILE ${HEADER_FILES})
    file(RELATIVE_PATH RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_FOLDER} ${HEADER_FILE})
    string(REPLACE "\\" "/" GROUP_NAME ${RELATIVE_PATH})
	get_filename_component(GROUP_NAME ${GROUP_NAME} DIRECTORY)
	if (GROUP_NAME STREQUAL "")
        source_group("Header Files" FILES ${HEADER_FILE})
		break()
    endif()
    source_group("Header Files\\${GROUP_NAME}" FILES ${HEADER_FILE})
endforeach()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_FOLDER})
add_compile_options(/Zc:__cplusplus)

#Adding SFML
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()