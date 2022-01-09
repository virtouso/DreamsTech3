# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)



project ("DreamsTech3")

# Include sub-projects.
add_subdirectory ("DreamsTech3Engine")
add_subdirectory ("TestGame")

