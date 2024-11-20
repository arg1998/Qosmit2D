#include "Game/Game.hpp"

void Game::applyMovementSystem() {
    for (auto &entt : entity_manager.getAllEntities()) {
        auto &transform = entt->get<TransformComponent>();
        if (transform.exists) {
            transform.angle += transform.angular_momentum;
        }
    }

    if (paused) return;
    
    auto &player_controller = player->get<PlayerInputComponent>();
    auto &player_transform = player->get<TransformComponent>();

    Vec2f delta_walk(0, 0);
    const f32 max_speed = 5;
    b8 player_moving = false;
    if (player_controller.move_up) {
        delta_walk.y = -max_speed;
        player_moving = true;
    }
    if (player_controller.move_down) {
        delta_walk.y = max_speed;
        player_moving = true;
    }

    if (player_controller.move_down && player_controller.move_up) {
        delta_walk.y = 0;
        player_moving = false;
    }

    if (player_controller.move_left) {
        delta_walk.x = -max_speed;
        player_moving = true;
    }

    if (player_controller.move_right) {
        delta_walk.x = max_speed;
        player_moving = true;
    }

    if (player_controller.move_left && player_controller.move_right) {
        delta_walk.x = 0;
        player_moving = false;
    }

    if (player_moving) {
        delta_walk.normalize().multiply(max_speed);
    } else {
        delta_walk.x = 0;
        delta_walk.y = 0;
    }

    if (player_transform.exists) {
        player_transform.velocity.x = delta_walk.x;
        player_transform.velocity.y = delta_walk.y;
    }

    for (auto &entt : entity_manager.getAllEntities()) {
        auto &transform = entt->get<TransformComponent>();
        if (transform.exists) {
            transform.pos.add(transform.velocity);
        }
    }
}