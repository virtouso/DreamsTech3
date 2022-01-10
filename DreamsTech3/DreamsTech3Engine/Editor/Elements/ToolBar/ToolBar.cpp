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

static sf::Texture* _transformTexture;
static sf::Texture*  _rotateTexture;
static sf::Texture* _scaleTexture;


static sf::Texture* _gridTexture;
static sf::Texture* _snapGridTexture;


ToolBar::ToolBar()
{
	_playIconTexture = new sf::Texture();
	_playIconTexture->loadFromFile(EditorReferences::PlayIcon);

	_stopIconTexture = new sf::Texture();
	_stopIconTexture->loadFromFile(EditorReferences::StopIcon);

	_transformTexture = new sf::Texture();
	_transformTexture->loadFromFile(EditorReferences::TransformIcon);

	_rotateTexture = new sf::Texture();
	_rotateTexture->loadFromFile(EditorReferences::RotateIcon);

	_scaleTexture = new sf::Texture();
	_scaleTexture->loadFromFile(EditorReferences::ScaleIcon);

	_gridTexture = new sf::Texture();
	_gridTexture->loadFromFile(EditorReferences::GridIcon);

	_snapGridTexture = new sf::Texture();
	_snapGridTexture ->loadFromFile(EditorReferences::SnapGridIcon);
}
ToolBar::~ToolBar()
{
	delete _playIconTexture;
	delete _stopIconTexture;
	delete _currentPlayStateSprite;

	delete _transformTexture;
	delete  _rotateTexture;
	delete _scaleTexture;

	delete _gridTexture;
	delete _snapGridTexture;


}

void ToolBar::Show()
{
	
	
	ImGui::BeginGroup();
	ImGui::SameLine();
	ImGui::ImageButton(*_transformTexture, sf::Vector2f(EditorSettings::ToolBarIconsWidth, EditorSettings::ToolBarIconsHeight));
	ImGui::SameLine();
	ImGui::ImageButton(*_rotateTexture, sf::Vector2f(EditorSettings::ToolBarIconsWidth, EditorSettings::ToolBarIconsHeight));
	ImGui::SameLine();
	ImGui::ImageButton(*_scaleTexture, sf::Vector2f(EditorSettings::ToolBarIconsWidth, EditorSettings::ToolBarIconsHeight));
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(200,0));
	ImGui::SameLine();
	ImGui::ImageButton(*_gridTexture,sf::Vector2f(EditorSettings::ToolBarIconsWidth,EditorSettings::ToolBarIconsHeight));
	ImGui::SameLine();
	ImGui::ImageButton(*_snapGridTexture, sf::Vector2f(EditorSettings::ToolBarIconsWidth, EditorSettings::ToolBarIconsHeight));
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(400, 0));
	ImGui::SameLine();
	ImGui::ImageButton(*_playIconTexture, sf::Vector2f(EditorSettings::ToolBarIconsWidth, EditorSettings::ToolBarIconsHeight));

	ImGui::EndGroup();

}