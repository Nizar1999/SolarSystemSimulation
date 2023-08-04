#pragma once
#include "rendering_context.h"

namespace Input
{
	void initializeInput();
	void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	void processInputPerFrame();
};
