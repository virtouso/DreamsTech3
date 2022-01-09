#include "EditorManager.h"
#include "../Elements/InspectorWindow/InspectorWindow.h"
#include "../Elements/TopBar/TopBar.h"


EditorManager::EditorManager()
{
	EditorManager::MainElements = new std::vector<IEditorElement*>(2);

	InspectorWindow* inspectorWindow = new InspectorWindow();
	EditorManager::MainElements->emplace_back(inspectorWindow);

	TopBar* topBar = new TopBar();
	EditorManager::MainElements->emplace_back(topBar);



}

EditorManager::~EditorManager()
{

	EditorManager::MainElements->clear();// it doesnt free the space. find a way
}


void EditorManager::Show()
{
	for (auto it : *EditorManager::MainElements)
	{
		if (it != nullptr)
			it->Show();
	}

}
