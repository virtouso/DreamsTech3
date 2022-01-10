#include "Transform.h"

sf::Vector2f Transform::GetPosition() const
{
	return _position;
}

float Transform::GetRotation() const
{
	return _rotation;
}


sf::Vector2f Transform::GetScale() const
{
	return _scale;
}

void Transform::Move(sf::Vector2f direction)
{
	_position += direction;
}

void Transform::Rotate( float amount)
{
	_rotation += amount;
	
}


void Transform::Scale(sf::Vector2f amount)
{
	_scale += amount;
}

void Transform::SetPosition(sf::Vector2f position)
{
	_position = position;
}


void Transform::SetRotation(float rotation)
{
	_rotation = rotation;
}


void Transform::SetScale(sf::Vector2f scale)
{
	_scale = scale;
}



