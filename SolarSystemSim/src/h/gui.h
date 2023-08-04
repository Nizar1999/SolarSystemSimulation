#pragma once
#include <string_view>
#include <vector>
#include <functional>

namespace Gui
{
	void beginGuiFrame();
	void addSliderFloat(std::string_view title, float* val, float min, float max);
	void addColorEdit(std::string_view title, float val[4]);
	void renderGuiFrame();
	void addCombo(std::string_view title, std::vector<const char*>& items, int& selectedItem);
	void addCheckbox(std::string_view title, bool& val);
	void addButton(std::string_view title, const std::function<void()>& lambda);
}
