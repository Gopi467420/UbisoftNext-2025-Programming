#pragma once
#include "../Game/Math/Vector/Vector2.h"


struct vector;
struct Camera2D;

class GObject
{
public:

    GObject() = default;
    virtual ~GObject() = default;
    
  
protected:
    Vector2  m_position{ 0, 0 };    
    bool     m_pendingDestroy = false;

    virtual void OnPositionChanged(const Vector2& oldPos, const Vector2& Pos) {}

public:
    
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void Render(Camera2D& camera) {};
    virtual void Shutdown() {};

    bool IsPendingDestroy() const;
    void MarkPendingDestroy();
    const Vector2& GetPosition() const;
    virtual void SetPosition(const Vector2& pos);

};
