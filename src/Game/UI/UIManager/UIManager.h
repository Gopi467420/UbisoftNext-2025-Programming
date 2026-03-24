#pragma once
#include <vector>
#include <string>

class UIWidget;
class Vector2;

class UIManager
{
public:
  
	

	void Render(Vector2 pos, std::string string);

	void SetText(std::vector<std::string>& textsA, uint32_t id, const std::string& text);

	void SetPosition(std::vector<Vector2>& posA, uint32_t id, const Vector2& pos);

	void SetVisible(std::vector<bool>& visibleA, uint32_t id, bool visible);



	uint32_t CreateWidget(Vector2 pos, const std::string& text, bool visible);

};
