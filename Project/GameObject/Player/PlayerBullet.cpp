#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector3 pos, Vector3 v)
{
	modelHandle_ = ModelManager::LoadObjectFile("PlayerBullet");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	
	float velocityXZ = sqrt(v.x * v.x + v.z * v.z);

	float heightY = -v.y;

	worldTransform_.rotation.y = std::atan2(v.x, v.z);
	worldTransform_.rotation.x = std::atan2(heightY, velocityXZ);

	velocity_ = v;
	soundHandle_ = AudioManager::SoundLoadWave("Resources/Sounds/kill.wav");

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
	SetID(0x00010);
}

void PlayerBullet::Update()
{
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);

	timer_++;


	if (timer_>=120)
	{
		isAlive = false;
	}

	worldTransform_.UpdateMatrix();
	OBBCollider::SetRotate(worldTransform_.rotation);
	OBBCollider::SetSize({ 1.5f,1.5f,3.0f });
}

void PlayerBullet::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}

void PlayerBullet::OnCollision(uint32_t id)
{
	id;
	isAlive = false;
	AudioManager::AudioPlayWave(soundHandle_);
}

Vector3 PlayerBullet::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}
