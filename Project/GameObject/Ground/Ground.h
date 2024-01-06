#pragma once
#include"Game3dObject.h"


class Ground
{
public:
	Ground() {};
	~Ground() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_{};

};