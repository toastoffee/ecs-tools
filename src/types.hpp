/**
  ******************************************************************************
  * @file           : types.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/6
  ******************************************************************************
  */



#ifndef ECS_TOOLS_TYPES_HPP
#define ECS_TOOLS_TYPES_HPP


#include <cstdint>
#include <bitset>

// simple type alias
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

// define maximum of entities and components
const Entity MAX_ENTITIES = 5000;
const ComponentType MAX_COMPONENTS = 32;

// record the components of one entity has
using Signature = std::bitset<MAX_COMPONENTS>;



#endif //ECS_TOOLS_TYPES_HPP
