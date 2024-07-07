/**
  ******************************************************************************
  * @file           : entity_manager.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/6
  ******************************************************************************
  */



#ifndef ECS_TOOLS_ENTITY_MANAGER_HPP
#define ECS_TOOLS_ENTITY_MANAGER_HPP

#include "types.hpp"

#include <queue>
#include <algorithm>


class EntityManager {
private:
    // unused entity IDs
    std::queue<Entity> _availableEntities{};

    // signatures correspond to entity ID
    std::array<Signature, MAX_ENTITIES> _signatures{};

    // all living entities count;
    Entity _livingEntitiesCount{};

public:
    EntityManager(){
        // initialize the queue with all entity IDs
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            _availableEntities.push(entity);
        }
    }

    Entity CreateEntity() {
        assert(_livingEntitiesCount < MAX_ENTITIES && "living entities count larger than extent");

        // take an unused ID from the queue;
        Entity id = _availableEntities.front();
        _availableEntities.pop();
        _livingEntitiesCount++;

        return id;
    }

    void DestroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "entity id out of range");

        // BUG: remains a bug that when you try to destroy an entity that already in _availableEntities

        _signatures[entity].reset();
        _availableEntities.push(entity);
        _livingEntitiesCount--;
    }

};


#endif //ECS_TOOLS_ENTITY_MANAGER_HPP
