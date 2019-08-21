
# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)
# Adds Catch2::Catch2

add_executable(test_string test_string.cpp)
target_compile_features(test_string PRIVATE cxx_std_17)
target_link_libraries(test_string PRIVATE cpp_util Catch2::Catch2)
add_test(NAME test_string COMMAND test_string)

add_executable(test_predicate test_predicate.cpp)
target_compile_features(test_predicate PRIVATE cxx_std_17)
target_link_libraries(test_predicate PRIVATE cpp_util Catch2::Catch2)
add_test(NAME test_predicate COMMAND test_predicate)
