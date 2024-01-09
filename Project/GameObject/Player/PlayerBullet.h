#pragma once
#include"Game3dObject.h"
#include"OBBCollider.h"
#include"ColliderConfig.h"
#include"AudioManager.h"

class PlayerBullet : public OBBCollider
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize(Vector3 pos,Vector3 v);

	void Update();

	void Draw(ViewProjection view);

	bool GetIsAlive() { return isAlive; }

	void OnCollision(uint32_t id)override;

	Vector3 GetWorldPosition()override;
private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_{};
	uint32_t modelHandle_ = 0;
	Vector3 velocity_ = {};

	uint32_t timer_ = 0;
	bool isAlive = true;

	uint32_t soundHandle_ = 0;
};
