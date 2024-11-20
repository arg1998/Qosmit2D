#pragma once

#include "defines.hpp"
#include "Component.hpp"

#include <tuple>
#include <vector>
#include <map>
#include <memory>

// forward declaration
class Entity;
class EntityManager;

enum EntityTag : u32 {
    UNTAGGED_ENTITIY = 0,
    PlayerEntity,
    EnemyEntity,
    ProjectileEntity,
    UserInterfaceEntity,

    EntityTypeCount
};

using ComponentTuple = std::tuple<
    TransformComponent,
    PolygonComponent,
    CollisionComponent,
    PlayerInputComponent,
    LifespanComponent,
    ScoreComponent,
    HealthComponent,
    DamageComponent,
    ImmunityComponent>;

using EntityList = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<EntityTag, EntityList>;
using EID = u32;  // Entity ID

class Entity {
    friend class EntityManager;

    ComponentTuple component_tuple;
    EID entity_id;
    EntityTag entity_tag{UNTAGGED_ENTITIY};
    b8 is_alive{true};
    b8 is_permanant{false};

    Entity(EntityTag tag, EID id, b8 permanant = false) {
        entity_tag = tag;
        entity_id = id;
        is_permanant = permanant;
    }

   public:
    Entity() = delete;

    b8 isAlive() {
        return is_alive;
    }

    b8 isPermanant() {
        return is_permanant;
    }

    void destroy() {
        if (isPermanant()) return;
        is_alive = false;
    }

    EID id() {
        return entity_id;
    }

    EntityTag tag() {
        return entity_tag;
    }
    const char* tagStr() const {
        static const char* entt_str[] = {"UNTAGGED_ENTITIY", "PlayerEntity", "EnemyEntity", "ProjectileEntity", "UserInterfaceEntity"};
        return entt_str[static_cast<u32>(entity_tag)];
    }

    template <typename T>
    T&
    get() {
        return std::get<T>(component_tuple);
    }

    template <typename T>
    const T& get() const {
        return std::get<T>(component_tuple);
    }

    template <typename T>
    b8 has() {
        return get<T>().exists;
    }

    template <typename T, typename... Args>
    T& add(Args&&... args) {
        auto& component = get<T>();
        component = T(std::forward<Args>(args)...);
        component.exists = true;
        return component;
    }
};

class EntityManager {
    const u32 MAX_ENTITY{1024};
    u64 num_entities{0};
    EntityList entities;
    EntityList to_add_queue;
    EntityMap entity_map;

    void removeDeadEntities(EntityList& entity_list) {
        for (auto it = entity_list.begin(); it != entity_list.end();) {
            auto& entt = (*it);
            if (!entt->isPermanant() && !entt->isAlive()) {
                it = entity_list.erase(it);
                continue;
            }
            it++;
        }
    }

    void init() {
        entities.reserve(MAX_ENTITY);
        to_add_queue.reserve(MAX_ENTITY / 4);
        for (u32 tag = static_cast<u32>(EntityTag::UNTAGGED_ENTITIY); tag < static_cast<u32>(EntityTag::EntityTypeCount); tag++) {
            entity_map[static_cast<EntityTag>(tag)] = EntityList();
            entity_map[static_cast<EntityTag>(tag)].reserve(MAX_ENTITY);
        }
    }

   public:
    EntityManager() {
        init();
    };

    u64 numEntities() {
        return num_entities;
    }

    void update() {
        // 1. add pending entities
        for (auto entity : to_add_queue) {
            entities.push_back(entity);
            EntityTag tag = entity->tag();
            entity_map[tag].push_back(entity);
        }
        to_add_queue.clear();

        // 2. remove dead entities from entities list
        removeDeadEntities(entities);
        // 3. remove dead entities from entities map
        for (auto& pair : entity_map) {
            removeDeadEntities(pair.second);
        }

        num_entities = entities.size();
    }

    std::shared_ptr<Entity> addEntity(EntityTag tag, b8 is_premanant = false) {
        // we can't use std::make_shared<Entitiy>() becuase the the consturctor of Entity Class is privtae
        auto entity = std::shared_ptr<Entity>(new Entity(tag, num_entities++, is_premanant));
        to_add_queue.push_back(entity);
        // entities.push_back(entity);
        // entity_map[tag].push_back(entity);
        return entity;
    }

    EntityList& getAllEntities() {
        return entities;
    }

    EntityList& getEntitiesByTag(EntityTag tag) {
        return entity_map[tag];
    }

    void deleteAllEntities() {
        entities.clear();
        for (u32 tag = static_cast<u32>(EntityTag::UNTAGGED_ENTITIY); tag < static_cast<u32>(EntityTag::EntityTypeCount); tag++) {
            entity_map[static_cast<EntityTag>(tag)].clear();
        }
        num_entities = entities.size();
    }
};
