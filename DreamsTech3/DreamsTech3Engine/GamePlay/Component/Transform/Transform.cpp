#include "Transform.h"
#include <imgui.h>
#include <imgui-SFML.h>

const std::string  Transform::Name = "Transform";


Transform::Transform(GameObject& gameObject) : Component(gameObject)
{

}


std::string Transform::GetName()
{
	return Transform::Name;
}

void Transform::Update()
{

}



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

void Transform::Rotate(float amount)
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



void Transform::DisplayInspector()
{
	ImGui::Text("Position");
	ImGui::SameLine();
	if(ImGui::Button("<")){}
	ImGui::SameLine();
	ImGui::Text( std::to_string( _position.x).c_str());
	ImGui::SameLine();
	if(ImGui::Button(">")){}

	ImGui::SameLine();
	if (ImGui::Button("<")) {}
	ImGui::SameLine();
	ImGui::Text(std::to_string(_position.y).c_str());
	ImGui::SameLine();
	if (ImGui::Button(">")) {}




}
