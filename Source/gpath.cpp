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


void gpath::FindPath(const RFuncSprite &rFuncSprite, sf::Vector2f point_old, sf::Color pathColor, const int descent)
{
	static const float step = 10;

	sf::Vector2u point;
	point.x = static_cast<unsigned>(point_old.x);
	point.y = static_cast<unsigned>(point_old.y);

	// –азмеры матрицы (можно настроить в соответствии с вашими нуждами)
	const unsigned int MATRIX_SIZE_X = _texture.getSize().x;
	const unsigned int MATRIX_SIZE_Y = _texture.getSize().y;

	// ќпределение матрицы
	std::vector<std::vector<bool>> matrix(MATRIX_SIZE_X, std::vector<bool>(MATRIX_SIZE_Y, false));

	while (true)
	{
		
		if (point.x < 0 || point.y < 0 || point.x >= MATRIX_SIZE_X || point.y >= MATRIX_SIZE_Y)
			break;
		if (matrix[point.x][point.y])
			break;
			
		matrix[point.x][point.y] = true;

		float cx = rFuncSprite.cx()[point.x][point.y];
		float cy = rFuncSprite.cy()[point.x][point.y];

		sf::RectangleShape rect({2, 2});
		rect.setFillColor(pathColor);
		rect.setPosition(point.x, _texture.getSize().y - point.y);
		_texture.draw(rect);
		
		point.x += static_cast<unsigned>(descent * step * cx);
		point.y += static_cast<unsigned>(descent * step * cy);
	}	

}

