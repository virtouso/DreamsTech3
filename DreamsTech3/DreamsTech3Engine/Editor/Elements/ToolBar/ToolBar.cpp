#include "ToolBar.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "../../EditorSettings/EditorSettings.h"
#include "../../EditorReferences/EditorReferences.h"

static sf::Texture* _playIconTexture;
static sf::Texture* _stopIconTexture;
static sf::Sprite* _currentPlayStateSprite;


ToolBar::ToolBar()
{
	_playIconTexture = new sf::Texture();
	_playIconTexture->loadFromFile(EditorReferences::TransformIcon);
}
ToolBar::~ToolBar()
{
	delete _playIconTexture;
	delete _stopIconTexture;
	delete _currentPlayStateSprite;
}

void ToolBar::Show()
{

	ImGui::Begin("Controlls");
	ImGui::ImageButton(*_playIconTexture,sf::Vector2f(EditorSettings::ToolBarIconsWidth,EditorSettings::ToolBarIconsHeight));
	ImGui::End();
}