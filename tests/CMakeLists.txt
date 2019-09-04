
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

add_executable(test_validation test_validation.cpp)
target_compile_features(test_validation PRIVATE cxx_std_17)
target_link_libraries(test_validation PRIVATE cpp_util Catch2::Catch2)
add_test(NAME test_validation COMMAND test_validation)

add_executable(test_algorithm test_algorithm.cpp)
target_compile_definitions(test_algorithm PRIVATE cxx_std_17)
target_link_libraries(test_algorithm PRIVATE cpp_util Catch2::Catch2)
add_test(NAME test_algorithm COMMAND test_algorithm)
