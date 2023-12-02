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



float amplitude = 1;
int frequency = 5;
int mode = 1; 

float RAnd(float w1, float w2) 
{ 
	return w1 + w2 - sqrt(w1 * w1 + w2 * w2); 
}

float ROr(float w1, float w2) 
{ 
	return w1 + w2 + sqrt(w1 * w1 + w2 * w2); 
}

void HandleUserInput(sf::RenderWindow& window, const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
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
	//vecs::Vector4f point = vecs::Vector4f();
	
	
}

void RenderGui(sf::RenderWindow& window)
{
	ImGui::Begin("Function selection");

	

	ImGui::End();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Lab 1");
	window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(window))
	{
		std::cout << "ImGui initialization failed\n";
		return -1;
	}

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
