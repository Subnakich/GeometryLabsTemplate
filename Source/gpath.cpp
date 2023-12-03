#include "gpath.h"

static float step = 10.f;

void gpath::Create(const sf::Vector2u &size) 
{
	_texture.create(size.x, size.y);
	setTexture(_texture.getTexture());
}

void gpath::Clear() 
{ 
	_texture.clear(sf::Color::Transparent); 
}

void gpath::FindPath(const RFuncSprite &rFuncSprite, sf::Vector2f point_old, sf::Color pathColor)
{
	static const float step = 10;

	sf::Vector2u point;
	point.x = static_cast<unsigned>(point_old.x);
	point.y = static_cast<unsigned>(point_old.y);

	while (true)
	{
		if (point.x < 0 || point.y < 0 || point.x >= _texture.getSize().x || point.y >= _texture.getSize().y)
			break;

		float cx = rFuncSprite.cx()[point.x][point.y];
		float cy = rFuncSprite.cy()[point.x][point.y];

		point.x += static_cast<unsigned>(step * cx);
		point.y += static_cast<unsigned>(step * cy);
	
		sf::RectangleShape rect({2, 2});
		rect.setFillColor(pathColor);
		rect.setPosition(point.x, point.y);
		_texture.draw(rect);
	}	
}

