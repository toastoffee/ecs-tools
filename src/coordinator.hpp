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
        _componentManager =
    }
};


#endif //ECS_TOOLS_COORDINATOR_HPP
