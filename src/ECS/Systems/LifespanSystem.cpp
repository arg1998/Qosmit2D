#include "Game/Game.hpp"

void Game::applyLifespanSystem() {
    if(paused) return;
    for (auto entt : entity_manager.getAllEntities()) {
        auto &lifespan = entt->get<LifespanComponent>();
        if (lifespan.exists) {
            lifespan.remaining_lifespan_frames--;
            if (lifespan.remaining_lifespan_frames < 1) {
                entt->destroy();
                continue;
            }

            auto &shape = entt->get<PolygonComponent>();
            f32 coef = static_cast<f32>(lifespan.remaining_lifespan_frames)  /  static_cast<f32>(lifespan.total_lifespan_frames);
            coef = std::max<f32>(coef, 0.3);
            shape.fill_color.a = coef * shape.original_fill_color.a;
            shape.outline_color.a = coef * shape.original_outline_color.a;
        }
    }
}