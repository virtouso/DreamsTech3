#include "EditBar.h"

#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"


static sf::Texture* _playIconTexture;
static sf::Texture* _stopIconTexture;
static sf::Sprite* _currentPlayStateSprite;


EditBar::EditBar()
{
	_playIconTexture = new sf::Texture();
	_playIconTexture->loadFromFile("Icons/small/_Help.png");

}
EditBar::~EditBar()
{
	delete _playIconTexture;
	delete _stopIconTexture;
	delete _currentPlayStateSprite;
}

void EditBar::Show()
{
//	ImGui::DrawRectFilled(sf::FloatRect(0,10,ImGui::GetWindowWidth(),10 ),sf::Color::Blue );
	//ImGui::DrawRect(sf::FloatRect(0, 10, ImGui::GetWindowWidth(), 10), sf::Color::Blue);
	ImGui::Begin("Controlls");
	ImGui::ImageButton(*_playIconTexture);
	ImGui::End();
}