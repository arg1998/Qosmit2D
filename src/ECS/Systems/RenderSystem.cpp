#include "Game/Game.hpp"
#include "Utils/Math.hpp"

void Game::applyRenderSystem() {
    // render all polygons
    for (auto &entt : entity_manager.getEntitiesByTag(EntityTag::EnemyEntity)) {
        auto &shape = entt->get<PolygonComponent>();
        auto &transform = entt->get<TransformComponent>();
        if (shape.exists && transform.exists) {
            shape.polygon.setPosition(transform.pos.x, transform.pos.y);
            shape.polygon.setRotation(transform.angle);
            shape.polygon.setFillColor(shape.fill_color);
            shape.polygon.setOutlineColor(shape.outline_color);

            this->window.draw(shape.polygon);
        }
    }

    for (auto &entt : entity_manager.getEntitiesByTag(EntityTag::ProjectileEntity)) {
        auto &shape = entt->get<PolygonComponent>();
        auto &transform = entt->get<TransformComponent>();
        if (shape.exists && transform.exists) {
            shape.polygon.setScale(transform.scale.x, transform.scale.y);
            shape.polygon.setPosition(transform.pos.x, transform.pos.y);
            shape.polygon.setRotation(transform.angle);
            shape.polygon.setFillColor(shape.fill_color);
            shape.polygon.setOutlineColor(shape.outline_color);

            this->window.draw(shape.polygon);
        }
    }

    // draw player on top of everything
    auto &shape = player->get<PolygonComponent>();
    auto &transform = player->get<TransformComponent>();
    if (shape.exists && transform.exists) {
        shape.polygon.setPosition(transform.pos.x, transform.pos.y);
        shape.polygon.setRotation(transform.angle);
        shape.polygon.setFillColor(shape.fill_color);
        shape.polygon.setOutlineColor(shape.outline_color);

        const f32 turret_scale = 5;
        const f32 turret_radius = (shape.radius / 2) + 10;
        sf::CircleShape turret(turret_radius, 3);
        turret.setOrigin(turret_radius, 0);
        turret.setScale(1.0f / turret_scale, 1.0f);
        turret.setPosition(transform.pos.x, transform.pos.y);
        turret.setFillColor(sf::Color::Yellow);

        const Vec2f direction = mouse_pos - transform.pos;
        f32 turret_angle = CalculateSfmlLocalAngle(direction);
        turret.setRotation(turret_angle + 180);

        this->window.draw(shape.polygon);
        this->window.draw(turret);
    }
}