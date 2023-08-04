#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "gui.h"

void Gui::beginGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::addSliderFloat(std::string_view title, float* val, float min, float max)
{
	ImGui::SliderFloat(title.data(), val, min, max);
}

void Gui::addColorEdit(std::string_view title, float val[4])
{
	ImGui::ColorEdit4(title.data(), val);
}

void Gui::renderGuiFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
