#include "RFuncSprite.h"


void RFuncSprite::Create(const sf::Vector2u &size)
{
	_cx = std::vector<std::vector<float>>(size.x, std::vector<float>(size.y, 0));
	_cy = std::vector<std::vector<float>>(size.x, std::vector<float>(size.y, 0));

	_image.create(size.x, size.y, sf::Color::Cyan);
	_texture.loadFromImage(_image);
	setTexture(_texture);
}

void RFuncSprite::SaveToFile(const std::string &str) { 
	_image.saveToFile(str + ".jpg");
}

vector4s::Vector4f RFuncSprite::getVector(const std::function<float(const sf::Vector2f &)> &rfunc,
										  const sf::FloatRect &subSpace, const unsigned int x,
										  const unsigned int y)
{ 
	sf::Vector3f point1 = getSpacePoint(rfunc, subSpace, x, y);
	sf::Vector3f point2 = getSpacePoint(rfunc, subSpace, x + 1, y);
	sf::Vector3f point3 = getSpacePoint(rfunc, subSpace, x, y + 1);
	float a = ((point2.y * point3.z - point2.z * point3.y) - (point1.y * point3.z - point1.z * point3.y) + (point1.y * point2.z - point1.z * point2.y));
	float b = -((point2.x * point3.z - point2.z * point3.x) - (point1.x * point3.z - point1.z * point3.x) + (point1.x * point2.z - point1.z * point2.x));
	float c = ((point2.x * point3.y - point2.y * point3.x) - (point1.x * point3.y - point1.y * point3.x) + (point1.x * point2.y - point1.y * point2.x));
	float d = -(point1.z * (point2.x * point3.y - point2.y * point3.x) - point2.z * (point1.x * point3.y - point1.y * point3.x) +
				point3.z * (point1.x * point2.y - point1.y * point2.x));

	float len = sqrt(a * a + b * b + c * c + d * d);

	float nx = a / len;
	float ny = b / len;
	float nz = c / len;
	float nw = d / len;

	vector4s::Vector4f n = vector4s::Vector4f(nx, ny, nz, nw);

	vector4s::Vector4f ci = (n + 1.f) / 2.f;

	return n;
}



void RFuncSprite::DrawRFunc(const std::function<float(const sf::Vector2f &)> &rfunc, const sf::FloatRect &subSpace,
							const int mode, const sf::Color color_new)
{
	for (unsigned x = 0; x < _image.getSize().x; ++x)
	{
		for (unsigned y = 0; y < _image.getSize().y; ++y)
		{
			vector4s::Vector4f n = getVector(rfunc, subSpace, x, y);
			vector4s::Vector4f ci = (n + 1.f) / 2.f;
			_cx[x][y] = n.x;
			_cy[x][y] = n.y;

			sf::Uint8 color_new_r;
			sf::Uint8 color_new_g;
			sf::Uint8 color_new_b;
			switch (mode)
			{
			case 1:
				color_new_r = static_cast<sf::Uint8>(color_new.r * ci.x);
				color_new_g = static_cast<sf::Uint8>(color_new.g * ci.x);
				color_new_b = static_cast<sf::Uint8>(color_new.b * ci.x);
				
				break;
			case 2:
				color_new_r = static_cast<sf::Uint8>(color_new.r * ci.y);
				color_new_g = static_cast<sf::Uint8>(color_new.g * ci.y);
				color_new_b = static_cast<sf::Uint8>(color_new.b * ci.y);
				
				break;
			case 3:
				color_new_r = static_cast<sf::Uint8>(color_new.r * ci.z);
				color_new_g = static_cast<sf::Uint8>(color_new.g * ci.z);
				color_new_b = static_cast<sf::Uint8>(color_new.b * ci.z);
				break;
			case 4:
				color_new_r = static_cast<sf::Uint8>(color_new.r * ci.w);
				color_new_g = static_cast<sf::Uint8>(color_new.g * ci.w);
				color_new_b = static_cast<sf::Uint8>(color_new.b * ci.w);
				break;
			}

			//sf::Uint8 color = static_cast<sf::Uint8>(255.f * ñ.x);
			sf::Color pixelColor;
			_image.setPixel(x, y, sf::Color(color_new_r, color_new_g, color_new_b));
			//_image.setPixel(x, y, sf::Color::Red);

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
	/*if (z > 0)
		_image.setPixel(x, y, sf::Color::Red);
	else
		_image.setPixel(x, y, sf::Color::Black);*/

	return sf::Vector3f(spacePoint.x, spacePoint.y, z);
}
