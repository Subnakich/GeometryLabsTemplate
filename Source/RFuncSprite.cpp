#include "RFuncSprite.h"


void RFuncSprite::Create(const sf::Vector2u &size)
{
	_image.create(size.x, size.y, sf::Color::Cyan);
	_texture.loadFromImage(_image);
	setTexture(_texture);
}

void RFuncSprite::DrawRFunc(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace) 
{
	for (unsigned x = 0; x < _image.getSize().x; ++x)
	{
		for (unsigned y = 0; y < _image.getSize().y; ++y)
		{
			sf::Vector3f spacePoint1 = getSpacePoint(rfunc, subSpace, x, y);
			sf::Vector3f spacePoint2 = getSpacePoint(rfunc, subSpace, x + 1, y);
			sf::Vector3f spacePoint3 = getSpacePoint(rfunc, subSpace, x, y + 1);

			
			
			_image.setPixel(x, y, sf::Color::Red);
		}
	}
	_texture.loadFromImage(_image);
}

sf::Vector3f RFuncSprite::getSpacePoint(const std::function<float(const sf::Vector2f &)> &rfunc,
										const sf::FloatRect &subSpace, float x, float y)
{
	sf::Vector2f spaceStep = {
		subSpace.width / static_cast<float>(_image.getSize().x),
		subSpace.height / static_cast<float>(_image.getSize().y),
	};
	sf::Vector2f spacePoint = {
		subSpace.left + static_cast<float>(x) * spaceStep.x,
		subSpace.top + static_cast<float>(y) * spaceStep.y,
	};
	const float z = rfunc(spacePoint);
	if (z > 0)
		_image.setPixel(x, y, sf::Color::Red);
	else
		_image.setPixel(x, y, sf::Color::Black);

	return sf::Vector3f(spacePoint.x, spacePoint.y, z);
}
