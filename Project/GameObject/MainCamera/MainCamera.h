#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"VectorTransform.h"
#include"Input.h"

class MainCamera
{
public:

	void Initialize();

	void Update(const WorldTransform&worldTransform);

	ViewProjection const& GetViewProjection() { return viewProjection_; }


private:

	const WorldTransform* target_ = {};
	ViewProjection viewProjection_;
	Vector3 offset_ = {};
};
