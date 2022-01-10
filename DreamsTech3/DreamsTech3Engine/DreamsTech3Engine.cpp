// DreamsTech3Engine.cpp : Defines the entry point for the application.
//

#include "DreamsTech3Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Settings/GeneralSettings.h"
#include "../DreamsTech3Engine/Editor/Manager/EditorManager.h"
#include "GamePlay/Entity/Object.h"
#include "Global/GlobalObjects.h"

int main()
{

	EditorManager editorManager = EditorManager();

	GlobalObjects::window = new  sf::RenderWindow(sf::VideoMode(GeneralSettings::WindowSize.x, GeneralSettings::WindowSize.y), "ImGui + SFML = <3");
	GlobalObjects::window->setFramerateLimit(GeneralSettings::FrameRate);
	ImGui::SFML::Init(*GlobalObjects::window);

	//   sf::CircleShape shape(100.f);
	//   shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;
	while (GlobalObjects::window->isOpen()) {
		sf::Event event;
		while (GlobalObjects::window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(*GlobalObjects::window, event);

			if (event.type == sf::Event::Closed) {
				GlobalObjects::window->close();
			}
		}

		ImGui::SFML::Update(*GlobalObjects::window, deltaClock.restart());

		editorManager.Show();



		GlobalObjects::window->clear();
		//	window.draw(shape);
		ImGui::SFML::Render(*GlobalObjects::window);
		GlobalObjects::window->display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}
