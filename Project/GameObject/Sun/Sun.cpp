#include "Sun.h"

void Sun::Initialize()
{
	sun_.intencity = 2.2f;
	sun_.radious = 320.0f;
	sun_.decay = 4.7f;
	sun_.position.y = 64.0f;
}

void Sun::Update()
{
	ImGui::Begin("light");
	ImGui::ColorPicker4("color", &sun_.color.x);
	ImGui::DragFloat("intencity", &sun_.intencity,-0.1f,0.1f);
	ImGui::DragFloat("decay", &sun_.decay, -0.1f, 0.1f);

	ImGui::DragFloat("radiouns", &sun_.radious, -0.1f, 0.1f);
	ImGui::DragFloat3("pos", &sun_.position.x, -0.1f, 0.1f);
	ImGui::End();
	//#5F2F2FFF

	sun_.color = color_;
	LightingManager::AddList(sun_);
}

