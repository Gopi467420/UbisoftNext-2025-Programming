#include "Shape.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "app.h"

#include <cmath>
#include <vector>

static constexpr float PI_F = 3.14159265358979323846f;

namespace Shape
{
    // -------------------------
    // Color conversion
    // -------------------------
    void GetColorRGB(ShapeColor color, float& r, float& g, float& b)
    {
        switch (color)
        {
        case ShapeColor::White:   r = 1; g = 1; b = 1; break;
        case ShapeColor::Black:   r = 0; g = 0; b = 0; break;
        case ShapeColor::Red:     r = 1; g = 0; b = 0; break;
        case ShapeColor::Green:   r = 0; g = 1; b = 0; break;
        case ShapeColor::Blue:    r = 0; g = 0; b = 1; break;
        case ShapeColor::Yellow:  r = 1; g = 1; b = 0; break;
        case ShapeColor::Cyan:    r = 0; g = 1; b = 1; break;
        case ShapeColor::Magenta: r = 1; g = 0; b = 1; break;
        case ShapeColor::Orange:  r = 1; g = 0.5f; b = 0; break;
        case ShapeColor::Purple:  r = 0.5f; g = 0; b = 1; break;
        case ShapeColor::Gray:    r = 0.5f; g = 0.5f; b = 0.5f; break;
        default:                  r = 1; g = 1; b = 1; break;
        }
    }

    // -------------------------
    // Helpers
    // -------------------------
    static Vector2 ToScreen(const Vector2& worldPt, const Camera2D& cam)
    {
        return CoordinateConversion::CameraToScreen(
            CoordinateConversion::WorldToCamera(worldPt, cam));
    }

    static Vector2 Centroid(const std::vector<Vector2>& pts)
    {
        Vector2 c(0, 0);
        for (const auto& p : pts) c += p;
        return c * (1.0f / (float)pts.size());
    }

    static void DrawTri(const Vector2& a, const Vector2& b, const Vector2& c, float r, float g, float bb)
    {
        App::DrawTriangle(
            a.x, a.y, 0, 1,
            b.x, b.y, 0, 1,
            c.x, c.y, 0, 1,
            r, g, bb,
            r, g, bb,
            r, g, bb,
            false);
    }

    static void DrawQuad2Tri(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, float r, float g, float bb)
    {
        DrawTri(a, b, c, r, g, bb);
        DrawTri(a, c, d, r, g, bb);
    }

    static void FillTopFan(const std::vector<Vector2>& top, float r, float g, float bb)
    {
        if (top.size() < 3) return;
        Vector2 c = Centroid(top);
        for (size_t i = 0; i < top.size(); ++i)
        {
            const Vector2& a = top[i];
            const Vector2& b = top[(i + 1) % top.size()];
            DrawTri(c, a, b, r, g, bb);
        }
    }

    
    static void DrawThickLine(
        const Vector2& a,
        const Vector2& b,
        float thickness,
        float r, float g, float bb)
    {
        Vector2 dir = b - a;
        float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
        if (len < 0.0001f) return;

        dir = dir * (1.0f / len);

        // perpendicular
        Vector2 n(-dir.y, dir.x);
        n = n * (thickness * 0.5f);

        Vector2 v1 = a + n;
        Vector2 v2 = a - n;
        Vector2 v3 = b - n;
        Vector2 v4 = b + n;

        // two triangles
        DrawTri(v1, v2, v3, r, g, bb);
        DrawTri(v1, v3, v4, r, g, bb);
    }
    static void DrawTopOutlineBlack(const std::vector<Vector2>& top)
    {
        if (top.size() < 2) return;

        for (size_t i = 0; i < top.size(); ++i)
        {
            const Vector2& a = top[i];
            const Vector2& b = top[(i + 1) % top.size()];

            DrawThickLine(a, b, 10, 0, 0, 0); // thickness = 3
        }
    }


    // Main 3D builder: sides + top + black outline
    static void Draw3DFromTopPolygon(const std::vector<Vector2>& top, float topR, float topG, float topB, float depthPx)
    {
        if (top.size() < 3) return;

        // depth in SCREEN pixels (do not multiply by zoom)
        Vector2 depth(depthPx, depthPx * 0.6f);

        // bottom polygon = offset
        std::vector<Vector2> bottom;
        bottom.reserve(top.size());
        for (const auto& v : top) bottom.push_back(v + depth);

        // Side color = darker (simple)
        float sideR = topR * 0.55f;
        float sideG = topG * 0.55f;
        float sideB = topB * 0.55f;

        // 1) sides
        for (size_t i = 0; i < top.size(); ++i)
        {
            const Vector2& a = top[i];
            const Vector2& b = top[(i + 1) % top.size()];
            const Vector2& c = bottom[(i + 1) % top.size()];
            const Vector2& d = bottom[i];
            DrawQuad2Tri(a, b, c, d, sideR, sideG, sideB);
        }

        // 2) top
        FillTopFan(top, topR, topG, topB);

        // 3) black outline (top boundary)
        DrawTopOutlineBlack(top);
    }

    // -------------------------
    // PUBLIC 3D FUNCTIONS
    // -------------------------
    void DrawBox3D(float worldX, float worldY, float width, float height, ShapeColor color, float depthPx)
    {
        Camera2D& cam = GameManager::Get().GetActiveScene().GetCamera();

        float r, g, b;
        GetColorRGB(color, r, g, b);

        Vector2 c = ToScreen({ worldX, worldY }, cam);

        // world -> screen
        float hw = (width * 0.5f) * cam.GetCameraZoom();
        float hh = (height * 0.5f) * cam.GetCameraZoom();

        std::vector<Vector2> top;
        top.reserve(4);
        top.push_back({ c.x - hw, c.y - hh });
        top.push_back({ c.x + hw, c.y - hh });
        top.push_back({ c.x + hw, c.y + hh });
        top.push_back({ c.x - hw, c.y + hh });

        Draw3DFromTopPolygon(top, r, g, b, depthPx);
    }
    static Vector2 RotateAround(const Vector2& p, const Vector2& center, float cosA, float sinA)
    {
        Vector2 d = p - center;
        return Vector2(
            center.x + d.x * cosA - d.y * sinA,
            center.y + d.x * sinA + d.y * cosA
        );
    }


    void DrawCircle3D(const Vector2& worldCenter, float radius, ShapeColor color, float depthPx)
    {
        Camera2D& cam = GameManager::Get().GetActiveScene().GetCamera();

        float r, g, b;
        GetColorRGB(color, r, g, b);

        Vector2 c = ToScreen(worldCenter, cam);
        float sr = radius * cam.GetCameraZoom();

        const int segments = 24;
        std::vector<Vector2> top;
        top.reserve(segments);

        const float step = 2.0f * PI_F / (float)segments;
        for (int i = 0; i < segments; ++i)
        {
            float a = step * (float)i;
            top.push_back({ c.x + cosf(a) * sr, c.y + sinf(a) * sr });
        }

        Draw3DFromTopPolygon(top, r, g, b, depthPx);
    }
    void DrawRegularPolygon3D(
        const Vector2& worldCenter,
        int sides,
        float radius,
        float rotationDegrees,
        ShapeColor color,
        float depthPx)
    {
        if (sides < 3) sides = 3;

        Camera2D& cam = GameManager::Get().GetActiveScene().GetCamera();

        float r, g, b;
        GetColorRGB(color, r, g, b);

        Vector2 c = ToScreen(worldCenter, cam);

        // world -> screen
        float sr = radius * cam.GetCameraZoom();

        // Create unrotated polygon in screen space
        const float step = 2.0f * PI_F / (float)sides;
        const float base = -PI_F * 0.5f; // points "up" initially

        std::vector<Vector2> top;
        top.reserve((size_t)sides);

        for (int i = 0; i < sides; ++i)
        {
            float a = base + step * (float)i;
            top.push_back({ c.x + cosf(a) * sr, c.y + sinf(a) * sr });
        }

        // Apply extra rotationDegrees around center
        float rotRad = rotationDegrees * PI_F / 180.0f;
        float cosA = cosf(rotRad);
        float sinA = sinf(rotRad);

        for (auto& v : top)
            v = RotateAround(v, c, cosA, sinA);

        // Build 3D + outline
        Draw3DFromTopPolygon(top, r, g, b, depthPx);
    }
}
