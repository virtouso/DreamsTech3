#include "ShapeRenderer.h"

#include <string>


const std::string  ShapeRenderer::Name = "ShapeRenderer";


 std::string ShapeRenderer::GetName()
{
	return ShapeRenderer::Name ;
}

 ShapeRenderer::ShapeRenderer():_radius(10),_sides(5),
                                                       _circleShape(new sf::CircleShape(_radius))
 {
	 _circleShape->setFillColor(sf::Color::Transparent);
	 _circleShape->setOutlineColor(sf::Color::Black);

 }

void ShapeRenderer::Update()
{
	
}

ShapeRenderer::~ShapeRenderer()
 {
	delete _circleShape;
 }



