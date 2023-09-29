# CMakeList.txt : CMake project for LexicalAnalyzerCpp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LexicalAnalyzerCpp "LexicalAnalyzerCpp.cpp" "LexicalAnalyzerCpp.h" "example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LexicalAnalyzerCpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
