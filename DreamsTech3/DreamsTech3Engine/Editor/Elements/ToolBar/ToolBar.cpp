#include "ToolBar.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "../../EditorSettings/EditorSettings.h"

static sf::Texture* _playIconTexture;
static sf::Texture* _stopIconTexture;
static sf::Sprite* _currentPlayStateSprite;


ToolBar::ToolBar()
{
	_playIconTexture = new sf::Texture();
	_playIconTexture->loadFromFile("Icons/small/_Help.png");

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