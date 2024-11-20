#pragma once

#include "defines.hpp"
#include "Containers/Vec.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ActorConfigs.hpp"

#include <string>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

using Actor = std::shared_ptr<Entity>;

class Game {
   private:
    std::string game_name;
    sf::RenderWindow window;
    sf::Vector2<f32> window_size;
    sf::Font font;
    sf::Text score_text;
    sf::Text game_status_text;
    EntityManager entity_manager;
    sf::Clock delta_clock;
    Actor player;
    u64 frame_count;
    u32 score;
    b8 paused; // if the systems are allowed to evolve the game states
    b8 game_over;
    b8 running; // if game is initialzied and game loop is running
    b8 debug_view;
    b8 should_spawn;
    Vec2f mouse_pos;

    PlayerConfig player_config;
    EnemyConfig enemy_config;
    

    b8 init();
    void restart();
    void handleWindowResize();

    void applyMovementSystem();
    void applyPhysicsSystem();
    void applySoundSystem();
    void applyUserInterfaceSystem();
    void applyUserInputSystem();
    void applyRenderSystem();
    void applyEnemySpawnSystem();
    void applyLifespanSystem();


    void spawnPlayer();
    void spawnBullet(const Vec2f& direction);

    Actor getPlayer();

    

   public:
    Game(std::string title, u32 width, u32 height);

    void run(const PlayerConfig& player_config, const EnemyConfig& enemy_config);
};