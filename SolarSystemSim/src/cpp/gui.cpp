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

void Gui::addSliderFloat(std::string_view title, std::string_view units, float& val, float min, float max)
{
	ImGui::Text(title.data());
	ImGui::SliderFloat(units.data(), &val, min, max);
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
