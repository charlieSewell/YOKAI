# Add source files.
target_sources(run_tests PRIVATE
		main_tests.cpp
        )

# Include project header files.
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})