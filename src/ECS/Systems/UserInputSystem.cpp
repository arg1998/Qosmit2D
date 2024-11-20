#include "Game/Game.hpp"

void Game::applyUserInputSystem() {
    ImGui::SFML::Update(window, delta_clock.restart());
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        // get mouse position
        const auto &sfml_mouse = sf::Mouse::getPosition(this->window);
        this->mouse_pos.x = sfml_mouse.x;
        this->mouse_pos.y = sfml_mouse.y;

        if (event.type == sf::Event::Closed) {
            window.close();
            running = false;
        }

        // Handle window resize event
        if (event.type == sf::Event::Resized) {
            
            this->window_size.x = static_cast<f32>(event.size.width);
            this->window_size.y = static_cast<f32>(event.size.height);
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }

        // disable click through if user is clicking or typing in imgui
        if (debug_view) {
            auto &imgui_io = ImGui::GetIO();
            if (imgui_io.WantCaptureMouse || imgui_io.WantCaptureKeyboard) {
                continue;
            }
        }

        if (event.type == event.KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (!game_over) {
                    paused = !paused;
                }
            }

            if (event.key.code == sf::Keyboard::Space) {
                debug_view = !debug_view;
            }

            if (event.key.code == sf::Keyboard::R && game_over) {
                restart();
            }
        }

        // -----------------------------------------------------------------------
        //                  Player input processing
        // -----------------------------------------------------------------------
        if (paused) return;

        auto &player_input = player->get<PlayerInputComponent>();
        if (event.type == event.KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                player_input.move_up = true;
            }
            if (event.key.code == sf::Keyboard::S) {
                player_input.move_down = true;
            }
            if (event.key.code == sf::Keyboard::A) {
                player_input.move_left = true;
            }
            if (event.key.code == sf::Keyboard::D) {
                player_input.move_right = true;
            }
        }

        if (event.type == event.KeyReleased) {
            if (event.key.code == sf::Keyboard::W) {
                player_input.move_up = false;
            }
            if (event.key.code == sf::Keyboard::S) {
                player_input.move_down = false;
            }
            if (event.key.code == sf::Keyboard::A) {
                player_input.move_left = false;
            }
            if (event.key.code == sf::Keyboard::D) {
                player_input.move_right = false;
            }
        }

        if (event.type == event.MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                player_input.shoot = true;
                auto mouse_pos = sf::Mouse::getPosition(window);
                spawnBullet(Vec2f(mouse_pos.x, mouse_pos.y));
            }
        }

        if (event.type == event.MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                player_input.shoot = false;
            }
        }
    }
}