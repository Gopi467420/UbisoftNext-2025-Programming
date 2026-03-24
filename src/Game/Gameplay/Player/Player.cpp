#include "Player.h"
#include "../Game/Components/Physics/MovementComponents/CharacterMovementComponent.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Math/Utils/Utils.h"
#include "App.h"

Player::Player(): m_movementcomponent(this), PlayerState (ECharacterState:: ECS_Moving){}
void Player::Init()
{
    m_position = Vector2(50, 50);
    Entity::Init();
   
}

void Player::Update(const float deltaTime)
{
    Entity::Update(deltaTime);
    HandlePlayerState(deltaTime);

}

void Player::Render(Camera2D& camera){
    Entity::Render(camera); App::Print(CoordinateConversion::WorldToScreen(GetPosition(), camera).x - 5, CoordinateConversion::WorldToScreen(GetPosition(), camera).y -5 , "P",0,0,0);
}

void Player::HandlePlayerState(const float deltaTime)
{
    switch (PlayerState)
    {
    case ECharacterState::ECS_Dead: break;
    case ECharacterState::ECS_Idle: break;
    case ECharacterState::ECS_Moving: HandleMovingState(deltaTime); break;
    case ECharacterState::ECS_Attack: break;
    }
}

void Player::Move(float deltaTime)
{

    float speed = 400;

    Vector2 input( App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

    // Dead zone
    if (fabs(input.x) < 0.5f) input.x = 0.0f;
    if (fabs(input.y) < 0.5f) input.y = 0.0f;

    // Normalize so diagonal is not faster
    if (input.LengthSquared() > 1.0f)
        input = input.Normalize();

   
    Vector2 desiredVelocity = input * speed;

    // Movement component handles sliding,blocking, applying deltaTime
    m_movementcomponent.MoveDelta(desiredVelocity, deltaTime);


        
}

  void Player::HandleMovingState(float deltaTime)
{
    Move(deltaTime);
    FaceMouse();
    
}

  void Player::OnCollision(Entity* other)
  {
    
  }


void Player::SetPlayerFacing(Vector2  newFacing)
{
    m_playerfacing = newFacing;
}
ECollisionLayer Player::GetCollisionLayer() const { return ECollisionLayer::Player; }
uint32_t Player::GetCollisionMask() const { return DefineCollisionMask({ ECollisionLayer::Gem, ECollisionLayer::Enemy }); }
ECollisionResponse Player::GetCollisionResponse() const { return ECollisionResponse::ECR_Trigger; }
ShapeData Player::GetDefaultShape() const { return SD_PolygonShape{3,25,ShapeColor::White}; }
EMobility Player::GetMobility() const
{
    return EMobility::Movable;
}
float Player::GetRotationDeg()
{
    return m_rotation;
}
bool Player::bCanMove() { return false; }
bool Player::bCanShoot() { return true; }
Vector2 Player::GetSpawnPosition()
{
    float offset = 100;
    return m_position + m_playerfacing * offset;
}
float Player::GetFacingDirection()
{
    return 0;

}

void Player::FaceMouse()
{
    // 1. Get camera
    Camera2D& cam =     GameManager::Get().GetActiveScene().GetCamera();

    // 2. Get mouse position in world space
    Vector2 mouseWorld = CoordinateConversion::GetMouseWorld(cam);

    // 3. Direction from player to mouse
    Vector2 playerPos = GetPosition();
    Vector2 dir = mouseWorld - playerPos;

    // Avoid jitter if very close
    if (dir.LengthSquared() < 0.0001f)
        return;

    // 4. Convert direction to angle
    float angleRad = atan2f(dir.y, dir.x);
    float angleDeg = angleRad * 180.0f / 3.14159265f;

    // 5. Apply rotation
    m_rotation = angleDeg +90;
}
  
  


  


