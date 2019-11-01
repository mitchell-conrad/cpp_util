
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${cpp_util_SOURCE_DIR}/include/cpp_util/*.hpp")

# Make an automatic library - will be static or dynamic based on user setting
#add_library(cpp_util
#        ${HEADER_LIST})

# We need this directory, and users of our library will need it too
#target_include_directories(cpp_util PUBLIC ../include)

# All users of this library will need at least C++17
#target_compile_features(cpp_util PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
