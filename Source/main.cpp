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

float amplitude = 200;
int frequency = 5;
int mode = 1; 

void RenderAbsoluteValueFunction(sf::RenderWindow &window, float amplitude)
{
	sf::VertexArray absCurve(sf::LineStrip, 1000);

	for (int i = 0; i < 1000; ++i)
	{
		float x = static_cast<float>(i) / 1000.0f * window.getSize().x;
		float y = amplitude * std::abs(x - window.getSize().x / 2);

		absCurve[i].position = sf::Vector2f(x, window.getSize().y / 2 - y);
		absCurve[i].color = sf::Color::Red;
	}

	window.draw(absCurve);
}

void RenderSquareFunction(sf::RenderWindow &window, float amplitude)
{
	sf::VertexArray squareCurve(sf::LineStrip, 1000);

	for (int i = 0; i < 1000; ++i)
	{
		float x = static_cast<float>(i) / 1000.0f * window.getSize().x;
		float y = amplitude * (x - window.getSize().x / 2) * (x - window.getSize().x / 2);

		squareCurve[i].position = sf::Vector2f(x, window.getSize().y / 2 - y);
		squareCurve[i].color = sf::Color::Red;
	}

	window.draw(squareCurve);
}

void RenderSquareRootFunction(sf::RenderWindow &window, float amplitude)
{
	sf::VertexArray sqrtCurve(sf::LineStrip, 1000);

	for (int i = 0; i < 1000; ++i)
	{
		float x = static_cast<float>(i) / 1000.0f * window.getSize().x;
		float y = amplitude * std::sqrt(x - window.getSize().x / 2);

		sqrtCurve[i].position = sf::Vector2f(x, window.getSize().y / 2 - y);
		sqrtCurve[i].color = sf::Color::Red;
	}

	window.draw(sqrtCurve);
}

void RenderSinFunction(sf::RenderWindow &window, float amplitude, float frequency)
{
	sf::VertexArray sinCurve(sf::LineStrip, 1000);

	for (int i = 0; i < 1000; ++i)
	{
		float x = static_cast<float>(i) / 1000.0f * window.getSize().x;
		float y = amplitude * std::sin(2 * 3.14159f * frequency * x / window.getSize().x);

		sinCurve[i].position = sf::Vector2f(x, window.getSize().y / 2 - y);
		sinCurve[i].color = sf::Color::Red;
	}

	window.draw(sinCurve);
}

void RenderCosFunction(sf::RenderWindow &window, float amplitude, float frequency)
{
	sf::VertexArray cosCurve(sf::LineStrip, 1000);

	for (int i = 0; i < 1000; ++i)
	{
		float x = static_cast<float>(i) / 1000.0f * window.getSize().x;
		float y = amplitude * std::cos(2 * 3.14159f * frequency * x / window.getSize().x);

		cosCurve[i].position = sf::Vector2f(x, window.getSize().y / 2 - y);
		cosCurve[i].color = sf::Color::Red;
	}

	window.draw(cosCurve);
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

	sf::RectangleShape back(sf::Vector2f(vec.x, vec.y));
	back.setFillColor(sf::Color::White);
	back.setPosition(0, 0);
	window.draw(back);

	sf::RectangleShape line_x(sf::Vector2f(vec.x, 2));
	line_x.setFillColor(sf::Color::Black);
	line_x.setPosition(0, vec.y / 2);
	window.draw(line_x);

	sf::RectangleShape line_y(sf::Vector2f(2, vec.y));
	line_y.setFillColor(sf::Color::Black);
	line_y.setPosition(vec.x / 2, 0);
	window.draw(line_y);
	
	switch (mode)
	{
	case 1:
		
		RenderSinFunction(window, amplitude, frequency);
		break;
	case 2:
		RenderCosFunction(window, amplitude, frequency);
		break;
	case 3:
		RenderSquareFunction(window, amplitude);
		break;
	case 4:
		RenderSquareRootFunction(window, amplitude);
		break;
	case 5:
		RenderAbsoluteValueFunction(window, amplitude);
		break;
	default:
		RenderSinFunction(window, amplitude, frequency);
		break;
	}
}

void RenderGui(sf::RenderWindow& window)
{
	ImGui::Begin("Function selection");

	if (ImGui::Button("Sin"))
	{
		mode = 1;
		amplitude = 200;
	}
	ImGui::SameLine();
	if (ImGui::Button("Cos"))
	{
		mode = 2;
		amplitude = 200;
	}
	ImGui::SameLine();
	if (ImGui::Button("Square"))
	{
		mode = 3;
		amplitude = 0.01;
	}
	ImGui::SameLine();
	if (ImGui::Button("SquareRoot"))
	{
		mode = 4;
		amplitude = 10;
	}
	ImGui::SameLine();
	if (ImGui::Button("Abs"))
	{
		mode = 5;
		amplitude = 1;
	}

	switch (mode)
	{
	case 1:
		ImGui::InputFloat("Amplitude value", &amplitude, 1.0F, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputInt("Frequency value", &frequency, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		break;
	case 2:
		ImGui::InputFloat("Amplitude value", &amplitude, 1.0F, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputInt("Frequency value", &frequency, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		break;
	case 3:
		ImGui::InputFloat("Amplitude value", &amplitude, 1.0F, ImGuiInputTextFlags_EnterReturnsTrue);
		break;
	case 4:
		ImGui::InputFloat("Amplitude value", &amplitude, 1.0F, ImGuiInputTextFlags_EnterReturnsTrue);
		break;
	case 5:
		ImGui::InputFloat("Amplitude value", &amplitude, 1.0F, ImGuiInputTextFlags_EnterReturnsTrue);
		break;
	default:
		ImGui::InputFloat("Amplitude value", &amplitude, 1.0F, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputInt("Frequency value", &frequency, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		break;
	}

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
