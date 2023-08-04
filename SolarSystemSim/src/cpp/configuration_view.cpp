#include "configuration_view.h"

void ConfigurationView::displayConfigurationOptions(std::vector<const char*>& items, int& selectedItem)
{
	//Rendering related configurations
	Gui::addSliderFloat("Camera Speed", &RenderingContext::m_camera.MovementSpeed, 0.0f, 100.0f);
	Gui::addSliderFloat("Time Scale", &RenderingContext::m_timeScale, 0.0f, 1.0f);
	Gui::addSliderFloat("Distance Factor", &RenderingContext::m_distanceFactor, 0.0f, 100.0f);
	Gui::addCheckbox("Show Orbits", RenderingContext::m_renderOrbits);

	//Orbit related configuration
	Gui::addColorEdit("Orbit Color", glm::value_ptr(OrbitRenderer::m_color));

	//Camera related configuration
	Gui::addCombo("Camera Position", items, selectedItem);
}

void ConfigurationView::addResetOrbitsButton(std::function<void()> buttonCallback)
{
	Gui::addButton("Reset Orbits", buttonCallback);
}
