#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Core/Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "MKart2D");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    Game game(window);
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            ImGui::SFML::ProcessEvent(e);
            if (e.type == sf::Event::Closed) window.close();
        }
        sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        game.update(dt.asSeconds());
        window.clear();
        game.render(window);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
