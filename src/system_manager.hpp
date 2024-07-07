/**
  ******************************************************************************
  * @file           : system_manager.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/7
  ******************************************************************************
  */



#ifndef ECS_TOOLS_SYSTEM_MANAGER_HPP
#define ECS_TOOLS_SYSTEM_MANAGER_HPP


#include "system.hpp"
#include "types.hpp"

#include <map>

class SystemManager {
private:
    // contains all signatures
    std::unordered_map<const char*, Signature> _signatures;

    // contains all systems
    std:: unordered_map<const char*, std::shared_ptr<System>> _systems;

public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        const char* typeName = typeid(T).name();

        assert(_systems.find(typeName) == _systems.end()
                && "Registering system more than once.");

        auto system = std::make_shared<T>();
        _systems.insert({typeName, system});
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();

        assert(_systems.find(typeName) != _systems.end()
                && "System used before registered.");

        // set system signatures, which indicates what components system contains
        _signatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity) {
        for(auto const& pair : _systems) {
            auto const& system = pair.second;

            system->_entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature) {
        for(auto const& pair : _systems){
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = _signatures[type];

            // if entity contains all components system needs
            if((entitySignature & systemSignature) == systemSignature) {
                system->_entities.insert(entity);
            }
            // else remove the entity
            else{
                system->_entities.erase(entity);
            }
        }
    }
};


#endif //ECS_TOOLS_SYSTEM_MANAGER_HPP
