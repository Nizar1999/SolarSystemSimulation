/*
 * Description: Debug menu view (presenting data, capturing input)
 */

#pragma once
 //TODO:refactor so we can remove these includes
#include "orbit_renderer.h"
#include "gui.h"

namespace ConfigurationView
{
	void displayConfigurationOptions(std::vector<const char*>& items, int& selectedItem);
	void addResetOrbitsButton(std::function<void()> buttonCallback);
};

