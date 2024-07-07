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
    std::shared_ptr<ComponentArray<T>> GetComponentArray(){
        const char* typeName = typeid(T).name();

        assert(_componentTypes.find(typeName) != _componentTypes.end()
                && "component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
    }
};


#endif //ECS_TOOLS_COMPONENT_MANAGER_HPP
