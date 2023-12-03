#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include <functional>
#include "vector4.hpp"
#include "RFuncSprite.h"

class gpath : public sf::Sprite
{
public:

	void Create(const sf::Vector2u &size);
	void Clear();
	void FindPath(const RFuncSprite &rFuncSprite, sf::Vector2f point, sf::Color color);

private:

	sf::RenderTexture _texture;
};
