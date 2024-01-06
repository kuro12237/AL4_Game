#pragma once

#include"Game3dObject.h"

#include"Input.h"

class Player
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update(const ViewProjection &view);

	void Draw(ViewProjection view);

	const WorldTransform &GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* view) { CameraViewProjection_ = view; }

private:

	void Control(const ViewProjection& view);

	float LerpShortAngle(const float& a, const float& b, float t);
	
	uint32_t modelbodyHandle_ = 0;
	float destinationAngleY_ = 0.0f;

	WorldTransform worldTransform_{};
	unique_ptr<Game3dObject>model_ = nullptr;
	const ViewProjection* CameraViewProjection_ = nullptr;


	XINPUT_STATE joyState_{};

};