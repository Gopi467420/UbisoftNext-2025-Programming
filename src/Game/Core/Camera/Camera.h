#pragma once
#include "../Game/Math/Vector/Vector2.h"
#include <cstdlib> // rand
#include <cmath>   // fabsf

struct Camera2D
{
    Vector2 m_position;   // base camera center (world space)
    float   m_zoom = 1.0f;

    // --- Shake state ---
    Vector2 m_shakeOffset{ 0, 0 };
    float   m_shakeTimeLeft = 0.0f;
    float   m_shakeDuration = 0.0f;
    float   m_shakeStrength = 0.0f;     // world units (like pixels in world)
    float   m_shakeFrequency = 45.0f;   // shakes per second
    float   m_shakeAccumulator = 0.0f;

public:
    float GetCameraZoom() const { return m_zoom; }

    // IMPORTANT: for rendering/conversion, use this position (base + shake)
    Vector2 GetPosition() const { return m_position + m_shakeOffset; }

    // For camera follow system: set the base position
    void SetPosition(Vector2 newPosition) { m_position = newPosition; }

    // Start shake
    // strength: how far camera can move (world units)
    // duration: seconds
    // frequency: how often new random offset is chosen
    void StartShake(float strength, float duration, float frequency = 45.0f)
    {
        if (duration <= 0.0f || strength <= 0.0f)
            return;
        
        // If a stronger shake comes in, override strength
        m_shakeStrength = (strength > m_shakeStrength) ? strength : m_shakeStrength;

        m_shakeDuration = duration;
        m_shakeTimeLeft = duration;
        m_shakeFrequency = frequency;
        m_shakeAccumulator = 0.0f;
    }

    void StopShake()
    {
        m_shakeTimeLeft = 0.0f;
        m_shakeOffset = Vector2(0, 0);
        m_shakeStrength = 0.0f;
        m_shakeAccumulator = 0.0f;
    }

    bool IsShaking() const { return m_shakeTimeLeft > 0.0f; }

    // Call every frame
    void Update(float dt)
    {
        if (m_shakeTimeLeft <= 0.0f)
        {
            m_shakeOffset = Vector2(0, 0);
            m_shakeStrength = 0.0f;
            return;
        }

        m_shakeTimeLeft -= dt;
        if (m_shakeTimeLeft < 0.0f) m_shakeTimeLeft = 0.0f;

        // Fade out (1 -> 0)
        float t = (m_shakeDuration > 0.0001f) ? (m_shakeTimeLeft / m_shakeDuration) : 0.0f;
        float currentStrength = m_shakeStrength * t;

        // Pick new random offset at frequency
        m_shakeAccumulator += dt;
        float interval = (m_shakeFrequency > 0.0001f) ? (1.0f / m_shakeFrequency) : 0.0f;

        if (interval <= 0.0f)
        {
            m_shakeOffset = Vector2(0, 0);
            return;
        }

        while (m_shakeAccumulator >= interval)
        {
            m_shakeAccumulator -= interval;

            // random in [-1,1]
            float rx = (float)rand() / (float)RAND_MAX; // [0,1]
            float ry = (float)rand() / (float)RAND_MAX; // [0,1]
            rx = rx * 2.0f - 1.0f;
            ry = ry * 2.0f - 1.0f;

            m_shakeOffset = Vector2(rx * currentStrength, ry * currentStrength);
        }

        // end
        if (m_shakeTimeLeft <= 0.0f)
        {
            StopShake();
        }
    }
};
