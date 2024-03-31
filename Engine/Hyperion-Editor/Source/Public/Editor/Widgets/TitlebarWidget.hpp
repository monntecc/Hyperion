#pragma once

#include "Hyperion.hpp"

namespace Hyperion {

	class TitlebarWidget {
	public:
		TitlebarWidget();

		// Window custom theme
		void DrawUITitlebar();
	private:
		bool m_TitleBarHovered = false;

		Ref<Texture2D> m_AppHeaderIcon;
		Ref<Texture2D> m_IconClose;
		Ref<Texture2D> m_IconMinimize;
		Ref<Texture2D> m_IconMaximize;
		Ref<Texture2D> m_IconRestore;
	};

}