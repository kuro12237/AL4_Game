#include "Enemy.h"

void Enemy::Initialize(Vector3 spownPos)
{
	ModelHandle_ = ModelManager::LoadObjectFile("Enemy");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(ModelHandle_);
	gameObject_->UseLight(true);
	worldTransform_.Initialize();
	worldTransform_.scale = {};
	worldTransform_.translate = spownPos;
	worldTransform_.translate.y += 0.5f;
	worldTransform_.UpdateMatrix();
	SetSize({ 1.0f,1.0f,1.0f });
	
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionMaskEnemy);
	SetID(0x00100);

	mt19937 randomEngine(seedGenerator());
	uniform_real_distribution<float>distribution(-0.7f, 0.7f);

	velocity_ = { distribution(randomEngine),0.0f,distribution(randomEngine) };

}

void Enemy::Update()
{
	


	if (isHit_)
	{
		worldTransform_.scale = VectorTransform::Add(worldTransform_.scale, { -0.05f,-0.05f,-0.05f });
		if (worldTransform_.scale.x <= 0.0f && worldTransform_.scale.y <= 0.0f && worldTransform_.scale.z <= 0.0f)
		{
			isAlive_ = false;
		}
	}

	const float kMoveLimitX = 30.0f;
	const float kMoveLimitZ = 30.0f;
	worldTransform_.translate.x = max(worldTransform_.translate.x, -kMoveLimitX);
	worldTransform_.translate.x = min(worldTransform_.translate.x, kMoveLimitX);
	worldTransform_.translate.z = max(worldTransform_.translate.z, -kMoveLimitZ);
	worldTransform_.translate.z = min(worldTransform_.translate.z, kMoveLimitZ);

	if (worldTransform_.translate.x >= kMoveLimitX || worldTransform_.translate.x <= -kMoveLimitX)
	{
		velocity_.x = velocity_.x * -1;
	}

	if (worldTransform_.translate.z >= kMoveLimitZ || worldTransform_.translate.z <= -kMoveLimitZ)
	{
		velocity_.z = velocity_.z * -1;
	}

	if (!isHit_)
	{
		if (isSpownAnimationFlag_)
		{
			worldTransform_.scale = VectorTransform::Add(worldTransform_.scale, { 0.05f,0.05f,0.05f });
			if (worldTransform_.scale.x >= 1.0f && worldTransform_.scale.y >= 1.0f && worldTransform_.scale.z >= 1.0)
			{
				isSpownAnimationFlag_ = false;
			}

		}
		worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	}

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
	
	if (!isHit_)
	{
		if (id == 0x00001)
		{
			
		}
		if (id == 0x00010)
		{
			isHit_ = true;
		}
		if (id==0x00100)
		{
			velocity_.x = velocity_.x * -1;
			velocity_.y = velocity_.y * -1;
		}
	}
}
