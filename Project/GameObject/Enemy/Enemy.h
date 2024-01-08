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

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t ModelHandle_ = 0;


};
