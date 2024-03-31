#pragma once

#include "Hyperion.hpp"

namespace Hyperion {

	class MenubarWidget 
	{
	public:
		MenubarWidget();

		void Draw();
	private:
		bool BeginMenubar(const ImRect& barRectangle);
		void EndMenubar();
	};

}