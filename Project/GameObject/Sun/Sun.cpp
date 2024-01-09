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
	sun_.color = color_;
	LightingManager::AddList(sun_);
}

