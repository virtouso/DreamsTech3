// DreamsTech3Engine.cpp : Defines the entry point for the application.
//

#include "DreamsTech3Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Settings/GeneralSettings.h"
#include "../DreamsTech3Engine/Editor/Manager/EditorManager.h"

int main()
{

	EditorManager editorManager = EditorManager();

	sf::RenderWindow window(sf::VideoMode(GeneralSettings::WindowSize.x, GeneralSettings::WindowSize.y), "ImGui + SFML = <3");
	window.setFramerateLimit(GeneralSettings::FrameRate);
	ImGui::SFML::Init(window);

	//   sf::CircleShape shape(100.f);
	//   shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());
	//	ImGui::Begin("Hello, world!");
	/*	if (ImGui::Button("Look at this pretty button"))
		{
			std::cout << "button pressed";
		}*/
		editorManager.Show();

	//	ImGui::End();

		window.clear();
	//	window.draw(shape);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}
