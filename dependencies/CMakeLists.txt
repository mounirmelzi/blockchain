set(CRYPTOPP_BUILD_TESTING OFF CACHE BOOL "Disable tests")
set(CRYPTOPP_BUILD_DOCUMENTATION OFF CACHE BOOL "Disable docs")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Static build")
add_subdirectory("cryptopp")
