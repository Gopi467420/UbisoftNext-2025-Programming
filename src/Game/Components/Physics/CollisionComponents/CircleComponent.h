#pragma once

#include "../Game/Framework/EntityComponent/EntityComponent.h"
#include "../Game/Framework/Enums/GameplayEnums.h"
#include "../Game/Math/Vector/Vector2.h"

class Entity;

struct Camera2D;

class CircleComponent : public EntityComponent
{
public:
    CircleComponent( Entity* owner,float radius, ECollisionLayer layer,uint32_t mask,ECollisionResponse preset);
    ~CircleComponent();

private:
    ECollisionResponse m_preset;
    bool m_registered = false;
    ECollisionLayer m_layer;
    float m_radius;
    uint32_t m_mask;


  public:

    bool OverlapsAt(const Vector2& testCenter, const CircleComponent& other) const;   
    void SetRegistered( bool value) {  m_registered = value; }
    bool CanCollideWith(const CircleComponent& other) const;
    const Vector2& CircleComponent::GetWorldPosition() const; 
    bool IsRegistered() { return m_registered; }
    ECollisionResponse GetCollisionPreset() const;
    float GetRadius() const;
    void SetRadius(float radius);
  
 public:   
      void Render(Camera2D& camera) override;

   

public:
   
};
