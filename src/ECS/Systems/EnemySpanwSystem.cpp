#include "Game/Game.hpp"

#include "Utils/Random.hpp"

void Game::applyEnemySpawnSystem() {
    if(paused || !should_spawn) return;
    if (frame_count % enemy_config.spawn_rate != 0) return;

    const auto& ec = this->enemy_config;

    u32 radius = RandomS32(ec.min_radius, ec.max_radius + 1);
    u32 num_sides = RandomS32(ec.min_side, ec.max_side + 1);
    sf::Color fill_color = ec.color_range[RandomS32(0, ec.color_range.size())];
    u32 speed = RandomS32(ec.min_speed, ec.max_speed + 1);
    Vec2f velocity;
    velocity.x = RandomFloatSinged();
    velocity.y = RandomFloatSinged();
    velocity.normalize().multiply(speed);
    f32 angular_momenum = speed * 0.5;
    if(RandomFloat() > 0.5){
        angular_momenum *= -1;
    }
    u32 margin = 5;
    Vec2f pos;
    pos.x = RandomS32(radius + margin, window_size.x - radius - margin);
    pos.y = RandomS32(radius + margin, window_size.y - radius - margin);

    auto enemy_entt = entity_manager.addEntity(EntityTag::EnemyEntity, false);
    enemy_entt->add<PolygonComponent>(num_sides, radius, 0, sf::Color(255, 255, 255, 255), fill_color);
    enemy_entt->add<TransformComponent>(pos, velocity, 0, angular_momenum, Vec2f(1.0f, 1.0f));
    enemy_entt->add<CollisionComponent>(radius);
    enemy_entt->add<HealthComponent>(ec.min_health); // TODO: implement min-max health based on variable damage system
    enemy_entt->add<DamageComponent>(ec.damage);
}