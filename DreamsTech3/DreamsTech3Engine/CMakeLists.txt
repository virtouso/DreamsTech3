# CMakeList.txt : CMake project for DreamsTech3Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

 find_package(ImGui-SFML CONFIG REQUIRED)
 find_package(ImGui CONFIG REQUIRED)
  find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)


add_executable (DreamsTech3Engine "DreamsTech3Engine.cpp" "DreamsTech3Engine.h"  "Settings/GeneralSettings.h" "Settings/GeneralSettings.cpp" )

   target_link_libraries(DreamsTech3Engine PRIVATE
   ImGui-SFML::ImGui-SFML
   imgui::imgui
   sfml-system sfml-network sfml-graphics sfml-window
   )