#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"

#include <functional>


class RFuncSprite : public sf::Sprite
{
public:
	void Create(const sf::Vector2u &size);

	void DrawRFunc(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace);

	sf::Vector3f getSpacePoint(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace,
							   float x, float y);

private:
	sf::Texture _texture;
	sf::Image _image;
};
