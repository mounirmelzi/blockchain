cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(
	"blockchain" 
	VERSION 1.0.0
	DESCRIPTION "blockchain implementation from scratch"
	LANGUAGES CXX
)

set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS ON)
set_property(GLOBAL PROPERTY LINKER_LANGUAGE CXX)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE -Wall)
target_compile_features(project_options INTERFACE cxx_std_20)
target_include_directories(project_options INTERFACE ${PROJECT_SOURCE_DIR})

add_subdirectory("dependencies")
add_subdirectory ("blockchain")
