#include "Game/Game.hpp"

b8 hasCollided(const Vec2f &A_pos, f32 A_radius, const Vec2f &B_pos, f32 B_radius) {
    f32 dx = B_pos.x - A_pos.x;
    f32 dy = B_pos.y - A_pos.y;
    f32 distance_squared = dx * dx + dy * dy;
    f32 collision_radius = A_radius + B_radius;

    return distance_squared <= (collision_radius * collision_radius);
}

void Game::applyPhysicsSystem() {
    if (paused) return;

    auto &player_transform = player->get<TransformComponent>();
    auto &player_bb = player->get<CollisionComponent>();

    if (player_transform.pos.x < player_bb.radius) {
        player_transform.pos.x = player_bb.radius;
    } else if (player_transform.pos.x > window_size.x - player_bb.radius) {
        player_transform.pos.x = window_size.x - player_bb.radius;
    }

    if (player_transform.pos.y < player_bb.radius) {
        player_transform.pos.y = player_bb.radius;
    } else if (player_transform.pos.y > window_size.y - player_bb.radius) {
        player_transform.pos.y = window_size.y - player_bb.radius;
    }

    for (auto &entt_E : entity_manager.getEntitiesByTag(EntityTag::EnemyEntity)) {
        auto &bb_E = entt_E->get<CollisionComponent>();  // boundign box (well... it's a circle for now)
        auto &t_E = entt_E->get<TransformComponent>();

        // check for window left and right boundary collistion
        if ((t_E.pos.x < bb_E.radius) || (t_E.pos.x > window_size.x - bb_E.radius)) {
            t_E.velocity.x *= -1;  // flip the x axis
        }
        // check for window top and bottom boundary collistion
        if ((t_E.pos.y < bb_E.radius) || (t_E.pos.y > window_size.y - bb_E.radius)) {
            t_E.velocity.y *= -1;  // flip the x axis
        }

        b8 is_player_immune = player->get<ImmunityComponent>().exists;
        if (hasCollided(player_transform.pos, player_bb.radius, t_E.pos, bb_E.radius)) {
            if (is_player_immune) {
                entt_E->destroy();
            } else {
                auto &health = player->get<HealthComponent>();
                auto &enemy_damage = entt_E->get<DamageComponent>();

                health.current_helth -= enemy_damage.damage;

                if (health.current_helth < 0) {
                    health.current_helth = 0;
                    player->destroy();
                    game_over = true;
                    paused = true;
                }
            }
        }

        // Bullets
        for (auto &entt_B : entity_manager.getEntitiesByTag(EntityTag::ProjectileEntity)) {
            auto &bb_B = entt_B->get<CollisionComponent>();
            auto &t_B = entt_B->get<TransformComponent>();

            b8 collided = hasCollided(t_E.pos, bb_E.radius, t_B.pos, bb_B.radius);
            if (collided) {
                entt_E->destroy();
                entt_B->destroy();
                score++;
            }
        }
    }
}