/**
  ******************************************************************************
  * @file           : system.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/6
  ******************************************************************************
  */



#ifndef ECS_TOOLS_SYSTEM_HPP
#define ECS_TOOLS_SYSTEM_HPP


#include "types.hpp"

#include <set>

class System {
public:
    std::set<Entity> _entities;
};


#endif //ECS_TOOLS_SYSTEM_HPP
