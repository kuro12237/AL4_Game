#pragma once

#include"Game3dObject.h"

#include"Input.h"
#include"OBBCollider.h"
#include"ColliderConfig.h"
#include"PlayerBullet.h"
#include"GameObject/HitParticle/HitParticle.h"
#include"GameObject/Player/PlayerBulletLine.h"

enum AnimationPlayerMove
{
	UP,
	DOWN
};

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

	bool GetIsAttack() { return isAttack_; }

	bool GetPrevAttack() { return prevIsAttack; }

	list<shared_ptr<PlayerBullet>>GetBullets() { return bullets_; }

	void ParticleDraw(ViewProjection view);

private:

	void Control(const ViewProjection& view);

	float LerpShortAngle(const float& a, const float& b, float t);
	
	void Attack();

	void AnimationMove();

	bool isAttack_ = false;
	bool prevIsAttack = false;

	int32_t AttackCoolTime_ = 0;
	const int32_t AttackCoolTimeMax_ = 20;

	uint32_t modelbodyHandle_ = 0;
	float destinationAngleY_ = 0.0f;

	WorldTransform worldTransform_{};
	unique_ptr<Game3dObject>model_ = nullptr;
	const ViewProjection* CameraViewProjection_ = nullptr;

	XINPUT_STATE joyState_{};

	AnimationPlayerMove MoveAnimationCase = UP;

	WorldTransform reticleWorldTransform = {};

	list<shared_ptr<PlayerBullet>>bullets_ = {};
	unique_ptr<HitParticle>hitParticle_ = nullptr;

	Vector3 RPNormalize = {};

	unique_ptr<PlayerBulletLine>bulletLine_ = nullptr;

};