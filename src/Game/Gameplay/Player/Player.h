#pragma once

#include "../Game/FrameWork/Entity/Entity.h"
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/Framework/Interfaces/Interfaces.h"
#include "../Game/Components/Physics/MovementComponents/CharacterMovementComponent.h"



struct Camera2D;

class Player : public Entity
{
public:
    Player();

private:   
    
    ECharacterState PlayerState;    
    void Move(float deltaTime) ;
    
 //variables
private:

    bool bFaceMouse;
    bool Debug;
    bool bCanMove();
    bool bCanShoot();    
    
    float m_rotation;
    float m_speed;
    Vector2 m_playerfacing = Vector2(1.0f, 0.0f);
    CharacterMovementComponent m_movementcomponent;

   
    void HandleMovingState(float deltaTime);
    void HandlePlayerState(const float deltaTime);

public:
    
    void Init() override;
    void Update(const float deltaTime) override ;
   
    void Render(Camera2D& camera) override;

public:
    // Accessors
    Vector2 GetSpawnPosition();
    float GetFacingDirection();

    void FaceMouse();
  

    void SetPlayerFacing(Vector2  newFacing);\
   

    // Inherited via Entity
    ECollisionLayer GetCollisionLayer() const override;
    uint32_t GetCollisionMask() const override;
    ECollisionResponse GetCollisionResponse() const override;   
    ShapeData GetDefaultShape() const override;
    void OnCollision(Entity* other) override;
    EMobility GetMobility() const override;

    float GetRotationDeg() override;

};
