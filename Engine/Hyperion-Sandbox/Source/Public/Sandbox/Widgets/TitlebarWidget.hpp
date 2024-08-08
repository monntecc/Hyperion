#pragma once

#include "Hyperion.hpp"

class TitlebarWidget
{
public:
    TitlebarWidget();

    // Window custom theme
    void DrawUITitlebar();

    bool IsTitlebarHovered() { return m_TitleBarHovered; }
private:
    bool m_TitleBarHovered = false;

    Hyperion::Ref<Hyperion::Texture2D> m_AppHeaderIcon;
    Hyperion::Ref<Hyperion::Texture2D> m_IconClose;
    Hyperion::Ref<Hyperion::Texture2D> m_IconMinimize;
    Hyperion::Ref<Hyperion::Texture2D> m_IconMaximize;
    Hyperion::Ref<Hyperion::Texture2D> m_IconRestore;
};
