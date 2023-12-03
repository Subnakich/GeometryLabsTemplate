#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"

#include <functional>
#include "vector4.hpp"

class RFuncSprite : public sf::Sprite
{
public:
	void Create(const sf::Vector2u &size);

	void DrawRFunc(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace,
				   const int mode, const sf::Color color);

	void SaveToFile(const std::string &str);

private:

	vector4s::Vector4f getPvVector(float a, float b, float c, float d);

	sf::Vector3f getSpacePoint(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace,
							   float x, float y);

	sf::Texture _texture;
	sf::Image _image;
};
