/**
  ******************************************************************************
  * @file           : coordinator.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/7
  ******************************************************************************
  */



#ifndef ECS_TOOLS_COORDINATOR_HPP
#define ECS_TOOLS_COORDINATOR_HPP

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "system_manager.hpp"

#include <iostream>

class Coordinator {
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;

public:

    Coordinator() {
        _componentManager = std::unique_ptr<ComponentManager>();
        _entityManager = std::unique_ptr<EntityManager>();
        _systemManager = std::unique_ptr<SystemManager>();
    }

    Entity CreateEntity() {
        return _entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity) {
        _entityManager->DestroyEntity(entity);
        _componentManager->EntityDestroyed(entity);
        _systemManager->EntityDestroyed(entity);
    }

    template<typename T>
    void RegisterComponent() {
        _componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        _componentManager->AddComponent<T>(entity, component);

        auto signature = _entityManager->GetSignature(entity);
        signature.set(_componentManager->GetComponentType<T>(), true);
        _entityManager->SetSignature(entity, signature);

        _systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        _componentManager->RemoveComponent<T>(entity);

        auto signature = _entityManager->GetSignature(entity);
        signature.set(_componentManager->GetComponentType<T>(), false);
        _entityManager->SetSignature(entity, signature);

        _systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T &GetComponent(Entity entity) {
        return _componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType() {
        return _componentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        return _systemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature) {
        _systemManager->SetSignature<T>(signature);
    }
};


#endif //ECS_TOOLS_COORDINATOR_HPP
