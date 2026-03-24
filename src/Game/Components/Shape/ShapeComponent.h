#pragma once
#include <variant>
#include <vector>
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/FrameWork/EntityComponent/EntityComponent.h"
#include "../Game/FrameWork/Structs/Structs.h"



struct Camera2D;
class ShapeComponent : public EntityComponent
{
public:
     ShapeComponent(Entity* owner, ShapeData shape);
    ~ShapeComponent();

    const ShapeData& GetShape() const { return m_shape; }
    void SetShape(ShapeData data) { m_shape = data; }
    void SetShapenew(const ShapeData& shape);
private:
    ShapeData m_shape;

public:
    void Render(Camera2D& camera) override;
    float ComputeBoundingRadius() const;
};
