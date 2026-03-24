#pragma once
#include <string>
#include "./Framework/GObject/GObject.h"

class UIWidget : public GObject
{
public:
    virtual ~UIWidget() = default;

    void SetVisible(bool v) { m_visible = v; }
    bool IsVisible() const { return m_visible; }

    void SetText(const std::string& t) { m_text = t; }
    const std::string& GetText() const { return m_text; }

private:
    bool m_visible = true;
    std::string m_text;
};
