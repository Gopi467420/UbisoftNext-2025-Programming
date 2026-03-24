#pragma once
#include "../Game/Framework/GObject/GObject.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "../Game/FrameWork/Interfaces/Interfaces.h"
#include "../Game/Components/Shape/ShapeComponent.h"
#include <vector>
#include <memory>

class EntityComponent;
class CircleComponent;
class ShapeComponent;

enum class EMobility { None, Static, Movable };

struct Camera2D;
class Entity : public GObject, public IDamagable
{
public:
    Entity();
    virtual ~Entity();

private:
  
    EMobility m_mobility = EMobility::None;
protected:
    std::vector<std::unique_ptr<EntityComponent>> m_components;

protected:
    virtual ECollisionResponse GetCollisionResponse() const = 0;   
    virtual uint32_t GetCollisionMask() const = 0;
    virtual ShapeData GetDefaultShape() const = 0;
    virtual EMobility GetMobility() const = 0;
    float ComputeColliderRadius();
    ShapeData m_shape;
    void SetShapeData(ShapeData m_shape);


public:
    virtual ECollisionLayer GetCollisionLayer() const = 0;
    const CircleComponent* GetCollider() const;
    CircleComponent* GetCollider();
    template<typename T, typename... Args> T& AddComponent(Args&&... args);
    template<typename T> const T* GetComponent() const;
    template<typename T> T* GetComponent() ;
    
public:
    //Core Events
    virtual void Init() override;
    virtual void Update(float deltaTime) override ;
    virtual void Render(Camera2D& camera) override;
    virtual void Shutdown() override;

    //CollisionEvents
    virtual void OnOverlapBegin(Entity* other) {}
    virtual void OnOverlapStay(Entity* other) {}
    virtual void OnOverlapEnd(Entity* other) {}
    virtual void OnHit(Entity* other) {}
    virtual void OnCollision(Entity* other) = 0;

public:
    virtual void DefineBaseComponents();
    void RegisterColliderForNonPooledEntities();
    void OnPositionChanged(const Vector2& oldPos,const Vector2& Pos) override;


    // Inherited via IDamagable
   virtual void TakeDamage(float amount) override {};
   
   virtual float GetDamageAmount() { return 0; };
   virtual void SetDamageAmount(float damage) {};

   virtual float GetRotationDeg() { return 0; };
};

 
template<typename T>
 const T* Entity::GetComponent() const
{
    static_assert(std::is_base_of<EntityComponent, T>::value,"T must derive from EntityComponent");
    for (auto& c : m_components){ if (auto* casted = dynamic_cast<T*>(c.get()))  return casted; }
    return nullptr;
};

 template<typename T>
  T* Entity::GetComponent() 
 {
     static_assert(std::is_base_of<EntityComponent, T>::value, "T must derive from EntityComponent");
     for (auto& c : m_components){ if (auto* casted = dynamic_cast<T*>(c.get()))  return casted; }
     return nullptr;
 };

template<typename T, typename... Args>
 T& Entity::AddComponent(Args&&... args)
{
    static_assert(std::is_base_of_v<EntityComponent, T>,"T must derive from EntityComponent");
    auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
   
    T& ref = *component;
    m_components.push_back(std::move(component));
    return ref;
}