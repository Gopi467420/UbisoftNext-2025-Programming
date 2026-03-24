#include "UIManager.h"
#include "../Game/Math/Vector/Vector2.h"
#include "App.h"

void UIManager::Render(Vector2 pos,std::string string )
{
    App::Print((int)pos.x, (int)pos.y, string.c_str());
}


void UIManager::SetText(std::vector<std::string>& textsA,uint32_t id, const std::string& text)
{
    if (id < textsA.size()) textsA[id] = text;
}
void UIManager::SetPosition(std::vector<Vector2>& posA, uint32_t id, const Vector2& pos)
{
    if (id < posA.size()) posA[id] = pos;
}
void UIManager::SetVisible(std::vector<bool>& visibleA, uint32_t id, bool visible)
{
    if (id < visibleA.size()) visibleA[id] = visible;
}