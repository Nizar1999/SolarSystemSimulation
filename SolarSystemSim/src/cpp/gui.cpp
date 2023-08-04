#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "rendering_context.h"

#include "gui.h"

void Gui::beginGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImVec4 newBgColor(0.0f, 0.0f, 0.0f, 0.0f);
	ImVec4 newTitleBarColor(0.0f, 0.0f, 0.0f, 0.7f);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = newBgColor;

	style.Colors[ImGuiCol_TitleBg] = newTitleBarColor; // For title bar background
	style.Colors[ImGuiCol_TitleBgActive] = newTitleBarColor; // For active title bar background
	style.Colors[ImGuiCol_TitleBgCollapsed] = newTitleBarColor; // For collapsed title bar background

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::Begin("Configuration");
}

void Gui::renderGuiFrame()
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Gui::toggleDebugMenu()
{
	GLFWwindow* window = RenderingContext::m_window;
	RenderingContext::m_focusGUI = !RenderingContext::m_focusGUI;
	if (!RenderingContext::m_focusGUI)
	{
		glfwSetCursorPos(window, RenderingContext::m_lastX, RenderingContext::m_lastY);
	}
	else
	{
		// Calculate the center position
		double centerX = static_cast<double>(RenderingContext::m_width) / 2.0;
		double centerY = static_cast<double>(RenderingContext::m_height) / 2.0;

		// Set the mouse position to the center of the window
		glfwSetCursorPos(window, centerX, centerY);
	}
}

void Gui::addSliderFloat(std::string_view title, float* val, float min, float max)
{
	ImGui::SliderFloat(title.data(), val, min, max);
}

void Gui::addColorEdit(std::string_view title, float val[4])
{
	ImGui::ColorEdit4(title.data(), val);
}

void Gui::addCombo(std::string_view title, std::vector<const char*>& items, int& selectedItem)
{
	ImGui::Combo(title.data(), &selectedItem, items.data(), items.size());
}

void Gui::addCheckbox(std::string_view title, bool& val)
{
	ImGui::Checkbox(title.data(), &val);
}

void Gui::addButton(std::string_view title, const std::function<void()>& lambda)
{
	if (ImGui::Button(title.data()))
	{
		lambda();
	}
}
