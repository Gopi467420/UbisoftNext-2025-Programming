//Collision Box components attached to all entities to calculate collision behaviour using AABB method 
//Collision box auutomatically excutes there collion function based on :ECollisionPreset = overlap, block and ignore.
#pragma once
#include "../Game/FrameWork/EntityComponent/EntityComponent.h"
#include"../Game/FrameWork/Enums/GameplayEnums.h"
#include <functional> // for declaring delegates



class Entity;
class GridHash;


class CollisionBox :public EntityComponent
{
    /*
    * //Constructors
public:
    CollisionBox(Entity* owner, ECollisionResponse startcollisionpreset, float width, float height, GridHash* grid);
  

public:
    //Delegate for Collision Call
    std::function<void(CollisionBox* Other)> OnCollision;
    
    //Functions
public:
    bool OverlapsAt(const Vector2& testPos, CollisionBox& other) const;

private:    
    float m_width;
    float m_height;
    GridHash* m_worldgrid;
    ECollisionResponse m_collisionpreset;

   //Accesors
public:
    float GetWidth() { return m_width; }
    float GetHeight() { return m_height; }
   //k void SetPosition(const Vector2 newPosition) override;
    ECollisionResponse GetCollisionPreset() { return m_collisionpreset; }
    void SetCollisionPreset(ECollisionResponse newPreset) { m_collisionpreset = newPreset; }

public:

   
 
    virtual void Update(const float deltaTime) override;
    virtual void Render() override;    //Used only for debug
    */
 
 

};