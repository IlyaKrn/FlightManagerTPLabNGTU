project(tests)

install(
        DIRECTORY /
        DESTINATION ${CMAKE_BINARY_DIR}/tests
        FILES_MATCHING PATTERN "*.py"
)
include(FindPythonInterp)
add_test(NAME TestExecutableRunning COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/tests/test1.py)
