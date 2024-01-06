#pragma once
#include"Game3dObject.h"

class Weapon
{
public:
	Weapon() {};
	~Weapon() {};

	void Initialize();

	void Update();

	void Draw(const ViewProjection& view);

	void SetParent(const WorldTransform& worldTransform) { worldTransform_.parent = &worldTransform; }

	const WorldTransform &GetWorldTransform() { return worldTransform_; }

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t modelHandle_ = 0;

};