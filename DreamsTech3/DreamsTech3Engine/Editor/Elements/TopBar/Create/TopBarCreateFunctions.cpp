#include  "TopBarCreateFunctions.h"
#include "../../../../GamePlay/Entity/GameObject.h"
#include "../../../../GamePlay/Component/Base/Component.h"
#include "../../../../GamePlay/Component/ShapeRenderer/ShapeRenderer.h"
#include "../../../../EngineState/Manager/EngineStateManager.h"

void TopBarCreateFunctions::CreateDefaultShapeRendererObject()
{
	std::cout << "gimmi";
	GameObject* gameObject = new GameObject("GameObject");
	gameObject->GetTransform()->SetPosition(sf::Vector2f(100,100));

	ShapeRenderer* shapeRenderer = new ShapeRenderer(*gameObject);
	gameObject->AddComponent(shapeRenderer);

	EngineStateManager::getInstance()->AddObjectToScene(gameObject);

	EngineStateManager::getInstance()->  SetSelectedObject(*gameObject);

}
