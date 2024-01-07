#pragma once

#include"Game3dObject.h"

#include"Input.h"
#include"GameObject/wepon/Weapon.h"
#include"OBBCollider.h"

class Player : public OBBCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update(const ViewProjection &view);

	void Draw(ViewProjection view);

	const WorldTransform &GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* view) { CameraViewProjection_ = view; }

	Vector3 GetWorldPosition() override{ return worldTransform_.translate; }

	void OnCollision(uint32_t id) override;

private:

	void Control(const ViewProjection& view);

	float LerpShortAngle(const float& a, const float& b, float t);
	
	void Attack();

	bool isAttack_ = false;

	int32_t AttackCoolTime_ = 0;
	const int32_t AttackCoolTimeMax_ = 120;

	uint32_t modelbodyHandle_ = 0;
	float destinationAngleY_ = 0.0f;

	WorldTransform worldTransform_{};
	unique_ptr<Game3dObject>model_ = nullptr;
	const ViewProjection* CameraViewProjection_ = nullptr;

	XINPUT_STATE joyState_{};

	unique_ptr<Weapon>weapon_ = nullptr;

};