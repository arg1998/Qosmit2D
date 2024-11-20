#pragma once

#include "defines.hpp"
#include <vector>
#include <SFML/Graphics/Color.hpp>

struct ProjectileConfic {
    u32 num_sides;
    f32 damage;  // if negative, it will heal!
    u32 radius;
    u32 max_speed;
    u32 lifespan;
    sf::Color outline_color;
    sf::Color fill_color;
    Vec2f scale;

    ProjectileConfic() : num_sides(3), radius(6), damage(1.0f), max_speed(12), lifespan(60), outline_color(255, 50, 50, 255), fill_color(250, 100, 100, 200), scale(1.0f, 2.0f) {}
};

struct PlayerConfig {
    u32 num_sides;
    u32 radius;
    u32 max_health;
    u32 max_speed;
    u32 angular_momentum;
    sf::Color outline_color;
    sf::Color fill_color;
    ProjectileConfic projectile;
    Vec2f scale;

    PlayerConfig() : num_sides(8), radius(40), max_health(3), max_speed(6), angular_momentum(3), outline_color(255, 0, 0, 255), fill_color(0, 0, 0, 255), projectile(), scale(1.0f, 2.0f) {}
};

struct EnemyConfig {
    u32 min_side;
    u32 max_side;
    u32 min_radius;
    u32 max_radius;
    u32 spawn_rate;  // in numebr of frames
    u32 min_health;
    u32 max_helth;
    u32 min_speed;
    u32 max_speed;
    f32 damage;
    std::vector<sf::Color> color_range;

    EnemyConfig() : min_side(3), max_side(7), min_radius(15), max_radius(35), spawn_rate(60), min_health(1), max_helth(3), min_speed(2), max_speed(4), damage(1.0f), color_range(1, sf::Color(255, 255, 255, 255)) {}
};