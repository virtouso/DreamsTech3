#
#include <string>
#include <SFML/Graphics/CircleShape.hpp>

#include "../Base/Component.h"


class ShapeRenderer :public Component
{
public:
	ShapeRenderer();
	~ShapeRenderer() override;

	void Update() override;
	std::string  GetName()  override ;
	const static	std::string Name;

private:
	float _radius;
	int _sides;

	sf::CircleShape *_circleShape;



};

