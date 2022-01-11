# CMakeList.txt : CMake project for DreamsTech3Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

 find_package(ImGui-SFML CONFIG REQUIRED)
 find_package(ImGui CONFIG REQUIRED)
  find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)


add_executable (DreamsTech3Engine "DreamsTech3Engine.cpp" "DreamsTech3Engine.h"  "Settings/GeneralSettings.h" "Settings/GeneralSettings.cpp"  "Editor/Manager/EditorManager.h" "Editor/Manager/EditorManager.cpp" "Editor/Elements/InspectorWindow/InspectorWindow.cpp" "Editor/Elements/InspectorWindow/InspectorWindow.h" "Editor/Elements/TopBar/TopBar.h" "Editor/Elements/TopBar/TopBar.cpp" "Editor/Elements/ToolBar/ToolBar.h" "Editor/Elements/ToolBar/ToolBar.cpp" "Editor/EditorReferences/EditorReferences.cpp" "GamePlay/Entity/Object.h" "GamePlay/Entity/Object.cpp" "GamePlay/Entity/GameObject.h" "GamePlay/Entity/GameObject.cpp" "GamePlay/Component/ShapeRenderer/ShapeRenderer.h" "GamePlay/Component/ShapeRenderer/ShapeRenderer.cpp" "GamePlay/Component/RigidBody/RigidBody.h" "GamePlay/Component/RigidBody/RigidBody.cpp" "GamePlay/Component/Particle/Particle.h" "GamePlay/Component/Particle/Particle.cpp" "GamePlay/Component/Collider/BoxCollider.h" "GamePlay/Component/Collider/BoxCollider.cpp" "GamePlay/Component/Collider/CircleCollider.h" "GamePlay/Component/Collider/CircleCollider.cpp" "FileSystem/FileSystem.h" "FileSystem/FileSystem.cpp" "EngineState/References/EngineStateReferences.h" "EngineState/References/EngineStateReferences.cpp" "EngineState/Manager/EngineStateManager.cpp" "EngineState/Manager/EngineStateManager.h" "Enums/EngineModes.h" "Global/GlobalObjects.h" "GamePlay/Component/Base/Component.cpp" "Global/GlobalObjects.cpp" "GamePlay/Component/Transform/Transform.h" "GamePlay/Component/Transform/Transform.cpp" "GamePlay/Component/Base/Component.fwd.h" "GamePlay/Entity/GameObject.fwd.h" "Editor/Elements/TopBar/Create/TopBarCreateFunctions.h" "Editor/Elements/TopBar/Create/TopBarCreateFunctions.cpp")

   target_link_libraries(DreamsTech3Engine PRIVATE
   ImGui-SFML::ImGui-SFML
   imgui::imgui
   sfml-system sfml-network sfml-graphics sfml-window
   )