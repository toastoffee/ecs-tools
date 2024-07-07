/**
  ******************************************************************************
  * @file           : component_manager.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/7
  ******************************************************************************
  */



#ifndef ECS_TOOLS_COMPONENT_MANAGER_HPP
#define ECS_TOOLS_COMPONENT_MANAGER_HPP

#include "types.hpp"

#include "component_array.hpp"

class ComponentManager {
private:
    // manage all componentType
    std::unordered_map<const char*, ComponentType> _componentTypes{};

    // manage all componentArray
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};

    // the component type to be assigned
    ComponentType _nextComponentType{};

private:
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) != _componentTypes.end()
                && "component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
    }

public:
    template<typename T>
    void RegisterComponent() {
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) == _componentTypes.end()
               && "Registering component type more than once.");

        // add this component type to the map
        _componentTypes.insert({typeName, _nextComponentType});

        // create a componentArray pointer and add it to the map
        _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        _nextComponentType++;
    }

    template<typename T>
    ComponentType GetComponentType() {
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) != _componentTypes.end()
               && "Component not registered before use.");

        return _componentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) != _componentTypes.end()
               && "Component not registered before use.");

        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) != _componentTypes.end()
               && "Component not registered before use.");

        GetComponentType<T>()->RemoveData(entity);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) != _componentTypes.end()
               && "Component not registered before use.");

        return GetComponentType<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity) {
        // notify each component array that an entity has been destroyed
        for(auto const & pair : _componentArrays){
            auto const& componentArray = pair.second;
            componentArray->EntityDestroyed(entity);
        }
    }
};


#endif //ECS_TOOLS_COMPONENT_MANAGER_HPP
