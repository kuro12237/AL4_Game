#include "Enemy.h"

void Enemy::Initialize(Vector3 spownPos)
{
	ModelHandle_ = ModelManager::LoadObjectFile("Enemy");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(ModelHandle_);
	gameObject_->UseLight(true);
	worldTransform_.Initialize();
	worldTransform_.translate = spownPos;
	worldTransform_.translate.y += 0.5f;
	worldTransform_.UpdateMatrix();
	SetSize({ 1.0f,1.0f,1.0f });
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionMaskEnemy);
}

void Enemy::Update()
{
	OBBCollider::SetSize({ 1.0f,1.0f,1.0f });
	OBBCollider::SetRotate(this->worldTransform_.rotation);
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];

	return result;
}

void Enemy::OnCollision(uint32_t id)
{
	id;
}
