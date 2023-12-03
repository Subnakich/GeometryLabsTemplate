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

	const std::vector<std::vector<float>> &cx() const { return _cx; }
	const std::vector<std::vector<float>> &cy() const { return _cy; }

private:
	
	std::vector<std::vector<float>> _cx;
	std::vector<std::vector<float>> _cy;

	vector4s::Vector4f getVector(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace,
								 const unsigned int x, const unsigned int y);

	sf::Vector3f getSpacePoint(const std::function<float(const sf::Vector2f &)> &rfunc,
									 const sf::FloatRect &subSpace,
							   float x, float y);

	sf::Texture _texture;
	sf::Image _image;
};
