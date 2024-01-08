#pragma once
#include"Light/LightingManager.h"

class Sun
{
public:
	Sun() {};
	~Sun() {};

	void Initialize();

	void Update();

	void SetColor(Vector4 color) { color_ = color; }
private:

	Vector4 color_ = { 1,1,1,1 };
	PointLight_param sun_;
};