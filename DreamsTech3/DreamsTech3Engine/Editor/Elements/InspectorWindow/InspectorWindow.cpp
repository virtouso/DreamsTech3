
#include "InspectorWindow.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "../../../EngineState/Manager/EngineStateManager.h"
#include "../../../GamePlay/Entity/GameObject.h"

void  InspectorWindow::Show() {


	ImGui::Begin("Inspector");

	if (EngineStateManager::getInstance()->GetSelectedObject() == nullptr)
		return;

	EngineStateManager::getInstance()->GetSelectedObject()->GetTransform()->DisplayInspector();
	for (const auto component :
	     EngineStateManager::getInstance()->GetSelectedObject()->GetComponents())
	{
		component->DisplayInspector();
	}


	ImGui::End();
}
