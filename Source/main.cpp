#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"

#include "vector4.hpp"
#include "RFuncSprite.h"
#include "gpath.h"


float amplitude = 1;
int frequency = 5;
int mode = 1; 
bool renderingModeChanged = true;
bool renderingColorChanged = true;

sf::Color color;

RFuncSprite rFuncSprite;
gpath gPath;

sf::FloatRect floatRect(-10, -10, 20, 15);

float RAnd(float w1, float w2) 
{ 
	return w1 + w2 - sqrt(w1 * w1 + w2 * w2); 
}

float ROr(float w1, float w2) 
{ 
	return w1 + w2 + sqrt(w1 * w1 + w2 * w2); 
}

float myFunc(const sf::Vector2f &point)
{ 
	const int x1 = -1, y1 = 0, x2 = 0, y2 = -1, x3 = 1, y3 = 0, x4 = 1, y4 = 2, x5 = 2, y5 = 6, x6 = 1, y6 = 6, x7 = 0,
			  y7 = 8, x8 = -1, y8 = 6, x9 = -2, y9 = 6, x10 = -1, y10 = 2;

	float W1 = (y1 - y2) * point.x + (x1 - x2) * point.y + (y2 * x1 - y1 * x2);
	float W2 = (y2 - y3) * point.x + (x2 - x3) * point.y + (y3 * x2 - y2 * x3);
	float W3 = (y3 - y4) * point.x + (x3 - x4) * point.y + (y4 * x3 - y3 * x4);
	float W4 = (y4 - y5) * point.x + (x4 - x5) * point.y + (y5 * x4 - y4 * x5);
	float W5 = (y5 - y6) * point.x + (x5 - x6) * point.y + (y6 * x5 - y5 * x6);
	float W6 = (y6 - y7) * point.x + (x6 - x7) * point.y + (y7 * x6 - y6 * x7);
	float W7 = (y7 - y8) * point.x + (x7 - x8) * point.y + (y8 * x7 - y7 * x8);
	float W8 = (y8 - y9) * point.x + (x8 - x9) * point.y + (y9 * x8 - y8 * x9);
	float W9 = (y9 - y10) * point.x + (x9 - x10) * point.y + (y10 * x9 - y9 * x10);
	float W10 = (y10 - y1) * point.x + (x10 - x1) * point.y + (y1 * x10 - y10 * x1);

	return RAnd(RAnd(RAnd(RAnd(RAnd(RAnd(RAnd(RAnd(RAnd(W1, W2), W3), W4), W5), W6), W7), W8), W9), W10);
}

void HandleUserInput(sf::RenderWindow& window, const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::MouseButtonPressed:
	{
		sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, window.getSize().y - event.mouseButton.y); 

		sf::Color invertedColor;
		if (color != sf::Color::White)
		{
			invertedColor = sf::Color(255 - color.r, 255 - color.g, 255 - color.b);
		}
		else
		{
			invertedColor = sf::Color::Red;
		}
		
		gPath.FindPath(rFuncSprite, mousePos, invertedColor);
	}
	break;
	default:
		break;
	}
}

void Update(sf::RenderWindow& window, const sf::Time& deltaClock)
{

	// Make some time-dependent updates, like: physics, gameplay logic, animations, etc.
}

void Render(sf::RenderWindow& window)
{
	// Draw some sfml/opengl items
	sf::Vector2u vec = window.getSize();

	if (renderingModeChanged)
	{
		switch (mode)
		{
		case 1:
			rFuncSprite.DrawRFunc(&myFunc, floatRect, mode, color);
			break;
		case 2:
			rFuncSprite.DrawRFunc(&myFunc, floatRect, mode, color);
			break;
		case 3:
			rFuncSprite.DrawRFunc(&myFunc, floatRect, mode, color);
			break;
		case 4:
			rFuncSprite.DrawRFunc(&myFunc, floatRect, mode, color);
			break;
		}

		renderingModeChanged = false;
	}
	if (renderingColorChanged)
	{
		rFuncSprite.DrawRFunc(&myFunc, floatRect, mode, color);
		
		renderingColorChanged = false;
	}
	window.draw(rFuncSprite);
	window.draw(gPath);
}

void RenderGui(sf::RenderWindow& window)
{
	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Image mode picker"))
	{
		if (ImGui::Button("M OX"))
		{
			mode = 1;
			renderingModeChanged = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("M OY"))
		{
			mode = 2;
			renderingModeChanged = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("M OZ"))
		{
			mode = 3;
			renderingModeChanged = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("M OW"))
		{
			mode = 4;
			renderingModeChanged = true;
		}
	}
	
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Color picker"))
	{
		static ImVec4 clr(255.f, 255.f, 255.f, 255.f);
		if (ImGui::ColorPicker3("Choose color", &clr.x))
		{
			color.r = static_cast<sf::Uint8>(clr.x * 255.f);
			color.g = static_cast<sf::Uint8>(clr.y * 255.f);
			color.b = static_cast<sf::Uint8>(clr.z * 255.f);
		}
		if (ImGui::Button("Submit color"))
		{
			renderingColorChanged = true;
		}
	}

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Image saver"))
	{
		static char buf[128] = "Result";
		ImGui::InputText("Enter the file name", buf, IM_ARRAYSIZE(buf));
		if (ImGui::Button("Save"))
		{
			std::string str(buf, 128);
			size_t len = strlen(buf);
			rFuncSprite.SaveToFile(str.c_str());
		}
		
	}

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Path cleaner"))
	{
		if (ImGui::Button("Clear!"))
		{
			gPath.Clear();
		}
	}

	ImGui::Separator();

	ImGui::End();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Lab 2");
	window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(window))
	{
		std::cout << "ImGui initialization failed\n";
		return -1;
	}

	
	rFuncSprite.Create(sf::Vector2u(800, 800));
	gPath.Create(sf::Vector2u(800, 800));

	color.r = static_cast<sf::Uint8>(255.f);
	color.g = static_cast<sf::Uint8>(255.f);
	color.b = static_cast<sf::Uint8>(255.f);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			HandleUserInput(window, event);
		}

		sf::Time deltaTime = deltaClock.restart();
		ImGui::SFML::Update(window, deltaTime);
		Update(window, deltaTime);

		window.clear();

		RenderGui(window);
		Render(window);

		ImGui::SFML::Render(window);

		window.display();
	}
	ImGui::SFML::Shutdown();

	return 0;
}
