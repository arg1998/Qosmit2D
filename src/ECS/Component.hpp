#pragma once

#include "defines.hpp"
#include "Containers/Vec.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class Component {
   public:
    b8 exists = false;
    Component() = default;
};

class TransformComponent : public Component {
   public:
    Vec2f pos{0, 0};
    Vec2f velocity{0, 0};
    f32 angle{0};  // degrees NOT radians
    f32 angular_momentum{0};
    Vec2f scale {1.0f, 1.0f};
    TransformComponent() = default;
    TransformComponent(const Vec2f &position, const Vec2f &velocity, f32 angle, f32 angular_momentum, Vec2f scale)
        : pos(position), velocity(velocity), angle(angle), scale(scale), angular_momentum(angular_momentum) {}
};

class PlayerInputComponent : public Component {
   public:
    b8 move_up{false};
    b8 move_down{false};
    b8 move_right{false};
    b8 move_left{false};
    b8 shoot{false};
    b8 ultimate_power{false};

    PlayerInputComponent() = default;
};

class ScoreComponent : public Component {
   public:
    u32 score{0};
    ScoreComponent() = default;
};

class CollisionComponent : public Component {
   public:
    u32 radius{0};
    CollisionComponent() = default;
    CollisionComponent(u32 radius) : radius(radius) {}
};

class PolygonComponent : public Component {
   public:
    sf::CircleShape polygon;
    f32 radius;
    f32 outline_thickness;
    sf::Color outline_color, original_outline_color;
    sf::Color fill_color, original_fill_color;

    PolygonComponent() = default;
    PolygonComponent(u32 num_sides, f32 radius, f32 outline_thickness, const sf::Color outline_color, const sf::Color fill_color)
        : radius(radius), outline_thickness(outline_thickness), outline_color(outline_color), original_outline_color(outline_color), fill_color(fill_color), original_fill_color(fill_color), polygon(radius, num_sides) {
        polygon.setOutlineColor(outline_color);
        polygon.setOutlineThickness(outline_thickness);
        polygon.setFillColor(fill_color);
        polygon.setOrigin(sf::Vector2f(radius, radius));
        
    }
};

class LifespanComponent : public Component {
   public:
    s32 total_lifespan_frames{0};
    s32 remaining_lifespan_frames{0};

    LifespanComponent() = default;
    LifespanComponent(u32 lifespan) : total_lifespan_frames(lifespan), remaining_lifespan_frames(lifespan) {}
};

class HealthComponent : public Component {
   public:
    f32 current_helth{1};
    f32 max_health{1};

    HealthComponent() = default;
    HealthComponent(f32 max_health) : max_health(max_health), current_helth(max_health) {}
};

class DamageComponent : public Component {
   public:
    f32 damage{1};

    DamageComponent() = default;
    DamageComponent(f32 damage) : damage(damage) {}
};

class ImmunityComponent : public Component {
   public:
    ImmunityComponent() = default;
};
