#include "ShapeComponent.h"
#include "../Game/FrameWork/Entity/Entity.h"
#include <variant>

#include "../Game/FrameWork/Shapes/Shape.h"



ShapeComponent::ShapeComponent(Entity* owner,ShapeData shape) : EntityComponent(owner),m_shape(shape)
{
}

ShapeComponent::~ShapeComponent()
{
}

void ShapeComponent::SetShapenew(const ShapeData& shape)
{
    m_shape = shape;
}

void ShapeComponent::Render(Camera2D& camera)
{
    auto lamdafunc = [&](const auto& s)
        {
            using T = std::decay_t<decltype(s)>;

            if constexpr (std::is_same_v<T, SD_CircleShape>)
            {
                Shape::DrawCircle3D(GetOwner()->GetPosition(), s.radius, s.color,0);
            }
            else if constexpr (std::is_same_v<T, SD_BoxShape>)
            {
                Shape::DrawBox3D(GetOwner()->GetPosition().x, GetOwner()->GetPosition().y, s.width, s.height, s.color, 8);
            }
            else if constexpr (std::is_same_v<T, SD_PolygonShape>)
            {
                Shape::DrawRegularPolygon3D(GetOwner()->GetPosition(), s.sides, s.radius, GetOwner()->GetRotationDeg(), s.color, 1);

                //Shape::DrawPolygon(GetOwner()->GetPosition(), s.vertices, 0.0f);
            }
        };

    std::visit(lamdafunc, m_shape);
}
 

float ShapeComponent::ComputeBoundingRadius() const
{
    return std::visit([](const auto& s) -> float
        {
            using T = std::decay_t<decltype(s)>;

            if constexpr (std::is_same_v<T, SD_CircleShape>)
            {
                return std::max(0.0f, s.radius);
            }
            else if constexpr (std::is_same_v<T, SD_BoxShape>)
            {
                const float hw = std::max(0.0f, s.width) * 0.5f;
                const float hh = std::max(0.0f, s.height) * 0.5f;
                return std::sqrt(hw * hw + hh * hh); // half diagonal
            }
            else if constexpr (std::is_same_v<T, SD_PolygonShape>)
            {
                // If radius means center->vertex, that's already the bounding radius.
                return std::max(0.0f, s.radius);
            }
            else
            {
                return 0.0f;
            }
        }, m_shape);
}

