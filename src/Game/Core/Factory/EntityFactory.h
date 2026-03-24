// This Script Manufactures Entities
#pragma once
#include <memory>

class StaticEntity;
class Player;
class GObject;
class Scene;

class EntityFactory
{
public:
     EntityFactory();

     std::unique_ptr<GObject> CreatePlayer();
     std::unique_ptr<GObject> CreateWorldObject();
     std::unique_ptr<GObject> CreateBase();

};

