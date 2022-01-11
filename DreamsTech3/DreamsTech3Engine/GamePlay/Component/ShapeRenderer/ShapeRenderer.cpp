#include "ShapeRenderer.h"

#include <iostream>

#include "../../../Global/GlobalObjects.h"
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Entity/GameObject.h"

const std::string  ShapeRenderer::Name = "ShapeRenderer";


std::string ShapeRenderer::GetName()
{
	return ShapeRenderer::Name;
}

ShapeRenderer::ShapeRenderer(GameObject& gameObject) : Component(gameObject), _radius(10), _sides(5),
_circleShape(new sf::CircleShape(_radius))
{
	_circleShape->setFillColor(sf::Color::Red);
	_circleShape->setOutlineColor(sf::Color::Blue);
	_circleShape->setOutlineThickness(10);
	_circleShape->setRadius(100);
	_circleShape->setPosition(_parentGameObject.GetTransform()->GetPosition().x, _parentGameObject.GetTransform()->GetPosition().y);
}

void ShapeRenderer::Update()
{
	
	GlobalObjects::window->draw(*_circleShape);
}

ShapeRenderer::~ShapeRenderer()
{
	delete _circleShape;
}



