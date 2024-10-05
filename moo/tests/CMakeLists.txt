
add_executable (mootest
    "../windows/WindowSystem.h"
    "../windows/WindowSystem.cpp"
    "../windows/TimerFactory.h"
    "../windows/TimerFactory.cpp"
    "../windows/Window.h"
    "../windows/Window.cpp"

	"WindowSubsystemTest.cpp"
    "TimerTest.cpp"
)

include_directories("../../googletest/src")
include_directories("../../googletest/googlemock/include")

enable_testing()

add_compile_definitions(GTEST_LINKED_AS_SHARED_LIBRARY)
set_property(TARGET mootest PROPERTY CXX_STANDARD 20)
target_link_libraries(mootest PRIVATE 
#    gmock gmock_main
GTest::gtest GTest::gmock_main GTest::gtest_main GTest::gmock
)

add_test(NAME    mootest 
         COMMAND mootest)