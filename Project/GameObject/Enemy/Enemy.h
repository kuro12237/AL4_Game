#pragma once
#include"Game3dObject.h"
#include"OBBCollider.h"
#include"ColliderConfig.h"

class Enemy:public OBBCollider
{
public:
	Enemy() {};
	~Enemy() {};

	void Initialize(Vector3 spownPos);

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

	bool GetIsAlive() { return isAlive_; }

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t ModelHandle_ = 0;

	Vector3 velocity_ = {};

	random_device seedGenerator;

	bool isAlive_ = true;
	bool isHit_ = false;
	bool isSpownAnimationFlag_ = true;

};
