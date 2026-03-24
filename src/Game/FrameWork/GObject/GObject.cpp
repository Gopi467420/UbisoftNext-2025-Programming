#include "GObject.h"

bool  GObject::IsPendingDestroy() const { return m_pendingDestroy; }
void  GObject::MarkPendingDestroy() { m_pendingDestroy = true; }
const Vector2& GObject::GetPosition() const { return m_position; }
void GObject::SetPosition(const Vector2& pos)
{
    OnPositionChanged(m_position,pos);
    m_position = pos;
    
}
