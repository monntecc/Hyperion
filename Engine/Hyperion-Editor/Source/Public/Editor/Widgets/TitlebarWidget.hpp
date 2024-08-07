#pragma once

#include "Hyperion.hpp"

#include "Editor/Widgets/MenubarWidget.hpp"

namespace Hyperion {

	class TitlebarWidget {
	public:
		TitlebarWidget();

		// Window custom theme
		void DrawUITitlebar();

        bool IsTitlebarHovered() { return m_TitleBarHovered; }
	private:
		bool m_TitleBarHovered = false;

		Ref<Texture2D> m_AppHeaderIcon;
		Ref<Texture2D> m_IconClose;
		Ref<Texture2D> m_IconMinimize;
		Ref<Texture2D> m_IconMaximize;
		Ref<Texture2D> m_IconRestore;

		// Widgets
		MenubarWidget m_MenubarWidget;
	};

}