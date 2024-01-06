#pragma once
#include"Light/LightingManager.h"

class Sun
{
public:
	Sun() {};
	~Sun() {};

	void Initialize();

	void Update();

private:

	PointLight_param sun_;
};