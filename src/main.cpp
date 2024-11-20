#include "Containers/Vec.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include <Game/Game.hpp>

#include <fmt/base.h>
#include <fmt/color.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {

    srand(time(NULL));
    PlayerConfig player;
    EnemyConfig enemy;
    enemy.color_range = {
        sf::Color(255, 0, 0),      // Bright Red
        sf::Color(0, 255, 0),      // Bright Green
        sf::Color(0, 0, 255),      // Bright Blue
        sf::Color(255, 255, 0),    // Yellow
        sf::Color(0, 255, 255),    // Cyan
        sf::Color(255, 0, 255),    // Magenta
        sf::Color(255, 165, 0),    // Orange
        sf::Color(75, 0, 130),     // Indigo
        sf::Color(238, 130, 238),  // Violet
        sf::Color(128, 0, 128),    // Purple
        sf::Color(0, 128, 128),    // Teal
        sf::Color(128, 128, 0),    // Olive
        sf::Color(255, 105, 180),  // Hot Pink
        sf::Color(173, 216, 230),  // Light Blue
        sf::Color(124, 252, 0)     // Lawn Green
    };

    Game game("Argosta", 1400, 900);
    game.run(player, enemy);
}