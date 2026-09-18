find_package(raylib REQUIRED)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.c")

foreach(SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${SOURCE} NAME_WE)
    
    # Create executable for each test file
    add_executable(${TEST_NAME} ${SOURCE})
    
    # Link test binary against your library AND raylib
    target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME} raylib)
    
    # Output test executables to build/bin/
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endforeach()
