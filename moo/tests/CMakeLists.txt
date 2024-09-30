
add_executable (mootest
	gametest.cpp
)

include_directories("../../googletest/src")

enable_testing()

set_property(TARGET mootest PROPERTY CXX_STANDARD 20)
target_link_libraries(mootest PRIVATE 
    gtest gtest_main
)

add_test(NAME    mootest 
         COMMAND mootest)