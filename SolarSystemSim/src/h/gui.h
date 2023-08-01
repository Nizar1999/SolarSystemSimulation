#pragma once
#include <string_view>

namespace Gui
{
	void beginGuiFrame();
	void addSliderFloat(std::string_view title, std::string_view units, float& val, float min, float max);
	void addColorEdit(std::string_view title, float val[4]);
	void renderGuiFrame();
}
