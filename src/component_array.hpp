/**
  ******************************************************************************
  * @file           : component_array.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/7
  ******************************************************************************
  */



#ifndef ECS_TOOLS_COMPONENT_ARRAY_HPP
#define ECS_TOOLS_COMPONENT_ARRAY_HPP

#include "types.hpp"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
private:
    // packed array of components
    std::array<T, MAX_ENTITIES> _componentArray;

    // map from entity ID to array index
    std::unordered_map<Entity, size_t> _entityToIndexMap;

    // map from array index to entity ID
    std::unordered_map<size_t, Entity> _indexToEntityMap;

    // total size of valid entities
    size_t  _size;

public:

    void InsertData(Entity entity, T component) {
        assert(_entityToIndexMap.find(entity) == _entityToIndexMap.end()
                && "Component added to same entity more than once.");

        // add new entry at end
        size_t newIndex = _size;
        _entityToIndexMap[entity] = newIndex;
        _indexToEntityMap[newIndex] = entity;
        _componentArray[newIndex] = component;
        _size++;
    }

    void RemoveData(Entity entity) {
        assert(_entityToIndexMap.find(entity) != _entityToIndexMap.end()
                && "Remove a non-existent component.");

        // update the component array
        size_t removedEntityIndex = _entityToIndexMap[entity];
        size_t lastEntityIndex = _size - 1;
        _componentArray[removedEntityIndex] = _componentArray[lastEntityIndex];

        // update the maps
        Entity lastEntity = _indexToEntityMap[lastEntityIndex];
        _entityToIndexMap[lastEntity] = removedEntityIndex;
        _indexToEntityMap[removedEntityIndex] = lastEntity;

        _entityToIndexMap.erase(entity);
        _indexToEntityMap.erase(lastEntityIndex);

        _size--;
    }

};


#endif //ECS_TOOLS_COMPONENT_ARRAY_HPP
