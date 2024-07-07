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

    

public:
};


#endif //ECS_TOOLS_COMPONENT_ARRAY_HPP
