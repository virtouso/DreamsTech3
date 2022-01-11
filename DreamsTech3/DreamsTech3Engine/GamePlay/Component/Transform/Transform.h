#pragma once
#include "../../Component/Base/Component.h"
#include "imgui-SFML.h"

class Transform :Component
{
public:
	void SetPosition(sf::Vector2f position);
	void Move(sf::Vector2f direction);
	sf::Vector2f GetPosition() const;



	void SetRotation(float rotation);
	void Rotate(float amount);
	float GetRotation() const;



	void SetScale(sf::Vector2f scale);
	void Scale(sf::Vector2f amount);
	sf::Vector2f GetScale() const;

private:
	sf::Vector2f _position;
	float _rotation;
	sf::Vector2f _scale;

};

