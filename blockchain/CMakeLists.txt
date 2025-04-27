include_directories("include")
file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(blockchain ${SOURCE_FILES})
target_link_libraries(blockchain PRIVATE project_options cryptopp)
