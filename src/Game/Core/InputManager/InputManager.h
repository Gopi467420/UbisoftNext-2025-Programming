#pragma once
#include "../Game/Framework/Enums/GameplayEnums.h"
#include <array>
#include <vector>
#include "app.h"

struct InputBinding
{
   
    EInputAction m_action;
    App::Key m_key;          
    int m_mouseButton;
};

class InputManager
{
public:
    void BindKey(EInputAction action, App::Key key);
    void BindMouse(EInputAction action, int mouseButton);

    void Update(float deltaTime);

    bool Down(EInputAction action) const;
    bool Pressed(EInputAction action) const;
    bool Released(EInputAction action) const;

private:
    static constexpr size_t kMaxActions = 256;

    std::vector<InputBinding> m_bindings;

    std::array<bool, kMaxActions> m_down{};
    std::array<bool, kMaxActions> m_pressed{};
    std::array<bool, kMaxActions> m_released{};
    std::array<bool, kMaxActions> m_prevDown{};

    static size_t ToIndex(EInputAction action) { return static_cast<size_t>(action); }
};
