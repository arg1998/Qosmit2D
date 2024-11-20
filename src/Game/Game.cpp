#include "Game.hpp"
#include "Utils/Math.hpp"

b8 Game::init() {
    spawnPlayer();

    this->paused = false;
    this->game_over = false;
    this->debug_view = false;
    this->should_spawn = true;
    this->score = 0;
    this->frame_count = 0;

    score_text.setFont(this->font);
    score_text.setFillColor(sf::Color(255, 255, 255, 255));

    game_status_text.setFont(this->font);
    game_status_text.setCharacterSize(36);
    this->running = true;
    return true;
}

Actor Game::getPlayer() {
    return this->player;
}

Game::Game(std::string title, u32 width, u32 height) {
    sf::ContextSettings sfml_settings;
    sfml_settings.antialiasingLevel = 8;
    this->font.loadFromFile("../assets/fonts/neuropol x rg.otf");
    this->window.create(sf::VideoMode(width, height), title, sf::Style::Default, sfml_settings);
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(this->window);

    this->game_name = title;
    this->window_size = sf::Vector2<f32>(width, height);

    init();
}

void Game::spawnPlayer() {
    this->player = entity_manager.addEntity(EntityTag::PlayerEntity, true);
    this->player->add<PolygonComponent>(player_config.num_sides, player_config.radius, 3.0f, player_config.outline_color, player_config.fill_color);
    this->player->add<TransformComponent>(Vec2f(window_size.x, window_size.y) * 0.5, Vec2f(0, 0), 0.0f, player_config.angular_momentum, player_config.scale);
    this->player->add<PlayerInputComponent>();
    this->player->add<CollisionComponent>(player_config.radius);
    this->player->add<HealthComponent>(player_config.max_health);
}

void Game::run(const PlayerConfig& player_config, const EnemyConfig& enemy_config) {
    this->player_config = player_config;
    this->enemy_config = enemy_config;

    delta_clock.restart();
    while (running) {
        frame_count++;
        entity_manager.update();
        window.clear();

        applyUserInputSystem();
        applyMovementSystem();
        applyPhysicsSystem();
        applyEnemySpawnSystem();
        applyLifespanSystem();
        applyRenderSystem();
        applyUserInterfaceSystem();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void Game::spawnBullet(const Vec2f& direction) {
    const auto& projectile = player_config.projectile;
    f32 bullet_radius = projectile.radius;
    f32 bullet_velocity_base = projectile.max_speed;
    f32 player_radius = player->get<PolygonComponent>().radius;  // read this dynamically in case we change the player radius mid-game
    auto player_transform = player->get<TransformComponent>();
    auto bullet_entt = entity_manager.addEntity(EntityTag::ProjectileEntity);

    Vec2f bullet_pos = direction - player_transform.pos;
    f32 bullet_angle = CalculateSfmlLocalAngle(bullet_pos);

    bullet_pos.normalize();
    Vec2f bullet_velocity = bullet_pos * bullet_velocity_base;
    bullet_pos.multiply(player_radius).add(Vec2f(bullet_radius / 2, bullet_radius / 2)).add(player_transform.pos);

    bullet_entt->add<PolygonComponent>(player_config.projectile.num_sides, bullet_radius, 1, projectile.outline_color, projectile.outline_color);
    bullet_entt->add<TransformComponent>(bullet_pos, bullet_velocity, bullet_angle, 0.0f, projectile.scale);
    bullet_entt->add<LifespanComponent>(projectile.lifespan);
    bullet_entt->add<CollisionComponent>(bullet_radius);
    bullet_entt->add<DamageComponent>(projectile.damage);
}

void Game::restart() {
    this->player.reset();
    entity_manager.deleteAllEntities();
    init();
}


void Game::handleWindowResize() {
    for (auto entt : entity_manager.getAllEntities()) {
        auto& transform = entt->get<TransformComponent>();
        auto& bb = entt->get<CollisionComponent>();
        if (transform.exists && bb.exists) {
            if (transform.pos.x < bb.radius ||
                transform.pos.y < bb.radius ||
                transform.pos.x > window_size.x - bb.radius ||
                transform.pos.y > window_size.y - bb.radius) {
                entt->destroy();
            }
        }
    }
}